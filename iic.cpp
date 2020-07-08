#include "iic.h"

iic::iic(const char *filename)
{
    this->_fd = open(filename, O_WRONLY);
    assert (_fd != -1);
}

iic::~iic()
{
    close(_fd);
}

void iic::write_single(uint16_t reg_address, uint8_t data)
{
    uint8_t x = data;
    return(write_block(reg_address, &x, 1));
}

void iic::write_block(uint16_t reg_address, uint8_t *data, uint8_t data_length)
{
    uint8_t x[data_length + 2];
    int i;
    x[0] = (reg_address >> 8) & 0xFF;
    x[1] = reg_address & 0xFF;
    for(i = 0; i < data_length; i++){
        x[i+2] = data[i];
    }

    int bytes_written = write(_fd, x, data_length + 2);
    assert(bytes_written == data_length + 2);
}
