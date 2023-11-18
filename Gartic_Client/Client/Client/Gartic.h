#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Gartic.h"

class Gartic : public QMainWindow
{
    Q_OBJECT

public:
    Gartic(QWidget *parent = nullptr);
    ~Gartic();

private:
    Ui::GarticClass ui;
    void on_wordButton_1_clicked();
    void on_wordButton_2_clicked();
    void on_wordButton_3_clicked();
};
