#include "Gartic.h"
#include <QKeyEvent>
#include <QString>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <iostream>
#include <cpr/cpr.h>
#include <crow.h>
#include <fstream>


std::ofstream f("output.out");

// At Start
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
    updateLeaderboard();
    updatePlayersScore();
    updatePlayersUsername();
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

void Gartic::on_language1_clicked()
{
    language = 1;
    int languageValue = 1;

    std::string url = "http://localhost:8080/language?language=" + std::to_string(languageValue);

    cpr::Response response = cpr::Get(cpr::Url{ url });

}

void Gartic::on_language2_clicked()
{
    language = 2;
    int languageValue = 2;

    std::string url = "http://localhost:8080/language?language=" + std::to_string(languageValue);

    cpr::Response response = cpr::Get(cpr::Url{ url });
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
            }
            addPlayerToServer(username);
            showInterface();
            playerLogged = true;
        }
        getWords();
    }

    QMainWindow::keyPressEvent(event);
}


void Gartic::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        isDrawing = false;
        lastMousePos = event->pos();
    }
}

void Gartic::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && ui.drawView->rect().contains(event->pos()))
    {
        std::cout << event->pos().x() << " " << event->pos().y() << '\n';
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
    ui.leaderboard->hide();
    ui.LeaderboardText->hide();

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
    ui.leaderboard->show(); 
    ui.LeaderboardText->show();

    ui.username_text->hide();
    ui.username->hide();
}

void Gartic::updateLeaderboard()
{
    //TODO: implement all logic
    //for(auto it& player)
    leaderboard = username + " " + "100";
    ui.leaderboard->setText(leaderboard);
}

void Gartic::updatePlayersUsername()
{ 
    //vezi ca e un singur extract pentru amandoua, ti l schimbi tu dupa sau il folosesti unde iti trebuie
    //crapa mereu, e greu rau programu sa mor eu
    /*std::vector<std::pair<std::string, uint16_t>> nameAndScore;
    cpr::Response response = cpr::Get(cpr::Url{ "http://localhost:8080/getPlayersName" });
    auto players = crow::json::load(response.text);

    for (const auto& player : players) {
        
        std::string playerName = player["name"].s();  
        uint16_t playerScore = player["score"].u();  

        nameAndScore.push_back(std::make_pair(playerName, playerScore));
    }*/
}

void Gartic::updatePlayersScore()
{
    for (auto& it : playersScore)
    {
        //TODO: extract playersScore from server
    }
}

void Gartic::addPlayerToServer(const QString& playerName)
{
    std::ofstream logFile("log.txt");
    std::cout.rdbuf(logFile.rdbuf()); 
    std::cerr.rdbuf(logFile.rdbuf()); 

    // URL-ul către serverul la care trimitem cererea POST
    std::string url = "http://localhost:8080/addPlayer";

    // Cuvântul pe care vrem să-l trimitem
    std::string cuvant = playerName.toUtf8().constData();
    
    std::cout << "Converted player name: " << cuvant << std::endl;

    // Configurația cererii
    cpr::Response r = cpr::Post(cpr::Url{ url }, cpr::Parameters{ {"username", cuvant} });

    // Verifică dacă cererea a fost reușită
    if (r.status_code == 200) {
        std::cout << "Cererea POST a fost trimisă cu succes!\n";
        std::cout << "Răspunsul serverului:\n" << r.text << std::endl;
    }
    else {
        std::cerr << "Eroare la trimiterea cererii POST. Cod de stare: " << r.status_code << std::endl;
        std::cerr << "Răspunsul serverului:\n" << r.text << std::endl;
    } 
}

void Gartic::getWords()
{
    if (isPlayerAllowedToDraw)
    {
        std::ofstream logFile("log.txt");
        std::cout.rdbuf(logFile.rdbuf());
        std::cerr.rdbuf(logFile.rdbuf());

        // URL-ul către serverul la care trimitem cererea POST
        std::string url = "http://localhost:8080/words";

        std::string chosenLanugage;
        if (language == 1)
            chosenLanugage = "1";
        else chosenLanugage = "2";

        // Configurația cererii
        cpr::Response r = cpr::Get(cpr::Url{ url }, cpr::Parameters{ {"lang", chosenLanugage} });

        // Verifică dacă cererea a fost reușită
        if (r.status_code == 200) {
            std::cout << "Cererea POST a fost trimisă cu succes!\n";
            std::cout << "Răspunsul serverului:\n" << r.text << std::endl;
        }
        else {
            std::cerr << "Eroare la trimiterea cererii POST. Cod de stare: " << r.status_code << std::endl;
            std::cerr << "Răspunsul serverului:\n" << r.text << std::endl;
        }
    }
}

void Gartic::SetWords(std::string word1,std::string word2,std::string word3)
{
    ui.wordButton_1->setText(QString::fromUtf8(word1.c_str()));
    ui.wordButton_2->setText(QString::fromUtf8(word2.c_str()));
    ui.wordButton_3->setText(QString::fromUtf8(word3.c_str()));
}

