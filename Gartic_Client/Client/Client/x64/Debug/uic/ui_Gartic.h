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
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
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
    QPushButton *wordButton1;
    QPushButton *wordButton_2;
    QPushButton *wordButton_3;
    QTextEdit *textEdit;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *GarticClass)
    {
        if (GarticClass->objectName().isEmpty())
            GarticClass->setObjectName("GarticClass");
        GarticClass->resize(473, 400);
        GarticClass->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        centralWidget = new QWidget(GarticClass);
        centralWidget->setObjectName("centralWidget");
        textBox = new QLineEdit(centralWidget);
        textBox->setObjectName("textBox");
        textBox->setGeometry(QRect(10, 320, 201, 21));
        wordButton1 = new QPushButton(centralWidget);
        wordButton1->setObjectName("wordButton1");
        wordButton1->setGeometry(QRect(30, 10, 75, 24));
        wordButton_2 = new QPushButton(centralWidget);
        wordButton_2->setObjectName("wordButton_2");
        wordButton_2->setGeometry(QRect(100, 10, 75, 24));
        wordButton_3 = new QPushButton(centralWidget);
        wordButton_3->setObjectName("wordButton_3");
        wordButton_3->setGeometry(QRect(170, 10, 75, 24));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(10, 200, 201, 111));
        GarticClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(GarticClass);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 473, 22));
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
