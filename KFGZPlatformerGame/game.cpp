#include <QGuiApplication>
#include <QScreen>
#include "game.h"

Game::Game(QWidget *parent)
{
    /*elmentjuk a kepernyo magassagat es szelesseget, ez fontos, mert nem minden telon ugyanaz,
    a dolgok meretet pedig ez alapjan szamoljuk*/
    QScreen *screen = QGuiApplication::primaryScreen();
    screenWidth = screen->geometry().width();
    screenHeight = screen->geometry().height();

    // scene, ez a palya
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,screenWidth,screenHeight);

    //view, ez amit a jatekos lat
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(screenWidth,screenHeight);

    //ha minden elokeszulet kesz, megnyitjuk az ablakot
    show();
}
