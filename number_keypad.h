#ifndef NUMBER_KEYPAD_H
#define NUMBER_KEYPAD_H

#include <QDialog>
#include <QDebug>

namespace Ui {
class number_keypad;
}

class number_keypad : public QDialog
{
    Q_OBJECT

public:
    explicit number_keypad(QWidget *parent = nullptr);
    unsigned long long get_freq();
    ~number_keypad();

private slots:

    void on_button_1_clicked();

    void on_button_2_clicked();

    void on_button_3_clicked();

    void on_button_G_clicked();

    void on_button_4_clicked();

    void on_button_5_clicked();

    void on_button_6_clicked();

    void on_button_M_clicked();

    void on_button_7_clicked();

    void on_button_8_clicked();

    void on_button_9_clicked();

    void on_button_K_clicked();

    void on_button_DP_clicked();

    void on_button_0_clicked();

    void on_button_BS_clicked();

    void on_button_H_clicked();

private:
    Ui::number_keypad *ui;
    QString freqString;
    long update_freq(int exponent);
};

#endif // NUMBER_KEYPAD_H
