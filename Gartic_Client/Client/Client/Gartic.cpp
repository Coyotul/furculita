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
    updatePlayers();
    updateLeaderboard();
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
    if (!wordChosen)
    {
        wordChosen = true;
        word = ui.wordButton_1->text();
        sendWordToServer(word);
        qDebug() << "Word selected: " << word;
        ui.wordText->setText(QString::fromStdString("Draw: ") + word);
        hideWordChoices();
    }
}

void Gartic::on_wordButton_2_clicked()
{
    if (!wordChosen)
    {
        wordChosen = true;
        word = ui.wordButton_2->text();
        sendWordToServer(word);
        qDebug() << "Word selected: " << word;
        ui.wordText->setText(QString::fromStdString("Draw: ") + word);
        hideWordChoices();
    }
}

void Gartic::on_wordButton_3_clicked()
{
    if (!wordChosen)
    {
        wordChosen = true;
        word = ui.wordButton_3->text();
        sendWordToServer(word);
        qDebug() << "Word selected: " << word;
        ui.wordText->setText(QString::fromStdString("Draw: ") + word);
        hideWordChoices();
    }
}

void Gartic::hideWordChoices()
{
    if (wordChosen == true)
    {
        ui.wordButton_1->hide();
        ui.wordButton_2->hide();
        ui.wordButton_3->hide();
    }
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
    if (event->key() == Qt::Key_K)
    {
        updatePlayers();
        updateLeaderboard();

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
        sendDrawingToServer();
    }
}

void Gartic::sendDrawingToServer()
{
    
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
    leaderboard.clear();
    int index = 0;
    for (auto& it : players)
    {
        leaderboard = leaderboard +'\n' + QString::number(++index) + ": " + it.first + " " + it.second;
    }
    ui.leaderboard->setText(leaderboard);
}

void sortPlayersByScore()
{

}

void Gartic::updatePlayers()
{
    // URL-ul către serverul de la care obținem informațiile despre jucători
    std::string url = "http://localhost:8080/getPlayers";

    // Configurația cererii GET
    cpr::Response response = cpr::Get(cpr::Url{ url });

    // Verifică dacă cererea a fost reușită
    if (response.status_code == 200) {
        // Parsarea răspunsului JSON
        crow::json::rvalue jsonData = crow::json::load(response.text);

        // Iterarea prin elementele JSON pentru a obține informațiile despre jucători
        for (const auto& player : jsonData) {
            std::string playerName = player["name"].s();
            int playerScore = player["score"].u();
            QString name = QString::fromUtf8(playerName);
            QString score = QString::number(playerScore);
            // Adaugă informațiile despre jucători în vectorul players
            players.push_back(std::make_pair(name, score));
        }
    }
    else {
        // Tratează eroarea în cazul în care cererea nu a fost reușită
        std::cerr << "Eroare la obținerea informațiilor despre jucători. Cod de stare: " << response.status_code << std::endl;
        std::cerr << "Răspunsul serverului:\n" << response.text << std::endl;
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

void Gartic::sendWordToServer(const QString& word)
{
    std::ofstream logFile("log.txt");
    std::cout.rdbuf(logFile.rdbuf());
    std::cerr.rdbuf(logFile.rdbuf());
    
    std::string url = "http://localhost:8080/wordToDraw";
    std::string wordToDraw = word.toUtf8().constData();

    cpr::Response r = cpr::Post(cpr::Url{ url }, cpr::Parameters{ {"chosenWord", wordToDraw} });

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
        cpr::Response r = cpr::Get(cpr::Url{ url }, cpr::Parameters{ {"language", chosenLanugage} });

        auto words = crow::json::load(r.text);
        std::vector<std::string> stringWords;
        for (const auto& word : words)
        {
            stringWords.push_back((std::string)word["word"]);
        }
        SetWords(stringWords[0], stringWords[1], stringWords[2]);
    }
}



void Gartic::SetWords(std::string word1,std::string word2,std::string word3)
{
    ui.wordButton_1->setText(QString::fromUtf8(word1.c_str()));
    ui.wordButton_2->setText(QString::fromUtf8(word2.c_str()));
    ui.wordButton_3->setText(QString::fromUtf8(word3.c_str()));
}

