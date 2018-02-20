#include <QApplication>
#include "menu.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Menu menu;
    Menu menu;
    //kesobb majd eloszor egy menu nyilik meg es ott lehet inditani a gamet, de addig is legyen igy
    return a.exec();
}
