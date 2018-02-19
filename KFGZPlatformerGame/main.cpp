#include <QApplication>
#include <QPushButton>
#include "game.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //kesobb majd eloszor egy menu nyilik meg es ott lehet inditani a gamet, de addig is legyen igy
    Game game;

    return a.exec();
}
