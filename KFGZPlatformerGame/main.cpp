#include <QApplication>
#include "game.h"
#include "menu.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Menu menu;
    Game game;
    //kesobb majd eloszor egy menu nyilik meg es ott lehet inditani a gamet, de addig is legyen igy
    return a.exec();
}
