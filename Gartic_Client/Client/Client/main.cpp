#include "Gartic.h"
#include <QtWidgets/QApplication>
#include <crow.h>
#include <cpr/cpr.h>
#include <iostream>
#include <chrono>
#include <thread>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    std::chrono::seconds interval(1);
    Gartic w;
    w.show();

    while (w.isDrawing == false) 
    {
        w.downloadImageFromServer();
        w.displayImage("downloaded_image.png");
        std::this_thread::sleep_for(interval);
    }
    
    return a.exec();
}
