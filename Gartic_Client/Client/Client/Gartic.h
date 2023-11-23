#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Gartic.h"
#include <QtWidgets/QMainWindow>
#include <QTextEdit>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>

class Gartic : public QMainWindow
{
    Q_OBJECT

public:
    Gartic(QWidget *parent = nullptr);
    ~Gartic();
    QGraphicsPathItem* currentDrawing;

    //For methods
private:
    Ui::GarticClass ui;
    void on_wordButton_1_clicked();
    void on_wordButton_2_clicked();
    void on_wordButton_3_clicked();
    void keyPressEvent(QKeyEvent* event); // Adaugăm o funcție pentru gestionarea evenimentelor de tastatură
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void hideInterface();
    void showInterface();



    QGraphicsScene* scene;
    QGraphicsRectItem* drawRectItem;



    //For var
private:
    QString chatText;
};
