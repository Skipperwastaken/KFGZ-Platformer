#include <QGuiApplication>
#include <QScreen>
#include "game.h"
#include "terrain.h"
#include <QDebug>

Game::Game(QWidget *parent)
{
    /*elmentjuk a kepernyo magassagat es szelesseget, ez fontos, mert nem minden telon ugyanaz,
    a dolgok meretet pedig ez alapjan szamoljuk*/
    QScreen *screen = QGuiApplication::primaryScreen();
    screenWidth = screen->geometry().width();
    screenHeight = screen->geometry().height();
    qDebug() << screenHeight << " " << screenWidth;

    // scene, ez a palya
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,screenWidth-2,screenHeight-2);

    //view, ez amit a jatekos lat
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(screenWidth,screenHeight);

    // jatekos letrehozasa
    player = new Character();
    player->setPos(screenWidth/2,screenHeight/2);  //itt majd lesz rendes helye is
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    scene->addItem(player);

    //ideiglenes map teszt
    Terrain *newRect = new Terrain(0, screenHeight*4/5+10, screenWidth, screenHeight/5);
    scene->addItem(newRect);

    //ha minden elokeszulet kesz, megnyitjuk az ablakot, androidon nincs tálca, úgyhogy windowson is fullscreennel kell tesztelni
    showFullScreen();
}
