#ifndef SPECTRUMDISPLAY_H
#define SPECTRUMDISPLAY_H

#include <QObject>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <errno.h>
#include <stdint.h>
#include <unistd.h>
#include <assert.h>
#include <dma_worker.h>
#include <QThread>
#include <qwt_plot_grid.h>
#include <waterfalldata.h>
#include <qwt_plot_spectrogram.h>
#include <qwt_scale_widget.h>
#include <qwt_color_map.h>
#include <waterfallplot.h>



#define FFT_SIZE 1024

class spectrumDisplay : public QObject {

    Q_OBJECT

public:
    spectrumDisplay(const char *dmaFileName, QwtPlot *fft, WaterfallPlot *waterfall);
    ~spectrumDisplay();
    QwtPlotCurve *fftCurve;

signals:
    void start_dma();

public slots:
    void process_dma(double *data);

private:
    double x[FFT_SIZE];
    double fftData[FFT_SIZE];
    QwtPlot *fft;
    WaterfallPlot *waterfall;
    dma_worker *worker;
    QThread *dmaThread;


};

#endif // SPECTRUMDISPLAY_H

