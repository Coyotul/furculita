/********************************************************************************
** Form generated from reading UI file 'Gartic.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GARTIC_H
#define UI_GARTIC_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GarticClass
{
public:
    QWidget *centralWidget;
    QLineEdit *textBox;
    QPushButton *wordButton1;
    QPushButton *wordButton_2;
    QPushButton *wordButton_3;
    QLineEdit *chat;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *GarticClass)
    {
        if (GarticClass->objectName().isEmpty())
            GarticClass->setObjectName("GarticClass");
        GarticClass->resize(526, 400);
        centralWidget = new QWidget(GarticClass);
        centralWidget->setObjectName("centralWidget");
        textBox = new QLineEdit(centralWidget);
        textBox->setObjectName("textBox");
        textBox->setGeometry(QRect(10, 320, 161, 21));
        wordButton1 = new QPushButton(centralWidget);
        wordButton1->setObjectName("wordButton1");
        wordButton1->setGeometry(QRect(30, 10, 75, 24));
        wordButton_2 = new QPushButton(centralWidget);
        wordButton_2->setObjectName("wordButton_2");
        wordButton_2->setGeometry(QRect(190, 10, 75, 24));
        wordButton_3 = new QPushButton(centralWidget);
        wordButton_3->setObjectName("wordButton_3");
        wordButton_3->setGeometry(QRect(390, 10, 75, 24));
        chat = new QLineEdit(centralWidget);
        chat->setObjectName("chat");
        chat->setGeometry(QRect(10, 200, 161, 111));
        GarticClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(GarticClass);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 526, 22));
        GarticClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(GarticClass);
        mainToolBar->setObjectName("mainToolBar");
        GarticClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(GarticClass);
        statusBar->setObjectName("statusBar");
        GarticClass->setStatusBar(statusBar);

        retranslateUi(GarticClass);

        QMetaObject::connectSlotsByName(GarticClass);
    } // setupUi

    void retranslateUi(QMainWindow *GarticClass)
    {
        GarticClass->setWindowTitle(QCoreApplication::translate("GarticClass", "Gartic", nullptr));
        wordButton1->setText(QCoreApplication::translate("GarticClass", "Word1", nullptr));
        wordButton_2->setText(QCoreApplication::translate("GarticClass", "Word2", nullptr));
        wordButton_3->setText(QCoreApplication::translate("GarticClass", "Word3", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GarticClass: public Ui_GarticClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GARTIC_H
