#include "spectrumdisplay.h"

spectrumDisplay::spectrumDisplay(const char *dmaFileName, QwtPlot *fft, WaterfallPlot *waterfall)
{

    this->fft = fft;
    this->fft->setAxisScale(QwtPlot::xBottom, 0, FFT_SIZE);
    this->fft->setAxisScale(QwtPlot::yLeft, -135, -40);

    this->waterfall = waterfall;
    this->waterfall->initialise(FFT_SIZE, 100, -135, -40);



    this->worker = new dma_worker(dmaFileName, FFT_SIZE);

    this->fftCurve = new QwtPlotCurve();

    // Populate dummy axis data
    for(int i = 0; i < FFT_SIZE; i++) {
        this->x[i] = i;
    }

    // Set Curve properties
    this->fftCurve->setPen(Qt::green, 1);
    this->fftCurve->attach(this->fft);



    // Enable Grid
    QwtPlotGrid *grid = new QwtPlotGrid();
    grid->setPen(0x666666);
    grid->attach(this->fft);

    // Setup DMA Thread
    this->dmaThread = new QThread;
    this->worker->moveToThread(this->dmaThread);

    // Connect Signals and Slots
    connect(
        this->dmaThread, &QThread::started,
        this->worker, &dma_worker::run
    );

    connect(
        this, &spectrumDisplay::start_dma,
        this->worker, &dma_worker::run
    );

    connect(
        this->worker, &dma_worker::ready,
        this, &spectrumDisplay::process_dma
    );

    connect(
        this->dmaThread, &QThread::finished,
        this->worker, &dma_worker::deleteLater
    );

    this->dmaThread->start();

}

spectrumDisplay::~spectrumDisplay()
{
    this->dmaThread->quit();
}

void spectrumDisplay::process_dma(double *data)
{
    this->fftCurve->setSamples(x, data, FFT_SIZE);
    this->fft->replot();
    this->waterfall->add_fft_data(data, FFT_SIZE);
    emit(start_dma());
}
