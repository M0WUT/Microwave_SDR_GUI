#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <stdio.h>
#include <fstream>
#include "src/json/json.hpp"
#include <QMessageBox>
#include <QDebug>
#include "vfo.h"
#include "number_keypad.h"
#include <QFontDatabase>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_button_aboutQt_clicked();

    void on_button_A_mode_clicked();

    void on_button_A_freq_clicked();

    void on_button_A_rx_clicked();

    void on_button_A_tx_clicked();

    void on_button_B_rx_clicked();

    void on_button_B_tx_clicked();

    void on_button_B_freq_clicked();

private:
    Ui::MainWindow *ui;
    vfo *vfoA;
    vfo *vfoB;

};
#endif // MAINWINDOW_H
