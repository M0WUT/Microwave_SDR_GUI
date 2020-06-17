#include "dma_worker.h"

dma_worker::dma_worker(const char *dmaFileName, int fftSize)
{
    this->dmaFile = open(dmaFileName, O_RDONLY);
    if(this->dmaFile == -1){
        qDebug() << "Could not open DMA file" << endl;
        exit(-EINVAL);
    }
    this->fftSize = fftSize;
    this->fftData = (double *) malloc(this->fftSize * sizeof (double));
    if(this->fftData == NULL){
        qDebug() << "Could not allocate memory for DMA buffer" << endl;
        exit(-ENOMEM);
    }

}

dma_worker::~dma_worker()
{
    close(this->dmaFile);
    free(this->fftData);
}

void dma_worker::run()
{
    //qDebug() << "Reading\n";
    // Need 2x for symmetric half of FFT as well
    int64_t tempData[2048];
    read(this->dmaFile, tempData, 2048 * sizeof(int64_t));
    // Convert to double for QwtPlot

    for(int i = 0; i < this->fftSize; i++){
        // Hacky fix to prevent trying to calculate log(0)
        double x_d = tempData[i] == 0 ? 1 : tempData[i];
        this->fftData[i] = 20 * log10(x_d) - 215;
    }
    emit ready(this->fftData);

}
