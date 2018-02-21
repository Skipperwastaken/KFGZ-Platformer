#include "spearman.h"

SpearMan::SpearMan()
{
    setNormalModel(QString(":/images/images/enemies/spearMan/spearman.png"));
    prepModel.load(":/images/images/enemies/spearMan/spearmanPrep.png");
    attackModel.load(":/images/images/enemies/spearMan/spearmanAttack.png");
    attackHitBox = new QGraphicsPixmapItem(QPixmap(":/images/images/enemies/spearMan/spearmanHitbox.png"), this);
    attackHitBox->setOffset(0, 91);
    attackHitBox->hide();
    prepTime=1000;
}
