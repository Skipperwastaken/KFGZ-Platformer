#include "earthwizard.h"

EarthWizard::EarthWizard()
{
    setNormalModel(QString(":/images/images/enemies/earthWizard/earthwizard.png"));
    prepModel.load(":/images/images/enemies/earthWizard/earthwizardPrep.png");
    attackModel.load(":/images/images/enemies/earthWizard/earthwizardAttack.png");
    attackHitBox = new QGraphicsPixmapItem(QPixmap(":/images/images/enemies/earthWizard/earthwizardHitbox.png"), this);
    //Az ötlet az, hogy egy széles hitboxú támadás, amit dupla ugrással kell hárítani
    attackHitBox->setOffset(-555, 105);
    attackHitBox->hide();
    prepTime=1000;
}
