#ifndef STATUSREGS_H
#define STATUSREGS_H

#include <QString>
#include <fstream>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <QMessageBox>
#include <QApplication>
#include <assert.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <QDebug>
#include <string>

#define IOCTL_SET_ADDRESS _IO(202, 0)

class StatusRegs
{
public:
    StatusRegs(QWidget *parent, const char *filename);
    ~StatusRegs();
    uint32_t read(unsigned int address);
    void write(unsigned int address, uint32_t data);

private:
    int _fd;
    void _set_address(int address);
    QWidget *parent;

};

#endif // STATUSREGS_H
