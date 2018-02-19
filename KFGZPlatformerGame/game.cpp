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
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,screenWidth-2,screenHeight-2);

    //view, ez amit a jatekos lat
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(screenWidth,screenHeight);

    // jatekos letrehozasa
    player = new Character;
    player->setPos(screenWidth/4,screenHeight/2);  //itt majd lesz rendes helye is
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    scene->addItem(player);

    //ideiglenes map teszt
    Terrain *ground = new Terrain(0, screenHeight*4/5, screenWidth, screenHeight/5, 1);
    Terrain *wall = new Terrain(screenWidth/2-250, screenHeight*4/5-100, 100, 100, 2);
    Terrain *bar = new Terrain(screenWidth/2+50, screenHeight*4/5-200, 100, 100, 3);
    Terrain *bar2 = new Terrain(screenWidth/2+250, screenHeight*4/5-350, 100, 100, 4);
    scene->addItem(ground);
    scene->addItem(wall);
    scene->addItem(bar);
    scene->addItem(bar2);

    //kilepesgomb
    //exitButton = new QPushButton(QString("Exit"), this);


    //ha minden elokeszulet kesz, megnyitjuk az ablakot, androidon nincs tálca, úgyhogy windowson is fullscreennel kell tesztelni
    showFullScreen();
    player->setFocus();
}

Game::~Game()
{
    qDebug() << "game deleted";
}
