#include "Gartic.h"
#include <QKeyEvent>
#include <QString>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <iostream>
#include <cpr/cpr.h>

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
    ui.drawView->viewport()->installEventFilter(this);

}
bool Gartic::eventFilter(QObject* obj, QEvent* event)
{
    if (obj == ui.drawView->viewport())
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
            if (mouseEvent->button() == Qt::LeftButton)
            {
                ui.drawView->setFocus();  // Setează focusul pe widget-ul de desen

                QPainterPath path;
                path.moveTo(ui.drawView->mapToScene(mouseEvent->pos()));

                QGraphicsPathItem* drawnPath = new QGraphicsPathItem(path);
                scene->addItem(drawnPath);

                currentDrawing = drawnPath;

                return true;  // Consumă evenimentul
            }
        }
        else if (event->type() == QEvent::MouseButtonRelease)
        {
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
            if (mouseEvent->button() == Qt::LeftButton)
            {
                currentDrawing = nullptr;

                return true;  // Consumă evenimentul
            }
        }
        else if (event->type() == QEvent::MouseMove)
        {
            if (currentDrawing)
            {
                QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
                if (ui.drawView->rect().contains(mouseEvent->pos()))
                {
                    QPainterPath path = currentDrawing->path();
                    path.lineTo(ui.drawView->mapToScene(mouseEvent->pos()));
                    currentDrawing->setPath(path);
                }
                else
                {
                    currentDrawing = nullptr;
                }

                return true;  // Consumă evenimentul
            }
        }
    }

    return QMainWindow::eventFilter(obj, event);
}


Gartic::~Gartic()
{}

void Gartic::on_wordButton_1_clicked()
{
    word = ui.wordButton_1->text();
    qDebug() << "Word selected: " << word;
    ui.wordText->setText(QString::fromStdString("Draw: ") + word);
}

void Gartic::on_wordButton_2_clicked()
{
    word = ui.wordButton_2->text();
    ui.wordText->setText(QString::fromStdString("Draw: ") + word);
}

void Gartic::on_wordButton_3_clicked()
{
    word = ui.wordButton_3->text();
    ui.wordText->setText(QString::fromStdString("Draw: ") + word);
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
            if (ui.username->text().size() > 0) {
                username = ui.username->text();
                //addPlayerToServer(username);
            }
            showInterface();
            playerLogged = true;
        }
    }

    QMainWindow::keyPressEvent(event);
}


void Gartic::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        isDrawing = false;
    }
}

void Gartic::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && ui.drawView->rect().contains(event->pos()))
    {
        ui.drawView->setFocus();

        // Adaugă un nou PainterPath la vectorul de linii
        QPainterPath newPath;
        lastMousePos = ui.drawView->mapToScene(event->pos());
        newPath.moveTo(lastMousePos);
        lines.push_back(newPath);

        isDrawing = true;
    }
}

void Gartic::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    for (const auto& path : lines)
    {
        painter.drawPath(path);
    }

    // Desenează linia curentă dacă se află în proces de desenare
    if (isDrawing)
    {
        QPainterPath currentPath;
        currentPath.moveTo(lastMousePos);
        currentPath.lineTo(ui.drawView->mapToScene(ui.drawView->mapFromGlobal(QCursor::pos())));
        painter.drawPath(currentPath);
    }
}


void Gartic::hideInterface()
{
    //We are gonna hide all buttons until the player logs in
    ui.drawView->hide();
    ui.textBox->hide();
    ui.textEdit->hide();
    ui.wordButton_1->hide();
    ui.wordButton_2->hide();
    ui.wordButton_3->hide();
    ui.wordText->hide();

    ui.username_text->show();
    ui.username->show();    
}

void Gartic::showInterface()
{
    ui.drawView->show();
    ui.textBox->show();
    ui.textEdit->show();
    ui.centralWidget->show();
    ui.wordButton_1->show();
    ui.wordButton_2->show();
    ui.wordButton_3->show();
    ui.wordText->show();

    ui.username_text->hide();
    ui.username->hide();
}

//void Gartic::addPlayerToServer(const QString& playerName)
//{
//    std::string playerNameStd = playerName.toStdString();
//    std::string url = "";
//    cpr::Response response = cpr::Post(
//    cpr::Url{url},
//    cpr::Parameters{{"playerName", playerNameStd}}
//    );
//}

void Gartic::SetWords(std::string word1,std::string word2,std::string word3)
{
    ui.wordButton_1->setText(QString::fromStdString(word1));
    ui.wordButton_2->setText(QString::fromStdString(word2));
    ui.wordButton_3->setText(QString::fromStdString(word3));
}

