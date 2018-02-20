#include "enemy.h"

Enemy::Enemy()
{
    prepAttackT = new QTimer(this);
    connect(prepAttackT, &QTimer::timeout,
            this, &Enemy::attack);
    connect(attackT, &QTimer::timeout,
            this, &Enemy::finishAttack);
}

void Enemy::prepAttack()
{
    model->setPixmap(prepModel);
}

void Enemy::attack()
{
    model->setPixmap(attackModel);
}

void Enemy::finishAttack()
{
    model->setPixmap(normalModel);
}
