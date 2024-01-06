#pragma once

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
    bool isDrawing = true;

 protected:
    //void closeEvent(QCloseEvent* event) override;

private slots:
    void on_wordButton_1_clicked();
    void on_wordButton_2_clicked();
    void on_wordButton_3_clicked();
    void on_language1_clicked();
    void on_language2_clicked();
    //void open();
    //void save();
    void penColor();
    void penWidth();
    //void about();
    //For methods
private:
    // Will tie user actions to functions
    void createActions();
    void createMenus();
    // Will check if changes have occurred since last save
    //bool maybeSave();
    // Opens the Save dialog and saves
    //bool saveFile(const QByteArray& fileFormat);
    // What we'll draw on
    ScribbleArea* scribbleArea;
    // The menu widgets
    QMenu* saveAsMenu;
    QMenu* fileMenu;
    QMenu* optionMenu;
    QMenu* helpMenu;
    // All the actions that can occur
    QAction* openAct;
    // Actions tied to specific file formats
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
    /*void paintEvent(QPaintEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    bool eventFilter(QObject* obj, QEvent* event);*/
    void hideInterface();
    void showInterface();
    void hideWordChoices();
    void updateLeaderboard();
    void updatePlayers();
    void addPlayerToServer(const QString& playerName);
    void getWords();
    void sendWordToServer(const QString& word);
    void sendImageToServer(const QImage& imageData);
    void updateChat();
    void sendChatToServer(const QString& chat);
    void getTimer();
    //void sortPlayersByScore();
    QGraphicsScene* scene;
    QLabel* timerLabel;

   //For var
private:
    QString username;
    QString chatText;
    QString leaderboard;
    QString word;
    bool wordChosen = false;
    int language=1;
    std::vector<std::pair<QString,QString>> players;
    bool playerLogged = false;
    QPointF lastMousePos;
    std::vector<QPainterPath> lines;
    bool isPlayerAllowedToDraw = true;
    QPainterPath currentPath;

    QTimer* timer;
    
};
