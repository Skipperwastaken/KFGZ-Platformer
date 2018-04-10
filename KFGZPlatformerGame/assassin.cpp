#include "assassin.h"

AssassIn::AssassIn()
{
    setNormalModel(QString(":/images/images/enemies/assassIn/assassin.png"));
    prepModel.load(":/images/images/enemies/assassIn/assassinPrep.png");
    attackModel.load(":/images/images/enemies/assassIn/assassinAttack.png");
    attackHitBox = new QGraphicsPixmapItem(QPixmap(":/images/images/enemies/assassIn/assassinHitbox.png"), this);
    //Kis hitbox, semmi preptime, ugrani, csúszni is lehet
    attackHitBox->setOffset(22, 71);
    attackHitBox->hide();
    prepTime=0000;
}
