#include <QGuiApplication>
#include <QScreen>
#include "game.h"
#include "terrain.h"
#include <QDebug>


Game::Game()
{

    /*elmentjuk a kepernyo magassagat es szelesseget, ez fontos, mert nem minden telon ugyanaz,
    a dolgok meretet pedig ez alapjan szamoljuk*/
    QScreen *screen = QGuiApplication::primaryScreen();
    screenWidth = screen->geometry().width();
    screenHeight = screen->geometry().height();
    qDebug() << "Screen height: " << screenHeight << ", Screen width: " << screenWidth;

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

    //ellenfelkereso timer
    checkForAttactT = new QTimer(this);
    connect(checkForAttactT, &QTimer::timeout,
            this, &Game::checkForAttact);
    checkForAttactT->start(10);
    //ellenfel hozzadasa, szinten csak ideiglenes
    //qDebug() << "1";
    spearman = new SpearMan;
    //qDebug() << "2";
    spearman->setPos(screenWidth/2, screenHeight*4/5-400);
    //qDebug() << "3";
    scene->addItem(spearman);
    //qDebug() << "4";

    //kilepesgomb, itt kesobb majd egy kis menu lesz
    exitButton = new QPushButton(QString("Exit"));
    exitButton->setGeometry(10, 10, screenHeight/10, screenHeight/10);
    scene->addWidget(exitButton);
    connect(exitButton, &QAbstractButton::clicked,
            this, &Game::exitGame);

    //ha minden elokeszulet kesz, megnyitjuk az ablakot, androidon nincs tálca, úgyhogy windowson is fullscreennel kell tesztelni
    showFullScreen();
}

//jatekos iranyitasa, lehetne a character classban is, de ott nehezebb bug mentesre megcsinalni
void Game::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_W){
        if(!event->isAutoRepeat() && player->jumpsLeft>0)
        {
            player->yVelocity=0.6;
            player->jumpsLeft--;
        }
        player->jumping=true;
        //qDebug() << "Jump";
    }
    if (event->key() == Qt::Key_A){
        player->goingLeft=true;
        //qDebug() << "Left";
    }
    if (event->key() == Qt::Key_D){
        player->goingRight=true;
        //qDebug() << "Right";
    }
    if (event->key() == Qt::Key_S){
        player->sliding=true;
        //qDebug() << "Slide";
    }
}

void Game::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_W){
        player->jumping=false;
        //qDebug() << "Jump key released";
    }
    if (event->key() == Qt::Key_A){
        player->goingLeft=false;
        //qDebug() << "Left key released";
    }
    if (event->key() == Qt::Key_D){
        player->goingRight=false;
        //qDebug() << "Right key released";
    }
    if (event->key() == Qt::Key_S){
        player->sliding=false;
        //qDebug() << "Slide key released";
    }
}

void Game::checkForAttact()
{
    if(std::abs(player->pos().y()-spearman->pos().y()) < 300 && std::abs(player->pos().x()-spearman->pos().x()) < 300)
    {
        qDebug() << "spearman close";
        spearman->prepAttack();
    }
}

Game::~Game()
{
    qDebug() << "game deleted";
}


void Game::exitGame()
{
    close();
}
