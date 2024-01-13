#pragma once

#define EMPTY_CHAT ""

#include <QtWidgets/QMainWindow>
#include "ui_Gartic.h"
#include <QtWidgets/QMainWindow>
#include <QTextEdit>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <cpr/cpr.h>
#include "scribblearea.h"

class Gartic : public QMainWindow
{
    Q_OBJECT

 public:
    Gartic(QWidget *parent = nullptr);
    ~Gartic();
    QGraphicsPathItem* currentDrawing;
    void SetWords(std::string word1, std::string word2, std::string word3);
    void downloadImageFromServer();
    void displayImage(const QString& imagePath);
    bool isDrawing = false;
 protected:
private slots:
    void on_wordButton_1_clicked();
    void on_wordButton_2_clicked();
    void on_wordButton_3_clicked();
    void on_language1_clicked();
    void on_language2_clicked();
    void penColor();
    void penWidth();
private:
    void createActions();
    void createMenus();
    ScribbleArea* scribbleArea;
    QMenu* saveAsMenu;
    QMenu* fileMenu;
    QMenu* optionMenu;
    QMenu* helpMenu;
    QAction* openAct;
    QList<QAction*> saveAsActs;
    QAction* exitAct;
    QAction* penColorAct;
    QAction* penWidthAct;
    QAction* printAct; 
    QAction* clearScreenAct;
    QAction* aboutAct;
    QAction* aboutQtAct;
    Ui::GarticClass ui;
    void keyPressEvent(QKeyEvent* event);
    bool eventFilter(QObject* obj, QEvent* event);
    void hideInterface();
    void showInterface();
    void hideWordChoices();
    void showWordChoices();
    void updateLeaderboard();
    void updatePlayers();
    void addPlayerToServer(const QString& playerName);
    void getWords();
    void sendWordToServer(const QString& word);
    void sendImageToServer(const QImage& imageData);
    void sendGuessedWordToServer(const QString& word);
    void updateChat();
    void sendChatToServer(const QString& chat);
    void getTimer();
    void getPlayerName();
    void sortPlayersByScore();
    void downloadAndDisplayImage();
    QGraphicsScene* scene;
    QLabel* timerLabel;

   //For var
private:
    QString username;
    QString chatText=EMPTY_CHAT;
    QString leaderboard;
    QString word;
    bool wordChosen = false;
    int language=1;
    std::vector<std::pair<QString,QString>> players;
    bool playerLogged = false;
    QPointF lastMousePos;
    std::vector<QPainterPath> lines;
    bool isPlayerAllowedToDraw = true;
    bool playerWillBeDrawing = false;
    QPainterPath currentPath;

    QTimer* timer;
    QTimer* chatUpdateTimer;
    QTimer* imageTimer;
};