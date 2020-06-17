#include "statusregs.h"

StatusRegs::StatusRegs(QWidget *parent, const char *filename)
{
    this->_fd = open(filename, O_RDWR);

    if(_fd == -1){
        // Either couldn't find file or the PL memory didn't look as expected
        QMessageBox::critical(parent, "Fatal Error", "Could not find /dev/status");
        QApplication::quit();
    }

    uint32_t y = read(0);
    uint32_t majorVersion, minorVersion;
    majorVersion = (y >> 8) & 0xFF;
    minorVersion = y & 0xFF;

    qDebug() << "INFO: FPGA Firmware detected. Version" << majorVersion << "." << minorVersion << "\n";

}

StatusRegs::~StatusRegs()
{
    close(_fd);
}

uint32_t StatusRegs::read(unsigned int address)
{
    char buffer[20];
    _set_address(address);
    ::read(_fd, buffer, 20);
    QString x(buffer);
    uint32_t y = x.toUInt();
    return y;
}

void StatusRegs::write(unsigned int address, uint32_t data)
{
    // @TODO
}

void StatusRegs::_set_address(int address)
{
    if(ioctl(_fd, IOCTL_SET_ADDRESS, address)){
        // Most likely wrote to unallowed memory address
        qDebug() << "ERROR: Attempt to access memory address" << address << "was not permitted\n";
        assert(0);
    }
}


