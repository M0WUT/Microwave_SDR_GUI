#ifndef FFTPLOT_H
#define FFTPLOT_H

#include <qwt_plot.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_curve.h>
#include <assert.h>


class FftPlot : public QwtPlot
{
public:
    FftPlot(QWidget *parent);
    ~FftPlot();
    void initialise(unsigned int fftSize, double minY, double maxY, double freqStart, double freqStep);
    void set_data(const double *data, unsigned int size);
    void set_freq(const double freqStart);
private:
    QwtPlotCurve *_curve;
    unsigned int _fftSize;
    double _minY, _maxY, _freqStart, _freqStep;
    double *_freq;
};

#endif // FFTPLOT_H
