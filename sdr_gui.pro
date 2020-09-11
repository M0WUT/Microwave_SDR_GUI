QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adau1361.cpp \
    adau1361_input_channel.cpp \
    adau1361_output_channel.cpp \
    adau1361_pll.cpp \
    audio_handler.cpp \
    clickablelabel.cpp \
    dma_worker.cpp \
    fftplot.cpp \
    iic.cpp \
    main.cpp \
    mainwindow.cpp \
    number_keypad.cpp \
    spectrumdisplay.cpp \
    statusregs.cpp \
    vfo.cpp \
    waterfalldata.cpp \
    waterfallplot.cpp

HEADERS += \
    adau1361.h \
    adau1361_common.h \
    adau1361_input_channel.h \
    adau1361_output_channel.h \
    adau1361_pll.h \
    audio_handler.h \
    clickablelabel.h \
    dma_worker.h \
    fftplot.h \
    iic.h \
    mainwindow.h \
    number_keypad.h \
    pl_addresses.h \
    spectrumdisplay.h \
    src/json/json.hpp \
    statusregs.h \
    vfo.h \
    waterfalldata.h \
    waterfallplot.h

FORMS += \
    mainwindow.ui \
    number_keypad.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc \
    resources/qdarkstyle/style.qrc


INCLUDEPATH += /home/dan/SDR_Petalinux_Project/images/linux/sdk/sysroots/cortexa9t2hf-neon-xilinx-linux-gnueabi/usr/include/
INCLUDEPATH += /home/dan/SDR_Petalinux_Project/images/linux/sdk/sysroots/cortexa9t2hf-neon-xilinx-linux-gnueabi/usr/include/QtWidgets
INCLUDEPATH += /home/dan/SDR_Petalinux_Project/images/linux/sdk/sysroots/cortexa9t2hf-neon-xilinx-linux-gnueabi/usr/include/c++/8.2.0
INCLUDEPATH += /home/dan/SDR_Petalinux_Project/images/linux/sdk/sysroots/cortexa9t2hf-neon-xilinx-linux-gnueabi/usr/include/c++/8.2.0/arm-xilinx-linux-gnueabi

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/local/qwt-6.1.3/lib/release/ -lqwt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/local/qwt-6.1.3/lib/debug/ -lqwt
else:unix: LIBS += -L$$PWD/../../../../usr/local/qwt-6.1.3/lib/ -lqwt

CONFIG += qwt

INCLUDEPATH += $$PWD/../../../../usr/local/qwt-6.1.3/include
DEPENDPATH += $$PWD/../../../../usr/local/qwt-6.1.3/include
