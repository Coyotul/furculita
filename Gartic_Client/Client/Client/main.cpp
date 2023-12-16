#include "Gartic.h"
#include <QtWidgets/QApplication>
#include <crow.h>
#include <cpr/cpr.h>
#include <iostream>

int main(int argc, char *argv[])
{
    int languageValue = 2;

    std::string url = "http://localhost:8080/language?language=" + std::to_string(languageValue);

    cpr::Response response = cpr::Get(cpr::Url{ url });


    QApplication a(argc, argv);
    Gartic w;
    w.SetWords("Cleste", "Magnet", "Andrei");
    w.show();
    return a.exec();
}
