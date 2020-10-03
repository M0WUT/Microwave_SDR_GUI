#ifndef SPECTRUMDISPLAY_H
#define SPECTRUMDISPLAY_H

#include <QObject>
#include <dma_worker.h>
#include <QThread>
#include <waterfallplot.h>
#include <fftplot.h>
#include <sys/ioctl.h>
#include <statusregs.h>
#include <pl_addresses.h>



#define FFT_SIZE 1024

class dma_worker;

class spectrumDisplay : public QObject {

    Q_OBJECT

    friend class dma_worker;

public:
    spectrumDisplay(
            const char *dmaFileName,
            FftPlot *fft,
            WaterfallPlot *waterfall,
            StatusRegs *status

    );
    ~spectrumDisplay();
    void set_freq(unsigned long long freq);
    uint32_t calculate_if_freq(uint32_t freq);


signals:
    void start_dma();

public slots:
    void process_dma();

private:
    FftPlot *_fft;
    WaterfallPlot *_waterfall;
    dma_worker *_worker;
    QThread *_dmaThread;
    StatusRegs *_status;


};

#endif // SPECTRUMDISPLAY_H

