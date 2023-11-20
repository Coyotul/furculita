#include "Gartic.h"
#include <QKeyEvent>
#include <QString>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>


Gartic::Gartic(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    scene = new QGraphicsScene(this);
    drawRectItem = new QGraphicsRectItem(0, 0, 600, 600);  // Poți schimba dimensiunile
    scene->addItem(drawRectItem);
    ui.drawView->setScene(scene);  // Asigură-te că este numele corect al QGraphicsView-
    currentDrawing = nullptr;

}

Gartic::~Gartic()
{}

void Gartic::on_wordButton_1_clicked()
{

}

void Gartic::on_wordButton_2_clicked()
{

}

void Gartic::on_wordButton_3_clicked()
{

}

void Gartic::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
    {
        chatText = chatText + '\n' +"George" + ": " + ui.textBox->text();
        ui.textEdit->setText(chatText);
        ui.textBox->clear();
    }

    QMainWindow::keyPressEvent(event);
}

void Gartic::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        // Creează un nou obiect de desenare pe scenă
        QPainterPath path;
        path.moveTo(event->pos());

        // Adaugă un nou obiect de desenare în scenă
        QGraphicsPathItem* drawnPath = new QGraphicsPathItem(path);
        scene->addItem(drawnPath);

        // Salvează obiectul de desenare pentru a continua linia
        currentDrawing = drawnPath;
    }
}

void Gartic::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton && currentDrawing)
    {
        // Adaugă segmente la calea obiectului de desenare pe măsură ce mouse-ul se mișcă
        QPainterPath path = currentDrawing->path();
        path.lineTo(event->pos());
        currentDrawing->setPath(path);
    }
}

void Gartic::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        // Resetarea obiectului de desenare după ce butonul mouse-ului este eliberat
        currentDrawing = nullptr;
    }
}

