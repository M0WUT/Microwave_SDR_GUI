/*  adau1361.c
*
*   This program is free software; you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation; either version 3 of the License, or
*   (at your option) any later version.

*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License along
*   with this program. If not, see <http://www.gnu.org/licenses/>.

*/
#include "adau1361.h"


adau1361::adau1361(const char *iicFile, const int slaveAddress)
{
    this->_iic = new iic(iicFile);
    assert (_iic != NULL);
    this->_iic->set_slave_address(slaveAddress);
    this->_pll = new adau1361_pll(this->_iic);
    assert (_pll != NULL);
    this->_pll->apply_settings();
    // Force disable jack detect as AD admit it doesn't work
    // source: https://ez.analog.com/dsp/sigmadsp/f/q-a/66306/jack-detection-with-adau1361
    this->_iic->write_single(ADAU1361_REG_JACK_DETECT, 0);


    // Load config with everything muted as default

    // Input channels
    _leftInputChannel = new adau1361_input_channel(LEFT_CHANNEL, this->_iic);
    assert (_leftInputChannel != NULL);
    _rightInputChannel = new adau1361_input_channel(RIGHT_CHANNEL, this->_iic);
    assert (_rightInputChannel != NULL);

    _leftInputChannel->set_input(INPUT_DISABLED);
    _rightInputChannel->set_input(INPUT_DISABLED);

    // Output channels



    // Generic settings
    this->set_operational_mode(NORMAL);
    enable_mic_bias(false);

}

void adau1361::set_operational_mode(op_mode_t mode)
{
    // Data[0] is for record power managment
    // Data[1] is for playback power management
    uint8_t data[2];
    switch(mode) {
        case NORMAL:
            data[0] = 0;
            data[1] = 0;
            break;
        case EXTREME_POWER_SAVING:
            data[0] = 0b00001110;
            data[1] = 0b01011100;
            break;
        case POWER_SAVING:
            data[0] = 0b00011110;
            data[1] = 0b11111100;
            break;
        case ENHANCED_PERFORMANCE:
            data[0] = 0b00101000;
            data[1] = 0b10101000;
            break;
    };

    this->_iic->write_single(ADAU1361_REG_REC_PWR_MGMT, data[0]);
    if(this->_rightOutputChannel->enabled())
        data[1] |= 2;
    if(this->_leftOutputChannel->enabled())
        data[1] |= 1;
    this->_iic->write_single(ADAU1361_REG_PLAY_PWR_MGMT, data[1]);
    _op_mode = mode;
}

adau1361::~adau1361()
{

}

void adau1361::enable_mic_bias(bool x)
{
    uint8_t data;

    if(_op_mode == ENHANCED_PERFORMANCE)
        data = (1 << 3);
    else
        data = 0;

    data |= x;
    _iic->write_single(ADAU1361_REG_REC_MIC_BIAS, data);
    _micBiasEnabled = x;
}
