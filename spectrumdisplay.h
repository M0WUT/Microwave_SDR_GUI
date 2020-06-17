#ifndef SPECTRUMDISPLAY_H
#define SPECTRUMDISPLAY_H

#include <QObject>
#include <dma_worker.h>
#include <QThread>
#include <waterfallplot.h>
#include <fftplot.h>
#include <sys/ioctl.h>



#define FFT_SIZE 1024

class spectrumDisplay : public QObject {

    Q_OBJECT

public:
    spectrumDisplay(const char *dmaFileName, FftPlot *fft, WaterfallPlot *waterfall);
    ~spectrumDisplay();
    void set_freq(unsigned long long freq);


signals:
    void start_dma();

public slots:
    void process_dma(double *data);

private:
    FftPlot *_fft;
    WaterfallPlot *_waterfall;
    dma_worker *_worker;
    QThread *_dmaThread;


};

#endif // SPECTRUMDISPLAY_H

