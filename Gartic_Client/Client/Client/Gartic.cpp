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
    drawRectItem = new QGraphicsRectItem(0, 0, 600, 600); 
    scene->addItem(drawRectItem);
    ui.drawView->setScene(scene); 
    currentDrawing = nullptr;
    hideInterface();
    username = "Guest";
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
        if (playerLogged)
        {
            chatText = chatText + '\n' + username + ": " + ui.textBox->text();
            ui.textEdit->setText(chatText);
            ui.textBox->clear();
        }
        else
        {
            username = ui.username->text();
            showInterface();
            playerLogged = true;
        }
    }

    QMainWindow::keyPressEvent(event);
}

void Gartic::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        QPainterPath path;
        path.moveTo(event->pos());

        QGraphicsPathItem* drawnPath = new QGraphicsPathItem(path);
        scene->addItem(drawnPath);

        currentDrawing = drawnPath;
    }
}

void Gartic::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton && currentDrawing)
    {
        QPainterPath path = currentDrawing->path();
        path.lineTo(event->pos());
        currentDrawing->setPath(path);
    }
}

void Gartic::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        currentDrawing = nullptr;
    }
}

void Gartic::hideInterface()
{
    //We are gonna hide all buttons until the player logs in
    ui.drawView->hide();
    ui.textBox->hide();
    ui.textEdit->hide();
    ui.wordButton1->hide();
    ui.wordButton_2->hide();
    ui.wordButton_3->hide();
    ui.username_text->show();
    ui.username->show();    
}

void Gartic::showInterface()
{
    ui.drawView->show();
    ui.textBox->show();
    ui.textEdit->show();
    ui.centralWidget->show();
    ui.wordButton1->show();
    ui.wordButton_2->show();
    ui.wordButton_3->show();
    ui.username_text->hide();
    ui.username->hide();
}

