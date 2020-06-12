#ifndef WATERFALLPLOT_H
#define WATERFALLPLOT_H

#include <qwt_plot.h>
#include <waterfalldata.h>
#include <qwt_plot_spectrogram.h>
#include <qwt_color_map.h>
#include <qwt_scale_widget.h>

class WaterfallPlot : public QwtPlot
{
public:   
    WaterfallPlot(QWidget *parent);
    void add_fft_data(const double *data, const unsigned int size);
    void initialise(unsigned int fftSize, unsigned int historySize, double min, double max);
private:
    QwtPlotSpectrogram *_spectrogram;
    WaterfallData *_data;
    QwtColorMap *_colourMap;  // I'm English, it has a u!
    QwtScaleWidget *_intensityAxis;
    uint32_t _fftSize;
    uint32_t _historySize;
};

#endif // WATERFALLPLOT_H
