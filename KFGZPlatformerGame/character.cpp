#include "character.h"

Character::Character(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    // karakter kepe, kesobb majd animalni kell
    setPixmap(QPixmap(":/images/images/character.png"));
}

void Character::keyPressEvent(QKeyEvent *event)
{

}

void Character::keyReleaseEvent(QKeyEvent *event)
{

}

void Character::move()
{

}
