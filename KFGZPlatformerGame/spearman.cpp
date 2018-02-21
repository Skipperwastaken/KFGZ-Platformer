#include "spearman.h"

SpearMan::SpearMan()
{
    setNormalModel(QString(":/images/images/enemies/spearMan/spearman.png"));
    prepModel.load(":/images/images/enemies/spearMan/spearmanPrep.png");
    attackModel.load(":/images/images/enemies/spearMan/spearmanAttack.png");

    prepTime=1000;
}
