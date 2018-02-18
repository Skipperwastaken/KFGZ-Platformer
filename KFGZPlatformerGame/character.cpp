#include "character.h"
#include "terrain.h"
#include <QDebug>

Character::Character(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    // karakter kepe, kesobb majd animalni kell
    setPixmap(QPixmap(":/images/images/character.png").scaled(QSize(100, 200)));

    //QLine itemek, ezekkel tud erintkezni a kornyezettel a karakter
    top = new QGraphicsLineItem(3, 1, 96, 1, this);
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

    //fal erzekeles reset
    wallLeft=false;
    wallRight=false;

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
            if (typeid(*(rightCollidingItems[i])) == typeid(Terrain)) //ha nem erintkezik fallal, akkor mehet
            {
                qDebug() << "wallRight";
                wallRight=true;
            }
        }
    }
    if(goingLeft)
    {
        QList<QGraphicsItem *> leftCollidingItems = left->collidingItems();
        for (int i = 0, n = leftCollidingItems.size(); i < n; ++i)
        {
            if (typeid(*(leftCollidingItems[i])) == typeid(Terrain)) //ha nem erintkezik fallal, akkor mehet
            {
                qDebug() << "wallLeft";
                wallLeft=true;
            }
        }
    }
    //oldalra mozgas
    if(goingRight && !wallRight)
        setPos(x()+0.4, y());
    if(goingLeft && !wallLeft)
        setPos(x()-0.4, y());
    //ha erintkezik a folddel, akkor a yvelocity 0, ha esik, akkor negativ, ha ugrik akkr pozitiv
    setPos(x(), y()-yVelocity);

}
