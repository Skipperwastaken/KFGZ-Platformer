#include "character.h"
#include "terrain.h"
#include <QDebug>

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
    if (event->key() == Qt::Key_W){
        yVelocity=3;
        qDebug() << "Jump";
    }
}

void Character::keyReleaseEvent(QKeyEvent *event)
{

}

void Character::move()
{
    //reset falling speed
    yVelocity -= 0.02;

    //foldreerkezes
    QList<QGraphicsItem *> bottomCollidingItems = bottom->collidingItems();
    for (int i = 0, n = bottomCollidingItems.size(); i < n; ++i)
    {
        if (typeid(*(bottomCollidingItems[i])) == typeid(Terrain)){ //ha érintkezik a földdel, akkor nem eshet
            yVelocity = (yVelocity < 0 ? 0 : yVelocity);
        }
    }

    //ha erintkezik a folddel, akkor a yvelocity 0, ha esik, akkor negativ, ha ugrik akkr pozitiv
    setPos(x(), y()-yVelocity);

}
