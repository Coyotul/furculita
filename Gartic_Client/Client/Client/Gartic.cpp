#include "Gartic.h"
#include <QKeyEvent>

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
        ui.chat->setText(ui.textBox->text());
    }

    QMainWindow::keyPressEvent(event); // Transmiti evenimentul mai departe pentru a gestiona comportamentul implicit al tastelor
}
