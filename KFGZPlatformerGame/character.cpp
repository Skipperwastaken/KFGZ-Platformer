#include "character.h"

Character::Character(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    // karakter kepe, kesobb majd animalni kell
    setPixmap(QPixmap(":/images/images/character.png").scaled(QSize(100, 200)));

    //QLine itemek, ezekkel tud erintkezni a kornyezettel a karakter
    top = new QGraphicsLineItem(1, 1, 98, 1, this);
    right = new QGraphicsLineItem(98, 1, 98, 198, this);
    bottom = new QGraphicsLineItem(1, 198, 98, 198, this);
    left = new QGraphicsLineItem(1, 1, 1, 189, this);

    //timer, annyi idokozonkent mozog a karakter
    moveTimer=new QTimer(this);
    connect(moveTimer,SIGNAL(timeout()),this,SLOT(move()));
    moveTimer->start(10);
}

void Character::keyPressEvent(QKeyEvent *event)
{

}

void Character::keyReleaseEvent(QKeyEvent *event)
{

}

void Character::move()
{
    //setPos(x(), y()-yVelocity);
}
