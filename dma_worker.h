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

class dma_worker : public QObject
{
    Q_OBJECT
public:
    dma_worker(const char *dmaFileName, int fftSize);
    ~dma_worker();

public slots:
    void run();

signals:
    void ready(double *data_p);


private:
    int dmaFile;
    int fftSize;
    double *fftData;
};


#endif // DMA_WORKER_H
