#include "number_keypad.h"
#include "ui_number_keypad.h"

number_keypad::number_keypad(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::number_keypad)
{
    ui->setupUi(this);
    this->freqString = "";
    ui->label_freq->setText(freqString);
}

unsigned long long number_keypad::get_freq()
{
    return(this->freq);
}

number_keypad::~number_keypad()
{
    delete ui;
}


void number_keypad::on_button_1_clicked()
{
    this->freqString += "1";
    ui->label_freq->setText(freqString);
}

void number_keypad::on_button_2_clicked()
{
    this->freqString += "2";
    ui->label_freq->setText(freqString);
}

void number_keypad::on_button_3_clicked()
{
    this->freqString += "3";
    ui->label_freq->setText(freqString);
}

void number_keypad::on_button_4_clicked()
{
    this->freqString += "4";
    ui->label_freq->setText(freqString);
}

void number_keypad::on_button_5_clicked()
{
    this->freqString += "5";
    ui->label_freq->setText(freqString);
}

void number_keypad::on_button_6_clicked()
{
    this->freqString += "6";
    ui->label_freq->setText(freqString);
}

void number_keypad::on_button_7_clicked()
{
    this->freqString += "7";
    ui->label_freq->setText(freqString);
}

void number_keypad::on_button_8_clicked()
{
    this->freqString += "8";
    ui->label_freq->setText(freqString);
}

void number_keypad::on_button_9_clicked()
{
    this->freqString += "9";
    ui->label_freq->setText(freqString);
}

void number_keypad::on_button_0_clicked()
{
    this->freqString += "0";
    ui->label_freq->setText(freqString);
}


void number_keypad::on_button_DP_clicked()
{
    this->freqString += ".";
    ui->label_freq->setText(freqString);
}

void number_keypad::on_button_BS_clicked()
{
    this->freqString.chop(1);
    ui->label_freq->setText(freqString);
}

void number_keypad::on_button_H_clicked()
{
    update_freq(this->freqString.toFloat(), 0);
}

void number_keypad::on_button_K_clicked()
{
    update_freq(this->freqString.toFloat(), 3);
}

void number_keypad::on_button_M_clicked()
{
    update_freq(this->freqString.toFloat(), 6);
}

void number_keypad::on_button_G_clicked()
{
    update_freq(this->freqString.toFloat(), 9);
}

void number_keypad::update_freq(float mantissa, int exponent){

    this->freq = mantissa * pow(10, exponent);

    qDebug() << this->freq;
    this->accept();
}
