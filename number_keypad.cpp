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
    return(this->freqString.toULongLong());
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
    update_freq(1);
}

void number_keypad::on_button_K_clicked()
{
    update_freq(3);
}

void number_keypad::on_button_M_clicked()
{
    update_freq(6);
}

void number_keypad::on_button_G_clicked()
{
    update_freq(9);
}

long number_keypad::update_freq(int exponent){

    // Search for decimal point
    int dp_index = this->freqString.indexOf(".");
    int offset = 0;


    if(dp_index != -1){
        // Decimal point found
        offset = this->freqString.length() - dp_index - 1;
        this->freqString.remove(dp_index, 1);
    }


    // Pad zeros on the end
    for(int i = 0; i < (exponent - offset); i++)
        this->freqString += "0";

    qDebug() << freqString;
    this->accept();
}
