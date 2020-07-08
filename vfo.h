#ifndef VFO_H
#define VFO_H

#include <QPushButton>
#include <QPixmap>
#include "number_keypad.h"
#include <QProgressBar>
#include <QLabel>
#include <QStatusBar>
#include <qwt_plot.h>
#include "spectrumdisplay.h"
#include <QThread>
#include <fftplot.h>
#include <statusregs.h>
#include <pl_addresses.h>


#define MIN_FREQ ((unsigned long long) 100000)
#define MAX_FREQ ((unsigned long long) 99000000000)


class vfo : public QObject {

    Q_OBJECT

public:
    vfo(
        QPushButton *freqButton,
        QPushButton *rxButton,
        QPushButton *txButton,
        QLabel *fcLabel,
        QPushButton *fcButton,
        QLabel *bwLabel,
        QPushButton *bwButton,
        QPushButton *modeButton,
        QLabel *meterLabel,
        QPushButton *meterScale,
        QProgressBar *meter,
        QLabel *ritLabel,
        QLabel *xitLabel,
        QStatusBar *statusBar,
        const char *dmaFileName,
        FftPlot *fft,
        WaterfallPlot *waterfall,
        StatusRegs *status
);

    ~vfo();
    typedef enum {AM, FM, USB, LSB, DATA} mode_t;
    void set_mode(mode_t mode);
    void set_freq(unsigned long long freq);
    void set_tx_enabled(bool x);
    void set_rx_enabled(bool x);
    void toggle_tx_enabled();
    void toggle_rx_enabled();
    bool get_tx_enabled();
    bool get_rx_enabled();
    void run_keypad(QWidget *parent = nullptr);
    void set_s_meter(int x);
    void set_rit(int x);
    void set_xit(int x);

private:

    // GUI references
    QPushButton *freqButton;
    QPushButton *rxButton;
    QPushButton *txButton;
    QLabel *fcLabel;
    QPushButton *fcButton;
    QLabel *bwLabel;
    QPushButton *bwButton;
    QPushButton *modeButton;
    QLabel *meterLabel;
    QPushButton *meterScale;
    QProgressBar *meter;
    QLabel *ritLabel;
    QLabel *xitLabel;
    QStatusBar* statusBar;
    spectrumDisplay *spectrum;
    StatusRegs *_status;

    // VFO freq
    unsigned long long freq;
    unsigned long long stepSize;

    // VFO mode
    mode_t mode;

    // VFO Usage settings
    bool rxEnabled;
    bool txEnabled;
    bool txActive;

    // AF DSP settings
    int fc;
    int bw;

    // RIT / XIT settings
    int rit;
    int xit;

    // ADC settings
    double _adcfreq;

};

#endif // VFO_H
