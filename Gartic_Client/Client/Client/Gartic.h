#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Gartic.h"
#include <QtWidgets/QMainWindow>
#include <QTextEdit>

class Gartic : public QMainWindow
{
    Q_OBJECT

public:
    Gartic(QWidget *parent = nullptr);
    ~Gartic();

    //For methods
private:
    Ui::GarticClass ui;
    void on_wordButton_1_clicked();
    void on_wordButton_2_clicked();
    void on_wordButton_3_clicked();
    void keyPressEvent(QKeyEvent* event); // Adaugăm o funcție pentru gestionarea evenimentelor de tastatură


    //For var
private:
    QString chatText;
};
