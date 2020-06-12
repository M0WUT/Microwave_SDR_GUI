#ifndef WATERFALLDATA_H
#define WATERFALLDATA_H

#include <qwt_raster_data.h>


class WaterfallData : public QwtRasterData
{
public:
    WaterfallData(
            const uint32_t fftSize,  // Number of points in an FFT
            const uint32_t historySize,  // Number of past FFTs to save
            double min,
            double max
    );
    ~WaterfallData();
    void add_fft_data(
            const double *data,  // new FFT data
            const uint32_t size  // this must be equal to fftSize
    );
    double value(double x, double y) const;  // Returns amplitude from coordinates in _fftData

private:
    uint32_t _fftSize;
    uint32_t _historySize;
    double *_fftData;
};

#endif // WATERFALLDATA_H
