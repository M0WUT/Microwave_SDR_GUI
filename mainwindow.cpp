#include "mainwindow.h"
#include "ui_mainwindow.h"

using json = nlohmann::json;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    vfoA = new vfo(
        ui->button_A_freq,
        ui->button_A_rx,
        ui->button_A_tx,
        ui->button_A_fc,
        ui->button_A_bw,
        ui->button_A_mode
    );

    vfoB = new vfo(
        ui->button_B_freq,
        ui->button_B_rx,
        ui->button_B_tx,
        ui->button_B_fc,
        ui->button_B_bw,
        ui->button_B_mode
    );


    ui->statusbar->showMessage("Main window loaded successfully", 5000);

    /*
    // Read variables that will only be set once per boot
    FILE *statusFile_p;
    statusFile_p = fopen("/dev/status", "rw");

    if(statusFile_p == NULL){
        QMessageBox::critical(this, "Fatal Error", "Could not find /dev/status");
        QApplication::quit();
    }

    fclose(statusFile_p);
    std::ifstream i("/dev/status");
    json j;
    i >> j;
    double x = j["bitstreamVersion"];
    ui->Button_bitstreamVersion->setNum(x);*/





}

MainWindow::~MainWindow()
{
    delete ui;
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
