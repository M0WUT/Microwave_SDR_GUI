#include "vfo.h"

vfo::vfo(
    QPushButton *freqButton,
    QPushButton *rxButton,
    QPushButton *txButton,
    QPushButton *fcButton,
    QPushButton *bwButton,
    QPushButton *modeButton
)
{
    // Copy GUI references into self
    this->freqButton = freqButton;
    this->rxButton = rxButton;
    this->txButton = txButton;
    this->fcButton = fcButton;
    this->bwButton = bwButton;
    this->modeButton = modeButton;

    this->set_rx_enabled(1);
    this->set_tx_enabled(0);

    this->set_freq(100e6);

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
    freq = std::min(freq, MAX_FREQ);
    freq = std::max(freq, MIN_FREQ);
    this->freq = (freq / 10) * 10;  // Round to 10Hz
    QString text;
    text.setNum(freq);
    int originalLength = text.length();
    for(int i = 3; i < originalLength; i += 3){
        text.insert(originalLength - i, '.');
    }

    text.chop(1);

    this->freqButton->setText(text);

}

void vfo::set_freq(QString freq)
{
    this->set_freq(freq.toULongLong());
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

