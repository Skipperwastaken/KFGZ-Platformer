#include "character.h"
#include "terrain.h"
#include <QDebug>

Character::Character(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    // karakter kepe, kesobb majd animalni kell
    setPixmap(QPixmap(":/images/images/character.png").scaled(QSize(100, 200)));

    //QLine itemek, ezekkel tud erintkezni a kornyezettel a karakter
    top = new QGraphicsLineItem(1, 1, 98, 1, this);
    //top->setPen();
    right = new QGraphicsLineItem(98, 8, 98, 192, this);
    bottom = new QGraphicsLineItem(1, 198, 98, 198, this);
    left = new QGraphicsLineItem(1, 8, 1, 192, this);

    //timer, annyi idokozonkent mozog a karakter
    moveTimer=new QTimer(this);
    connect(moveTimer,SIGNAL(timeout()),this,SLOT(move()));
    moveTimer->start(1);
}

void Character::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_W){
        if(!event->isAutoRepeat() && jumpsLeft>0)
        {
            yVelocity=0.4;
            jumpsLeft--;
        }
        jumping=true;
        qDebug() << "Jump";
    }
    if (event->key() == Qt::Key_A){
        goingLeft=true;
        qDebug() << "Left";
    }
    if (event->key() == Qt::Key_D){
        goingRight=true;
        qDebug() << "Right";
    }
    if (event->key() == Qt::Key_S){
        //jumping=true;
        qDebug() << "Slide";
    }
}

void Character::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_W){
        jumping=false;
        qDebug() << "Jump stopped";
    }
    if (event->key() == Qt::Key_A){
        goingLeft=false;
        qDebug() << "Left stopped";
    }
    if (event->key() == Qt::Key_D){
        goingRight=false;
        qDebug() << "Right stopped";
    }
    if (event->key() == Qt::Key_S){
        //jumping=true;
        qDebug() << "Slide";
    }
}

void Character::move()
{
    //gravitacio
    yVelocity -= (jumping && yVelocity>0 ? 0.0005 : 0.0010);

    //foldreerkezes
    QList<QGraphicsItem *> bottomCollidingItems = bottom->collidingItems();
    for (int i = 0, n = bottomCollidingItems.size(); i < n; ++i)
    {
        if (typeid(*(bottomCollidingItems[i])) == typeid(Terrain)) //ha erintkezik a folddel, akkor nem eshet
        {
            yVelocity = (yVelocity < 0 ? 0 : yVelocity);
            jumpsLeft =1; //ha leer a foldre akkor ugorhat ujra
        }
    }
    if(goingRight)
    {
        QList<QGraphicsItem *> rightCollidingItems = right->collidingItems();
        for (int i = 0, n = rightCollidingItems.size(); i < n; ++i)
        {
            if (typeid(*(rightCollidingItems[i])) != typeid(Terrain)) //ha nem erintkezik fallal, akkor mehet
            {
                setPos(x()+0.4, y());
            }
        }
    }
    if(goingLeft)
    {
        QList<QGraphicsItem *> leftCollidingItems = left->collidingItems();
        for (int i = 0, n = leftCollidingItems.size(); i < n; ++i)
        {
            if (typeid(*(leftCollidingItems[i])) != typeid(Terrain)) //ha nem erintkezik fallal, akkor mehet
            {
                setPos(x()-0.4, y());
            }
        }
    }


    //ha erintkezik a folddel, akkor a yvelocity 0, ha esik, akkor negativ, ha ugrik akkr pozitiv
    setPos(x(), y()-yVelocity);

}
