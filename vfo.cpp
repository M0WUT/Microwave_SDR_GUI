#include "vfo.h"

vfo::vfo (ClickableLabel *freqButton,
    QPushButton *rxButton,
    QPushButton *txButton,
    QLabel *fcLabel,
    QPushButton *fcButton,
    QLabel *bwLabel,
    QPushButton *bwButton,
    QPushButton *modeButton,
    QLabel *meterLabel,
    QPushButton *meterScale,
    QProgressBar *meter,
    QLabel *ritLabel,
    QLabel *xitLabel,
    QStatusBar *statusBar,
    const char *dmaFileName,
    FftPlot *fft,
    WaterfallPlot *waterfall,
    StatusRegs *status
)
{
    // Copy GUI references into self
    this->freqButton = freqButton;
    this->rxButton = rxButton;
    this->txButton = txButton;
    this->fcLabel = fcLabel;
    this->fcButton = fcButton;
    this->bwLabel = bwLabel;
    this->bwButton = bwButton;
    this->modeButton = modeButton;
    this->meterLabel = meterLabel;
    this->meterScale = meterScale;
    this->meter = meter;
    this->ritLabel = ritLabel;
    this->xitLabel = xitLabel;
    this->statusBar = statusBar;
    this->spectrum = new spectrumDisplay(dmaFileName, fft, waterfall, status);
    this->_status = status;


    QString filename = ":resources/img/scale_s_meter";
    QPixmap pix(filename);
    QIcon icon(pix);
    this->meterScale->setFixedSize(280, 20);
    this->meterScale->setIconSize(QSize(280, 28));
    this->meterScale->setIcon(icon);

    this->_adcfreq = 80e6;

    this->set_rx_enabled(1);
    this->set_tx_enabled(0);

    this->set_s_meter(13);
    this->set_rit(0);
    this->set_xit(0);

    set_step_size(100);
    _status->write(ADDRESS_DISPMODE, 2);
}

vfo::~vfo()
{
    ;
}

void vfo::set_mode(vfo::mode_t mode)
{
    this->mode = mode;

    //TODO
}

void vfo::set_freq(unsigned long long freq)
{

    unsigned long long requestedFreq = freq;
    freq = std::min(freq, MAX_FREQ);
    freq = std::max(freq, MIN_FREQ);

    if(freq != requestedFreq){
        // Frequency has had to be limited
        QString msg;
        if(freq > 1e9){
            msg.setNum(freq / 1e9);
            msg += " GHz";
        } else if(freq > 1e6){
            msg.setNum(freq / 1e6);
            msg += " MHz";
        } else if(freq > 1e3){
            msg.setNum(freq/ 1e3);
            msg += " kHz";
        } else {
            msg.setNum(freq);
            msg += " Hz";
        }
        msg.prepend("Requested frequency out of range. Limited to ");
        statusBar->showMessage(msg, 2000);
    }





    unsigned long long  fftFreq = this->spectrum->calculate_if_freq(freq);

    _status->write(ADDRESS_FFTACC, (double) (fftFreq << 32) / _adcfreq);
    _status->write(ADDRESS_DISPFREQ, freq);

    _status->write(ADDRESS_PHACC1, (double) (freq << 32) / _adcfreq);

    //this->spectrum->set_freq(freq);

    QString text;
    text.setNum(freq);

    /*
    int stepIndex = log10(_stepSize);  // Index of char in "text" that should be underlined to indicate it's the step size
    QString prettyText;

    for(int i = 0; i < text.length(); i++) {
        if(i == stepIndex) {
            prettyText.prepend("<u>" + text[text.length() - 1 - i] + "</u>");
        } else {
            prettyText.prepend(text[text.length() - 1 - i]);
        }

        if ((i + 1) % 3 == 0)
            prettyText.prepend(".");
    }
    */

    //this->freqButton->setText(text);

    _freq = freq;

}


void vfo::set_tx_enabled(bool x)
{
    this->txEnabled = x;
    QString filename = (x ? ":resources/img/icon_tx_enabled" : ":resources/img/icon_tx_disabled");
    QPixmap pix(filename);
    QIcon icon(pix);
    this->txButton->setIcon(icon);
    this->txButton->setIconSize(QSize(50, 50));
    this->txButton->setFixedSize(QSize(50, 50));
}

void vfo::set_rx_enabled(bool x)
{
    this->rxEnabled = x;
    QString filename = (x ? ":resources/img/icon_rx_enabled" : ":resources/img/icon_rx_disabled");
    QPixmap pix(filename);
    QIcon icon(pix);
    this->rxButton->setIcon(icon);
    this->rxButton->setIconSize(QSize(50, 50));
    this->rxButton->setFixedSize(QSize(50, 50));
}

void vfo::toggle_tx_enabled()
{
    set_tx_enabled(!this->txEnabled);
}

void vfo::toggle_rx_enabled()
{
    set_rx_enabled(!this->rxEnabled);
}

bool vfo::get_tx_enabled()
{
    return this->txEnabled;
}

bool vfo::get_rx_enabled()
{
    return this->rxEnabled;
}

void vfo::run_keypad(QWidget *parent)
{
    number_keypad keypad(parent);
    keypad.setModal(true);
    if(keypad.exec() == QDialog::Accepted){
        unsigned long long freq = keypad.get_freq();
        this->set_freq(freq);
    }
}

void vfo::set_s_meter(int x)
{
    // x = 0-9 -> S0-S9
    // x = 10 -> S9+5
    // x = 11 -> S9+10
    // x = 12 -> S9+20
    // x = 13 -> S9+30

    x = std::min(x, 13);
    meter->setValue(x);
    QString labelText = "S";

    switch(x){
        case 10: labelText += "9+5"; break;
        case 11: labelText += "9+10"; break;
        case 12: labelText += "9+20"; break;
        case 13: labelText += "9+30"; break;
        case 14: labelText += "9++"; break;
        default: labelText += QString::number(x);
    };

    meterLabel->setText(labelText);
}

void vfo::set_rit(int x)
{
    rit = x;
    if(x){
        ritLabel->setStyleSheet("QLabel {color:#009900}");
    } else {
        ritLabel->setStyleSheet("QLabel {color:#808080}");
    }
}

void vfo::set_xit(int x)
{
    xit = x;
    if(x){
        xitLabel->setStyleSheet("QLabel {color:#FF0000}");
    } else {
        xitLabel->setStyleSheet("QLabel {color:#808080}");
    }
}

void vfo::increment()
{
    set_freq(_freq + _stepSize);
}

void vfo::decrement()
{
    set_freq(_freq - _stepSize);
}

void vfo::set_step_size(int step)
{
    assert (step % 10 == 0);
    _stepSize = step;
}

