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
};
