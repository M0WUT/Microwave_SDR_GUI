#include "waterfallplot.h"


WaterfallPlot::WaterfallPlot(QWidget *parent):
    QwtPlot(parent)
{

}

void WaterfallPlot::add_fft_data(const double *data, const unsigned int size)
{
    this->_data->add_fft_data(data, size);
    this->_spectrogram->setData(this->_data);
}

class ColorMap_MultiColor : public QwtLinearColorMap
{
public:
    ColorMap_MultiColor() : QwtLinearColorMap(Qt::darkCyan, Qt::white)
    {
        addColorStop(0.4, Qt::cyan);
        addColorStop(0.6, Qt::yellow);
        addColorStop(0.8, Qt::red);
    }
};

void WaterfallPlot::initialise(unsigned int fftSize, unsigned int historySize, double min, double max)
{
    this->_fftSize = fftSize;
    this->_historySize = historySize;
    this->setAxisScale(QwtPlot::xBottom, 0, fftSize);
    this->setAxisScale(QwtPlot::yLeft, 0, historySize);

    this->_spectrogram = new QwtPlotSpectrogram;
    this->_colourMap = new ColorMap_MultiColor();
    this->_spectrogram->setColorMap(this->_colourMap);
    this->_spectrogram->setRenderThreadCount(4);
    this->_intensityAxis = axisWidget(QwtPlot::yRight);
    this->setAxisScale(QwtPlot::yRight, min, max);
    QwtInterval z = QwtInterval(min, max);
    this->_intensityAxis->setColorMap(z, this->_colourMap);
    this->_data = new WaterfallData(fftSize, historySize, min, max);
    this->enableAxis(QwtPlot::xBottom, true);

    this->_spectrogram->attach(this);
}
