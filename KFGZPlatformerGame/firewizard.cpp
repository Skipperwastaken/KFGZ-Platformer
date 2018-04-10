#include "firewziard.h"

FireWizard::FireWizard()
{
    setNormalModel(QString(":/images/images/enemies/fireWizard/fireWizard.png"));
    prepModel.load(":/images/images/enemies/fireWizard/fireWizardPrep.png");
    attackModel.load(":/images/images/enemies/fireWizard/fireWizardAttack.png");
    attackHitBox = new QGraphicsPixmapItem(QPixmap(":/images/images/enemies/fireWizard/fireBall.png"), this);
    attackHitBox->setOffset(0,40);
    attackHitBox->hide();
    prepTime=1000;
}
