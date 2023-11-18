#include "Gartic.h"
#include <QtWidgets/QApplication>
#include <crow.h>
#include <cpr/cpr.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Gartic w;
    w.show();
    return a.exec();
}
