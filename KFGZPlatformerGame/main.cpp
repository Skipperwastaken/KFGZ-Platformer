#include <QApplication>
#include <game.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //kesobb majd eloszor egy emnu nyilik meg es ott lehet inditani a gamet, de addig is legyen igy
    Game *game = new Game();

    return a.exec();
}
