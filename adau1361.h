#ifndef ADAU1361_H
#define ADAU1361_H

#include <adau1361_pll.h>
#include <adau1361_input_channel.h>
#include <adau1361_output_channel.h>
#include <adau1361_common.h>


class adau1361 : public QObject
{
    Q_OBJECT
public:
    adau1361(const char *iicFile, const int slaveAddress);
    void set_operational_mode(op_mode_t mode);
    ~adau1361();
    void enable_mic_bias(bool x);

private:
    iic *_iic;
    adau1361_pll *_pll;
    op_mode_t _op_mode;
    adau1361_input_channel *_leftInputChannel, *_rightInputChannel;
    adau1361_output_channel *_leftOutputChannel, *_rightOutputChannel;
    bool _micBiasEnabled;

};

#endif  // #ifdef ADAU1361_H
