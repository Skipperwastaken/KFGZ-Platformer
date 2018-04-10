#include "swordsman.h"

SwordsMan::SwordsMan()
{
    setNormalModel(QString(":/images/images/enemies/swordsMan/swordsman.png"));
    prepModel.load(":/images/images/enemies/swordsMan/swordsmanPrep.png");
    attackModel.load(":/images/images/enemies/swordsMan/swordsmanAttack.png");
    attackHitBox = new QGraphicsPixmapItem(QPixmap(":/images/images/enemies/swordsMan/swordsmanHitbox.png"), this);
    //Egy viszonylag nagy hitboxszal van felszerelve ami a karatkter tetejét érinti ezáltal csak átugrani lehet esetleg később becsúszással legyőzni.
    attackHitBox->setOffset(0, 0);
    attackHitBox->hide();
    prepTime=1500;
}
