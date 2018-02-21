#include "enemy.h"

Enemy::Enemy()
{
    prepAttackT = new QTimer(this);
    attackT = new QTimer(this);
    attackCD = new QTimer(this);
    prepAttackT->setSingleShot(true);
    attackT->setSingleShot(true);
    attackCD->setSingleShot(true);

    connect(prepAttackT, &QTimer::timeout,
            this, &Enemy::attack);
    connect(attackT, &QTimer::timeout,
            this, &Enemy::finishAttack);

}

void Enemy::setNormalModel(QString mdl)
{
    normalModel.load(mdl);
    model = new QGraphicsPixmapItem(normalModel, this);
}

void Enemy::prepAttack()
{
    if(!prepAttackT->isActive() && !attackT->isActive() && !attackCD->isActive())
    {
        model->setPixmap(prepModel);
        prepAttackT->start(prepTime);
    }
}

void Enemy::attack()
{
    qDebug() << "attack";
    model->setPixmap(attackModel);
    attackT->start(500);
}

void Enemy::finishAttack()
{
    qDebug() << "finish attack";
    model->setPixmap(normalModel);
    attackCD->start(2000);
}
