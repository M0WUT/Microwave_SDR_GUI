#include "waterfalldata.h"

WaterfallData::WaterfallData(const uint32_t fftSize, const uint32_t historySize, double min, double max)
{
    this->_fftSize = fftSize;
    this->_historySize = historySize;
    // Allocate memory for data and set all to 0
    _fftData = (double *) malloc(_fftSize * _historySize * sizeof(double));
    memset(_fftData, -120.0, _fftSize * _historySize * sizeof(double));
    setInterval(Qt::XAxis, QwtInterval(0, _fftSize));
    setInterval(Qt::YAxis, QwtInterval(0, _historySize));
    setInterval(Qt::ZAxis, QwtInterval(min, max));
}

WaterfallData::~WaterfallData()
{
    free(_fftData);
}


void WaterfallData::add_fft_data(const double *data, const uint32_t size)
{
    assert((size == _fftSize));  // FFT Data must be the expected size
    // Move all previous FFTs one position closer to 0th position
    memmove(_fftData, &_fftData[_fftSize], _fftSize * (_historySize - 1) * sizeof(double));

    // Insert new data to (now) blank space at end of _fftData
    memcpy(&_fftData[(_historySize - 1) * _fftSize], data, _fftSize * sizeof(double));


}

double WaterfallData::value(double x, double y) const
{
    // x and y are pixel coordinates in the the plot window, need to return
    // the amplitude at that point in the data. Returns nearest value

    double yMax = interval(Qt::YAxis).maxValue();
    double xMax = interval(Qt::XAxis).maxValue();
    double xMin = interval(Qt::XAxis).minValue();
    double yLength = (double)(_historySize - 1);
    double xLength = (double)(_fftSize - 1);

    unsigned int yLocation = (unsigned int) ((1.0 - y / yMax) * yLength);
    unsigned int xLocation = (unsigned int) (((x - xMin) / (xMax - xMin)) * xLength + 0.5);
    unsigned int location = yLocation * _fftSize + xLocation;
    //qDebug() << y << yMax << yLength << yLocation << "\n";
    return _fftData[location];
}
