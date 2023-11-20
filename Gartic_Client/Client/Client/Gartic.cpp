#include "Gartic.h"
#include <QKeyEvent>
#include <QString>


Gartic::Gartic(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
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
        chatText = chatText + '\n' + ui.textBox->text();
        ui.chat->setText(chatText);
        ui.textBox->clear();
    }

    QMainWindow::keyPressEvent(event);
}
