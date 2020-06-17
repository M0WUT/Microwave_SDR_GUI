#include "spectrumdisplay.h"

spectrumDisplay::spectrumDisplay(const char *dmaFileName, FftPlot *fft, WaterfallPlot *waterfall)
{

    this->_fft = fft;
    this->_fft->initialise(FFT_SIZE, -135, -40, 28e6, 1000);


    this->_waterfall = waterfall;
    this->_waterfall->initialise(FFT_SIZE, 100, -135, -40);

    this->_worker = new dma_worker(dmaFileName, FFT_SIZE);


    // Setup DMA Thread
    this->_dmaThread = new QThread;
    this->_worker->moveToThread(this->_dmaThread);

    // Connect Signals and Slots
    connect(
        this->_dmaThread, &QThread::started,
        this->_worker, &dma_worker::run
    );

    connect(
        this, &spectrumDisplay::start_dma,
        this->_worker, &dma_worker::run
    );

    connect(
        this->_worker, &dma_worker::ready,
        this, &spectrumDisplay::process_dma
    );

    connect(
        this->_dmaThread, &QThread::finished,
        this->_worker, &dma_worker::deleteLater
    );

    this->_dmaThread->start();

}

spectrumDisplay::~spectrumDisplay()
{
    this->_dmaThread->quit();
}

void spectrumDisplay::set_freq(unsigned long long freq)
{
    this->_fft->set_freq(freq);
}

void spectrumDisplay::process_dma(double *data)
{
    this->_fft->set_data(data, FFT_SIZE);
    this->_waterfall->add_fft_data(data, FFT_SIZE);
    emit(start_dma());
}
