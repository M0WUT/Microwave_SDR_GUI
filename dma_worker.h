#ifndef DMA_WORKER_H
#define DMA_WORKER_H

#include <QObject>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <errno.h>
#include <stdint.h>
#include <unistd.h>
#include <assert.h>
#include <QDebug>
#include <math.h>
#include <spectrumdisplay.h>

class spectrumDisplay;

class dma_worker : public QObject
{
    Q_OBJECT
public:
    dma_worker(spectrumDisplay *parent, const char *dmaFileName, int fftSize);
    ~dma_worker();

public slots:
    void run();

signals:
    void ready();


private:
    int dmaFile;
    int fftSize;
    double *fftData;
    spectrumDisplay *_parent;
};


#endif // DMA_WORKER_H
