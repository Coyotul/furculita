#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Gartic.h"
#include <QtWidgets/QMainWindow>
#include <QTextEdit>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <cpr/cpr.h>

class Gartic : public QMainWindow
{
    Q_OBJECT

public:
    Gartic(QWidget *parent = nullptr);
    ~Gartic();
    QGraphicsPathItem* currentDrawing;

    void SetWords(std::string word1, std::string word2, std::string word3);

private slots:
    void on_wordButton_1_clicked();
    void on_wordButton_2_clicked();
    void on_wordButton_3_clicked();
    void on_language1_clicked();
    void on_language2_clicked();

    //For methods
private:
    Ui::GarticClass ui;
   
    void keyPressEvent(QKeyEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    bool eventFilter(QObject* obj, QEvent* event);
    void hideInterface();
    void showInterface();
    void updateLeaderboard();
    void updatePlayersUsername();
    void updatePlayersScore();
    void addPlayerToServer(const QString& playerName);

    QGraphicsScene* scene;
    QGraphicsRectItem* drawRectItem;


    //For var
private:
    QString username;
    QString chatText;
    QString leaderboard;
    QString word;
    int language=1;
    std::vector<QString> playersUsername;
    std::vector<QString> playersScore;
    bool playerLogged = false;
    bool isDrawing = false;
    QPointF lastMousePos;
    std::vector<QPainterPath> lines;

};
