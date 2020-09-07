#include "mainwindow.h"
#include "ui_mainwindow.h"

using json = nlohmann::json;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Confirm we have status / control comms with PL
    this->_status = new StatusRegs(this, "/dev/statusregs");

    // Initialise VFOs
    vfoA = new vfo(
        ui->button_A_freq,
        ui->button_A_rx,
        ui->button_A_tx,
        ui->label_A_fc,
        ui->button_A_fc,
        ui->label_A_bw,
        ui->button_A_bw,
        ui->button_A_mode,
        ui->label_A_meter,
        ui->button_A_meterScale,
        ui->meter_A,
        ui->label_A_rit,
        ui->label_A_xit,
        ui->statusbar,
        "/dev/fft_dma",
        ui->A_FFT,
        ui->A_waterfall,
        this->_status
    );
    /*

    vfoB = new vfo(
        ui->button_B_freq,
        ui->button_B_rx,
        ui->button_B_tx,
        ui->label_B_fc,
        ui->button_B_fc,
        ui->label_B_bw,
        ui->button_B_bw,
        ui->button_B_mode,
        ui->label_B_meter,
        ui->button_B_meterScale,
        ui->meter_B,
        ui->label_B_rit,
        ui->label_B_xit,
        ui->statusbar
    );*/

    vfoA->set_freq(28e6);

    _audio = new audio_handler("/dev/i2c-2", 0x38);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete(_audio);
    delete(vfoA);
}


void MainWindow::on_button_aboutQt_clicked()
{
    QMessageBox::aboutQt(this, "Qt information");
}

void MainWindow::on_button_A_freq_clicked()
{
    vfoA->run_keypad(this);
}

void MainWindow::on_button_A_mode_clicked()
{
    ;  // TODO
}

void MainWindow::on_button_A_rx_clicked()
{
    if(vfoA->get_rx_enabled()) {
        // Only disable RX if the other RX is enabled - don't want a deaf receiver!
        if(vfoB->get_rx_enabled()) {
           vfoA->set_rx_enabled(0);
        } else {
            ui->statusbar->showMessage("Can't disable both receivers", 3000);
        }
    } else {
        vfoA->set_rx_enabled(1);
    }
}

void MainWindow::on_button_A_tx_clicked()
{
    vfoA->toggle_tx_enabled();
    if(vfoA->get_tx_enabled()){
        // Musn't have both set to TX
        vfoB->set_tx_enabled(0);
    }
}

void MainWindow::on_button_B_rx_clicked()
{
    if(vfoB->get_rx_enabled()) {
        // Only disable RX if the other RX is enabled - don't want a deaf receiver!
        if(vfoA->get_rx_enabled()) {
           vfoB->set_rx_enabled(0);
        } else {
            ui->statusbar->showMessage("Can't disable both receivers", 3000);
        }

    } else {
        vfoB->set_rx_enabled(1);
    }
}

void MainWindow::on_button_B_tx_clicked()
{
    vfoB->toggle_tx_enabled();
    if(vfoB->get_tx_enabled()){
        // Musn't have both set to TX
        vfoA->set_tx_enabled(0);
    }
}

void MainWindow::on_button_B_freq_clicked()
{
    vfoB->run_keypad(this);
}

void MainWindow::on_button_A_meterScale_clicked()
{
    ;
}
