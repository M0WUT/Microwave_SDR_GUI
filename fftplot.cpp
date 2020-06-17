#include "fftplot.h"

FftPlot::FftPlot(QWidget *parent):
    QwtPlot(parent)
{
    this->_curve = new QwtPlotCurve();

    // Set Curve properties
    this->_curve->setPen(Qt::green, 1);
    this->_curve->attach(this);

    // Enable Grid
    QwtPlotGrid *grid = new QwtPlotGrid();
    grid->setPen(0x666666);
    grid->attach(this);
}

FftPlot::~FftPlot()
{
    free(this->_freq);
}

void FftPlot::initialise(unsigned int fftSize, double minY, double maxY, double freqStart, double freqStep)
{
    this->_fftSize = fftSize;
    this->_freq = (double *) malloc(_fftSize * sizeof(double));
    this->_minY = minY;
    this->_maxY = maxY;
    this->set_freq(freqStart);
    this->setAxisScale(QwtPlot::xBottom, _freqStart, _freqStart + _fftSize * _freqStep);
    this->setAxisScale(QwtPlot::yLeft, minY, maxY);
}

void FftPlot::set_data(const double *data, unsigned int size)
{
    assert (size == _fftSize);
    this->_curve->setSamples(_freq, data, _fftSize);
    this->replot();
}

void FftPlot::set_freq(const double freqStart)
{
    this->_freqStart = freqStart;

    for(unsigned int i = 0; i < _fftSize; i++)
        _freq[i] = freqStart + i * _freqStep;
}


