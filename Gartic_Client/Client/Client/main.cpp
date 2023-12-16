#include "Gartic.h"
#include <QtWidgets/QApplication>
#include <crow.h>
#include <cpr/cpr.h>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Gartic w;
    w.SetWords("Cleste", "Magnet", "Andrei");
    w.show();
    return a.exec();
}
