#include "character.h"
#include "terrain.h"
#include <QDebug>

Character::Character(QGraphicsItem *parent): QGraphicsRectItem(parent)
{
    // karakter kepe, kesobb majd animalni kell
    setRect(0, 0, 100, 200);
    setPen(QPen(QColor(0,0,0,0)));
    model=new QGraphicsPixmapItem(QPixmap(":/images/images/character.png").scaled(QSize(100, 200)), this);

    //QLine itemek, ezekkel tud erintkezni a kornyezettel a karakter
    top = new QGraphicsLineItem(4, 1, 96, 1, this);
    top->setPen(QPen(Qt::cyan, 4));
    right = new QGraphicsLineItem(99, 4, 99, 196, this);
    right->setPen(QPen(Qt::blue, 4));
    bottom = new QGraphicsLineItem(4, 199, 96, 199, this);
    bottom->setPen(QPen(Qt::black, 4));
    left = new QGraphicsLineItem(1, 4, 1, 196, this);
    left->setPen(QPen(Qt::red, 4));

    //timer, annyi idokozonkent mozog a karakter
    moveTimer=new QTimer(this);
    connect(moveTimer,SIGNAL(timeout()),this,SLOT(move()));
    moveTimer->start(1);

    //csuszas
    slidingTimer=new QTimer(this);
    connect(slidingTimer,SIGNAL(timeout()),this,SLOT(stopSliding()));
    slidingTimer->setSingleShot(true);
    slidingCD=new QTimer(this);
    slidingCD->setSingleShot(true);
}

Character::~Character()
{
    qDebug() << "Character deleted";
}

void Character::move()
{
    //gravitacio
    yVelocity -= (jumping && yVelocity>0 ? 0.0008 : 0.0014);

    //fal erzekeles reset
    wallLeft=false;
    wallRight=false;

    //foldon van-e
    bottomCollidingItems = bottom->collidingItems();
    for (int i = 0, n = bottomCollidingItems.size(); i < n; ++i)
    {
        //ha erintkezik a folddel, akkor nem eshet es csak akkor csuszhat
        if (typeid(*(bottomCollidingItems.at(i))) == typeid(Terrain))
        {
            //eses megallitasa
            yVelocity = (yVelocity < 0 ? 0 : yVelocity);
            //ha leer a foldre akkor ugorhat ujra
            jumpsLeft =1;
            //csuszas
            if(!slidingTimer->isActive() && !slidingCD->isActive() && sliding)
            {
                //TODO: elkezd csuszni
                top->setLine(4, 101, 96, 101);
                right->setLine(99, 104, 99, 196);
                left->setLine(1, 104, 1, 196);

                //qDebug() << "started sliding";
                slidingTimer->start(1000);
            }

        }
    }
    if(!sliding && slidingTimer->remainingTime()<500 && slidingTimer->isActive())
    {
        slidingTimer->stop();
        stopSliding();
        //qDebug() << "sliding stopped, released slide button";
    }
    if(yVelocity!=0 && slidingTimer->isActive())
    {
        slidingTimer->stop();
        stopSliding();
        //qDebug() << "sliding stopped, left ground";
    }
    topCollidingItems = top->collidingItems();
    for (int i = 0, n = topCollidingItems.size(); i < n; ++i)
    {
        if (typeid(*(topCollidingItems.at(i))) == typeid(Terrain)) //ha erintkezik plafonnal, akkor stop
        {
            //ugras megallitasa
            yVelocity = (yVelocity > 0 ? 0 : yVelocity);
        }
    }

    //jobb oldalrol jonni fog a fal, igy ott jobban megkell csinalni a falnak utkozest
    //ha mas iranyba is mozognanak feluletek, akkor ott is megkene ilyenre csinalni
        //qDebug() << "rightWall";
    rightCollidingItems = right->collidingItems();
    for (int i = 0, n = rightCollidingItems.size(); i < n; ++i)
    {
        if (typeid(*(rightCollidingItems.at(i))) == typeid(Terrain)) //vane fal mellette
        {
            //() << rightCollidingItems[i]->scenePos().x() << " " << pos().x();
            if(rightCollidingItems[i]->scenePos().x()-100<pos().x())
            {
                setPos(rightCollidingItems[i]->scenePos().x()-100, y());
            }
        }
    }


    if(goingLeft)
    {
        leftCollidingItems = left->collidingItems();
        for (int i = 0, n = leftCollidingItems.size(); i < n; ++i)
        {
            if (typeid(*(leftCollidingItems.at(i))) == typeid(Terrain)) //vane fal mellette
            {
                //qDebug() << "wallLeft";
                wallLeft=true;
            }
        }
    }
    //oldalra mozgas
    //ha levegoben van vagy csuszik, akkor lassabban mozog oldalra, mint ha futna a foldon
    if(goingRight && !wallRight)
        setPos(x()+(yVelocity == 0 && !slidingTimer->isActive() ? 0.4 : 0.25), y());
    if(goingLeft && !wallLeft)
        setPos(x()-(!slidingTimer->isActive()  ? 0.4 : 0.25), y());
    //ha erintkezik a folddel, akkor a yvelocity 0, ha esik, akkor negativ, ha ugrik akkr pozitiv
    setPos(x(), y()-yVelocity);
}

void Character::stopSliding()
{
    //TODO: stop sliding
    top->setLine(4, 1, 96, 1);
    for (int i = 0, n = topCollidingItems.size(); i < n; ++i)
    {
        if (typeid(*(topCollidingItems.at(i))) == typeid(Terrain))
        {
            top->setLine(4, 101, 96, 101);
            slidingTimer->start(10);
            return;
        }
    }
    right->setLine(99, 4, 99, 196);
    left->setLine(1, 4, 1, 196);
    slidingCD->start(500);
}
