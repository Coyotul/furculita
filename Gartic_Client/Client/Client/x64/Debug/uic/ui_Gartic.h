/********************************************************************************
** Form generated from reading UI file 'Gartic.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GARTIC_H
#define UI_GARTIC_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GarticClass
{
public:
    QWidget *centralWidget;
    QLineEdit *textBox;
    QPushButton *wordButton_1;
    QPushButton *wordButton_2;
    QPushButton *wordButton_3;
    QTextEdit *textEdit;
    QGraphicsView *drawView;
    QLineEdit *username;
    QLabel *username_text;
    QLabel *logo;
    QLabel *wordText;
    QMenuBar *menuBar;
    QMenu *menuGartic;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *GarticClass)
    {
        if (GarticClass->objectName().isEmpty())
            GarticClass->setObjectName("GarticClass");
        GarticClass->resize(653, 725);
        GarticClass->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        centralWidget = new QWidget(GarticClass);
        centralWidget->setObjectName("centralWidget");
        textBox = new QLineEdit(centralWidget);
        textBox->setObjectName("textBox");
        textBox->setGeometry(QRect(30, 630, 201, 21));
        wordButton_1 = new QPushButton(centralWidget);
        wordButton_1->setObjectName("wordButton_1");
        wordButton_1->setGeometry(QRect(30, 10, 75, 24));
        wordButton_2 = new QPushButton(centralWidget);
        wordButton_2->setObjectName("wordButton_2");
        wordButton_2->setGeometry(QRect(100, 10, 75, 24));
        wordButton_3 = new QPushButton(centralWidget);
        wordButton_3->setObjectName("wordButton_3");
        wordButton_3->setGeometry(QRect(170, 10, 75, 24));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(30, 510, 201, 111));
        drawView = new QGraphicsView(centralWidget);
        drawView->setObjectName("drawView");
        drawView->setGeometry(QRect(10, 50, 641, 451));
        username = new QLineEdit(centralWidget);
        username->setObjectName("username");
        username->setGeometry(QRect(260, 220, 113, 21));
        username_text = new QLabel(centralWidget);
        username_text->setObjectName("username_text");
        username_text->setGeometry(QRect(130, 200, 121, 61));
        QFont font;
        font.setFamilies({QString::fromUtf8("Terminal")});
        font.setPointSize(11);
        font.setItalic(false);
        username_text->setFont(font);
        logo = new QLabel(centralWidget);
        logo->setObjectName("logo");
        logo->setGeometry(QRect(260, -10, 111, 61));
        logo->setPixmap(QPixmap(QString::fromUtf8(":/Gartic/gartic_logo_125px.png")));
        wordText = new QLabel(centralWidget);
        wordText->setObjectName("wordText");
        wordText->setGeometry(QRect(440, 20, 221, 21));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Garamond")});
        font1.setPointSize(16);
        font1.setBold(true);
        wordText->setFont(font1);
        GarticClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(GarticClass);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 653, 22));
        menuGartic = new QMenu(menuBar);
        menuGartic->setObjectName("menuGartic");
        GarticClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(GarticClass);
        mainToolBar->setObjectName("mainToolBar");
        GarticClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(GarticClass);
        statusBar->setObjectName("statusBar");
        GarticClass->setStatusBar(statusBar);

        menuBar->addAction(menuGartic->menuAction());

        retranslateUi(GarticClass);

        QMetaObject::connectSlotsByName(GarticClass);
    } // setupUi

    void retranslateUi(QMainWindow *GarticClass)
    {
        GarticClass->setWindowTitle(QCoreApplication::translate("GarticClass", "Gartic", nullptr));
        wordButton_1->setText(QCoreApplication::translate("GarticClass", "Word1", nullptr));
        wordButton_2->setText(QCoreApplication::translate("GarticClass", "Word2", nullptr));
        wordButton_3->setText(QCoreApplication::translate("GarticClass", "Word3", nullptr));
        username_text->setText(QCoreApplication::translate("GarticClass", "Username", nullptr));
        logo->setText(QString());
        wordText->setText(QCoreApplication::translate("GarticClass", "Draw: ", nullptr));
        menuGartic->setTitle(QCoreApplication::translate("GarticClass", "Gartic", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GarticClass: public Ui_GarticClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GARTIC_H
