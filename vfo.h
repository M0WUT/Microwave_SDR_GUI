#ifndef VFO_H
#define VFO_H

#include <QPushButton>
#include <QPixmap>
#include "number_keypad.h"


#define MIN_FREQ ((unsigned long long) 100000)
#define MAX_FREQ ((unsigned long long) 99000000000)


class vfo
{
public:
    vfo(
        QPushButton *freqButton,
        QPushButton *rxButton,
        QPushButton *txButton,
        QPushButton *fcButton,
        QPushButton *bwButton,
        QPushButton *modeButton
    );

    ~vfo();
    typedef enum {AM, FM, USB, LSB, DATA} mode_t;
    void set_mode(mode_t mode);
    void set_freq(unsigned long long freq);
    void set_freq(QString freq);
    void set_tx_enabled(bool x);
    void set_rx_enabled(bool x);
    void toggle_tx_enabled();
    void toggle_rx_enabled();
    bool get_tx_enabled();
    bool get_rx_enabled();
    void run_keypad(QWidget *parent = nullptr);

private:

    // GUI references
    QPushButton *freqButton;
    QPushButton *rxButton;
    QPushButton *txButton;
    QPushButton *fcButton;
    QPushButton *bwButton;
    QPushButton *modeButton;

    // VFO freq
    unsigned long long freq;
    unsigned long long stepSize;

    // VFO mode
    mode_t mode;

    // VFO Usage settings
    bool rxEnabled;
    bool txEnabled;
    bool txActive;

    // AF DSP settings
    int fc;
    int bw;
};

#endif // VFO_H
