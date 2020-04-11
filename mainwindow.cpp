#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "number_keypad.h"

using json = nlohmann::json;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    ui->label_bitstreamVersion->setNum(x);





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
    number_keypad keypad(this);
    keypad.setModal(true);
    keypad.exec();
}

void MainWindow::on_button_A_mode_clicked()
{
    ;
}
