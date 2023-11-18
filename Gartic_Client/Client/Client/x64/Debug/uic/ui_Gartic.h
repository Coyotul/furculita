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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GarticClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *GarticClass)
    {
        if (GarticClass->objectName().isEmpty())
            GarticClass->setObjectName("GarticClass");
        GarticClass->resize(600, 400);
        menuBar = new QMenuBar(GarticClass);
        menuBar->setObjectName("menuBar");
        GarticClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(GarticClass);
        mainToolBar->setObjectName("mainToolBar");
        GarticClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(GarticClass);
        centralWidget->setObjectName("centralWidget");
        GarticClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(GarticClass);
        statusBar->setObjectName("statusBar");
        GarticClass->setStatusBar(statusBar);

        retranslateUi(GarticClass);

        QMetaObject::connectSlotsByName(GarticClass);
    } // setupUi

    void retranslateUi(QMainWindow *GarticClass)
    {
        GarticClass->setWindowTitle(QCoreApplication::translate("GarticClass", "Gartic", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GarticClass: public Ui_GarticClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GARTIC_H
