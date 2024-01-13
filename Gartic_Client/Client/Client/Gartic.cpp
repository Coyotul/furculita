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
#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QPaintEvent>
#include <QList>
#include <QMainWindow>
#include <QtWidgets>
#include <QPixmap>
#include <QLabel>

std::ofstream f("output.out");

// At Start
Gartic::Gartic(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    scene = new QGraphicsScene(this);
    scribbleArea = new ScribbleArea;
    scene->addWidget(scribbleArea);
    ui.drawView->setScene(scene);
    currentDrawing = nullptr;
    hideInterface();
    username = "Guest";
    ui.drawView->viewport()->installEventFilter(this);
    ui.easterEgg->hide();
    ui.drawing->hide();
    ui.drawView->setMouseTracking(true);
    createActions();
    createMenus();
    setWindowTitle(tr("Scribble Application"));
    //Timer
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Gartic::getTimer);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Gartic::getTimer);
    chatUpdateTimer = new QTimer(this);
    connect(chatUpdateTimer, &QTimer::timeout, this, &Gartic::updateChat);
    chatUpdateTimer->start(1000);
}
void Gartic::penColor()
{

    QColor newColor = QColorDialog::getColor(scribbleArea->penColor());

    if (newColor.isValid())
        scribbleArea->setPenColor(newColor);
}
void Gartic::penWidth()
{
    bool ok;
    int newWidth = QInputDialog::getInt(this, tr("Scribble"),
        tr("Select pen width:"),
        scribbleArea->penWidth(), 1, 50, 1, &ok);
    if (ok)
        scribbleArea->setPenWidth(newWidth);
}
void Gartic::createActions()
{

    penColorAct = new QAction(tr("&Pen Color..."), this);
    connect(penColorAct, SIGNAL(triggered()), this, SLOT(penColor()));

    penWidthAct = new QAction(tr("Pen &Width..."), this);
    connect(penWidthAct, SIGNAL(triggered()), this, SLOT(penWidth()));

    clearScreenAct = new QAction(tr("&Clear Screen"), this);
    clearScreenAct->setShortcut(tr("Ctrl+L"));
    connect(clearScreenAct, SIGNAL(triggered()),
        scribbleArea, SLOT(clearImage()));

}
void Gartic::createMenus()
{

    optionMenu = new QMenu(tr("&Options"), this);
    optionMenu->addAction(penColorAct);
    optionMenu->addAction(penWidthAct);
    optionMenu->addSeparator();
    optionMenu->addAction(clearScreenAct);

    menuBar()->addMenu(optionMenu);

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
        //timer->start(1000);
        if (language == 2)
            ui.wordText->setText("Draw: " + word);
        else
            ui.wordText->setText("Desen: " + word);

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
        //timer->start(1000);
        if (language == 2)
            ui.wordText->setText("Draw: " + word);
        else
            ui.wordText->setText("Desen: " + word);
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
        //timer->start(1000);
        if (language == 2)
            ui.wordText->setText("Draw: " + word);
        else
            ui.wordText->setText("Desen: " + word);
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

void Gartic::showWordChoices()
{
    ui.wordButton_1->show();
    ui.wordButton_2->show();
    ui.wordButton_3->show();
}



void Gartic::on_language1_clicked()
{
    //romanian language
    language = 1;
    int languageValue = 1;
    ui.LeaderboardText->setText("Clasament");
    ui.username_text->setText("Utilizator:");
    ui.wordText->setText("Deseneaza:");
    ui.timerText->setText("Timp:");

    std::string url = "http://localhost:8080/language?language=" + std::to_string(languageValue);
    cpr::Response response = cpr::Get(cpr::Url{ url });
}

void Gartic::on_language2_clicked()
{
    //english language
    language = 2;
    int languageValue = 2;
    ui.LeaderboardText->setText("Leaderboard");
    ui.username_text->setText("Username:");
    ui.wordText->setText("Draw:");
    ui.timerText->setText("Timer:");
    std::string url = "http://localhost:8080/language?language=" + std::to_string(languageValue);
    cpr::Response response = cpr::Get(cpr::Url{ url });
}
void Gartic::getTimer()
{
    std::string url = "http://localhost:8080/getTimeLeft";
    cpr::Response response = cpr::Get(cpr::Url{ url });



    if (response.status_code == 200)
    {
        crow::json::rvalue jsonData = crow::json::load(response.text);

        int timeLeft = jsonData["timeLeft"].i();
        if (timeLeft == 60 || timeLeft == 59 || timeLeft == 58 || timeLeft == 57 || timeLeft == 56 || timeLeft == 55)
        {
            getPlayerName();
        }
        QString timerText = QString("Timer: %1").arg(timeLeft);
        ui.timerText->setText(timerText);
        if (timeLeft == 0)
        {
            scribbleArea->clearImage();
        }
    }
    else
    {
        qDebug() << "Error fetching timer value. Status code: " << response.status_code;
    }
}

void Gartic::getPlayerName()
{
    std::string url = "http://localhost:8080/getMainPlayer";
    std::string url2 = "http://localhost:8080/getWord";
    cpr::Response response = cpr::Get(cpr::Url{ url });
    cpr::Response response2 = cpr::Get(cpr::Url{ url2 });

    if (response.status_code == 200)
    {
        auto name = crow::json::load(response.text);
        std::string name1 = (std::string)name["name"];
        std::string stringUsername = username.toUtf8().constData();
        if (stringUsername == name1)
        {
            isDrawing = true;
            ui.drawing->hide();

        }
        else
        {
            auto wordToGuess = crow::json::load(response2.text);
            std::string wordToGuess2 = (std::string)wordToGuess[0]["word"];
            QString word = "";
            for (const auto& it : wordToGuess2)
            {
                word.push_back('-');
            }
            ui.wordText->setText(word);
            isDrawing = false;
            imageTimer = new QTimer(this);
            connect(imageTimer, &QTimer::timeout, this, &Gartic::downloadAndDisplayImage);
            imageTimer->start(1000);
        }
    }
    else
    {
        qDebug() << "Error fetching player name. Status code: " << response.status_code;
    }
}


void Gartic::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
    {
        if (playerLogged)
        {
            chatText = chatText + '\n' + username + ": " + ui.textBox->text();
            ui.textEdit->setText(chatText);

            if (ui.textBox->text() == "german")
            {
                ui.easterEgg->show();
            }
            sendChatToServer('\n' + username + ": " + ui.textBox->text());
            ui.textBox->clear();
            updateLeaderboard();
        }
        else
        {
            if (ui.username->text().size() > 0) {
                username = ui.username->text();
            }
            addPlayerToServer(username);
            showInterface();
            playerLogged = true;
            updateLeaderboard();
            timer->start(1000);
        }
        getWords();

    }
    QMainWindow::keyPressEvent(event);
}

bool Gartic::eventFilter(QObject* obj, QEvent* event)
{
    if (obj == ui.drawView->viewport())
    {
        if (event->type() == QEvent::MouseButtonRelease)
        {
            QImage imageData = scribbleArea->getImage();
            sendImageToServer(imageData);
        }
    }
    return QMainWindow::eventFilter(obj, event);
}
void Gartic::downloadImageFromServer()
{
    ui.wordButton_1->hide();
    ui.wordButton_2->hide();
    ui.wordButton_3->hide();

    std::string url = "http://localhost:8080/getDrawing";

    cpr::Response response = cpr::Get(cpr::Url{ url });

    if (response.status_code == 200) {
        std::ofstream file("downloaded_image.png", std::ios::binary);
        file.write(response.text.c_str(), response.text.size());
        file.close();

        qDebug() << "Imaginea a fost descărcată și salvată cu succes în downloaded_image.png.";
    }
    else {
        qDebug() << "Eroare la descărcarea imaginii. Cod de stare: " << response.status_code;
    }
}

void Gartic::displayImage(const QString& imagePath)
{
    QPixmap newPixmap(imagePath);

    if (newPixmap.isNull()) {
        qDebug() << "Eroare la încărcarea noii imagini.";
        return;
    }
    ui.drawing->show();
    ui.drawing->setPixmap(newPixmap);
}



void Gartic::sendImageToServer(const QImage& image)
{
    std::ofstream logFile("log.txt");
    std::cout.rdbuf(logFile.rdbuf());
    std::cerr.rdbuf(logFile.rdbuf());

    std::string url = "http://localhost:8080/drawing";

    QByteArray imageData;
    QBuffer buffer(&imageData);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG");
    buffer.close();

    cpr::Response r = cpr::Post(
        cpr::Url{ url },
        cpr::Header{ {"Content-Type", "application/octet-stream"} },
        cpr::Body{ imageData.data(), static_cast<size_t>(imageData.size()) });
    updateLeaderboard();

    if (r.status_code == 200) {
        std::cout << "Cererea POST a fost trimisă cu succes!\n";
        std::cout << "Răspunsul serverului:\n" << r.text << std::endl;
    }
    else {
        std::cerr << "Eroare la trimiterea cererii POST. Cod de stare: " << r.status_code << std::endl;
        std::cerr << "Răspunsul serverului:\n" << r.text << std::endl;
    }
}

void Gartic::updateChat()
{
    std::string url = "http://localhost:8080/getChat";
    cpr::Response response = cpr::Get(cpr::Url{ url });
    if (response.status_code == 200)
    {
        auto jsonData = crow::json::load(response.text);
        std::string text = jsonData["chat"].s();
        std::string stdString = chatText.toUtf8().constData();
        size_t lastNewlinePos = stdString.find_last_of("\n");
        std::string copy = stdString;
        stdString = stdString.substr(lastNewlinePos + 1);
        if (text != ('\n' + stdString) && text.size() != 0) {
            chatText += text;
            ui.textEdit->setText(chatText);
        }
    }
}

void Gartic::sendChatToServer(const QString& chat)
{
    std::string url = "http://localhost:8080/chat";
    std::string txt = chat.toUtf8().constData();
    cpr::Response r = cpr::Post(cpr::Url{ url }, cpr::Parameters{ {"chat", txt} });
    if (r.status_code == 200) {
    }
    else {
        std::cerr << "Eroare la trimiterea cererii POST. Cod de stare: " << r.status_code << std::endl;
        std::cerr << "Răspunsul serverului:\n" << r.text << std::endl;
    }
}

void Gartic::sendGuessedWordToServer(const QString& word)
{
    /*std::string url = "http://localhost:8080/guessedWord";
    std::string wordStr = word.toUtf8().constData();
    std::string txt = wordStr;

    cpr::Response r = cpr::Post(
        cpr::Url{ url },
        cpr::Parameters{
            {"word", txt},
            {"name", username.toStdString()}
        }
    );

    if (r.status_code == 200)
    {
    }
    else {
        std::cerr << "Eroare la trimiterea cererii POST. Cod de stare: " << r.status_code << std::endl;
        std::cerr << "Răspunsul serverului:\n" << r.text << std::endl;
    }*/
}

void Gartic::sortPlayersByScore()
{
    std::sort(players.begin(), players.end(),
        [](const auto& a, const auto& b) { return a.second < b.second; });
}

void Gartic::downloadAndDisplayImage()
{
    if (!isDrawing)
    {
        downloadImageFromServer();
        displayImage("downloaded_image.png");
    }
    else if (!playerWillBeDrawing)
    {
        playerWillBeDrawing = true;
        getWords();
        showWordChoices();
        ui.drawing->hide();
    }
}


void Gartic::hideInterface()
{
    ui.drawView->hide();
    ui.textBox->hide();
    ui.textEdit->hide();
    ui.wordButton_1->hide();
    ui.wordButton_2->hide();
    ui.wordButton_3->hide();
    ui.wordText->hide();
    ui.leaderboard->hide();
    ui.LeaderboardText->hide();
    ui.timerText->hide();
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
    ui.timerText->show();
    ui.leaderboard->show();
    ui.LeaderboardText->show();

    ui.username_text->hide();
    ui.username->hide();
    ui.language1->hide();
    ui.language2->hide();
}
void Gartic::updateLeaderboard()
{
    leaderboard.clear();
    ui.leaderboard->setText(" ");
    int index = 0;
    updatePlayers();
    sortPlayersByScore();
    for (auto& it : players)
    {
        leaderboard = leaderboard + '\n' + QString::number(++index) + ": " + it.first + " " + it.second;
    }
    ui.leaderboard->setText(leaderboard);
}

void Gartic::updatePlayers()
{
    // URL-ul către serverul de la care obținem informațiile despre jucători
    std::string url = "http://localhost:8080/getPlayers";

    // Configurația cererii GET
    cpr::Response response = cpr::Get(cpr::Url{ url });
    players.clear();
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
        getPlayerName();
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

void Gartic::SetWords(std::string word1, std::string word2, std::string word3)
{
    ui.wordButton_1->setText(QString::fromUtf8(word1.c_str()));
    ui.wordButton_2->setText(QString::fromUtf8(word2.c_str()));
    ui.wordButton_3->setText(QString::fromUtf8(word3.c_str()));
}