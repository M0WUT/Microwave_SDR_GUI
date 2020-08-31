#ifndef ADAU1361_OUTPUT_CHANNEL_H
#define ADAU1361_OUTPUT_CHANNEL_H

#include <adau1361_common.h>

class adau1361_output_channel
{
    Q_OBJECT
public:
    adau1361_output_channel();
    bool enabled();
};

#endif // ADAU1361_OUTPUT_CHANNEL_H
