#ifndef IIC_H
#define IIC_H

#include <QObject>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

class iic
{
public:
    iic(const char* filename);
    ~iic();
    void write_single(uint16_t reg_address, uint8_t data);
    void write_block(uint16_t reg_address, uint8_t *data, uint8_t data_length);
private:
    int _fd;
};

#endif // IIC_H
