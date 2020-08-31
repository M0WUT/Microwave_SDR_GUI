#include "adau1361_input_channel.h"

adau1361_input_channel::adau1361_input_channel(channel_t channel, iic *iic)
{
    this->_channel = channel;
    this->_iic = iic;
}

void adau1361_input_channel::set_input(adc_input_t input)
{
    // Input source
    uint8_t x[4];
    switch(input) {
        case DIGITAL_MICROPHONE:  // Deliberate fallthrough
        case INPUT_DISABLED:
            x[0] = 0;  // Mute INP, INN and disable mixer
            x[1] = 0;  // Mute DIFF and AUX input
            break;
        case IN_P:
            x[0] = 0b01010001;  // 0dB gain for INP, mute INN  and enable mixer
            x[1] = 0;  // Mute DIFF and AUX input
            break;
        case IN_N:
            x[0] = 0b00001011;  // 0dB gain for INN, mute INP and enable mixer
            x[1] = 0;  // Mute DIFF and AUX input
            break;
        case IN_DIFF:
            x[0] = 0b00000001;  // Mute INP, INN and enable mixer
            x[1] = 0b00001000;  // 0dB gain for DIFF, mute AUX
            break;
        case IN_AUX:
            x[0] = 0b00000001;  // Mute INP, INN and enable mixer
            x[1] = 0b00000101;  // Mute DIFF, 0dB gain for AUX
            break;
    };

    uint16_t address;
    if(_channel == LEFT_CHANNEL)
        address = ADAU1361_REG_REC_MIXER_L0;
    else
        address = ADAU1361_REG_REC_MIXER_R0;

    this->_iic->write_block(address, x, 2);
    this->_input = input;

    // Differential input volume control
    x[0] = (0b010000 << 2);  // 0dB differential gain
    if(_input == IN_DIFF)
        x[0] |= 0b11;  // Enable and unmute differential input
    else
        x[0] |= 0b00; // Disable and mute differential input

    if(_channel == LEFT_CHANNEL)
        address = ADAU1361_REG_LEFT_DIFF_VOL;
    else
        address = ADAU1361_REG_RIGHT_DIFF_VOL;

    _iic->write_single(address, x[0]);

    // ALC

}

bool adau1361_input_channel::enabled()
{
    if(_input != INPUT_DISABLED)
        return true;
    else
        return false;
}
