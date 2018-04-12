#include "enemy.h"

Enemy::Enemy()
{
    prepAttackT = new QTimer(this);
    attackT = new QTimer(this);
    attackCD = new QTimer(this);
    attackHitboxT = new QTimer(this);
    prepAttackT->setSingleShot(true);
    attackT->setSingleShot(true);
    attackCD->setSingleShot(true);

    connect(prepAttackT, &QTimer::timeout,
            this, &Enemy::attack);
    connect(attackT, &QTimer::timeout,
            this, &Enemy::finishAttack);
    connect(attackHitboxT, &QTimer::timeout,
            this, &Enemy::checkAttackHitbox);

}

void Enemy::setNormalModel(QString mdl)
{
    normalModel.load(mdl);
    model = new QGraphicsPixmapItem(normalModel, this);
    if(model->pixmap().hasAlphaChannel())
        //qDebug() << "van alpha channel";
    model->setShapeMode(QGraphicsPixmapItem::HeuristicMaskShape);
}

void Enemy::prepAttack()
{
    if(dead)
        return;
    if(!prepAttackT->isActive() && !attackT->isActive() && !attackCD->isActive())
    {
        model->setPixmap(prepModel);
        model->setShapeMode(QGraphicsPixmapItem::HeuristicMaskShape);
        prepAttackT->start(prepTime);
    }
}

void Enemy::attack()
{
    if(dead)
        return;
    //qDebug() << "attack";
    model->setPixmap(attackModel);
    attackHitBox->show();
    attackHitboxT->start(10);
    attackT->start(500);
}

void Enemy::checkAttackHitbox()
{
    if(dead)
    {
        attackHitboxT->stop();
        return;
    }
    QList<QGraphicsItem *> hitStuff = attackHitBox->collidingItems();
    for (int i = 0, n = hitStuff.size(); i < n; ++i)
    {
        //ha karaktert er, akkor hit() jelzest emittel
        if (typeid(*(hitStuff[i])) == typeid(Character))
        {
            emit hit();
            qDebug() << "hit";
        }
    }
}


void Enemy::finishAttack()
{
    attackHitboxT->stop();
    if(dead)
        return;
    //qDebug() << "finish attack";
    attackHitBox->hide();
    model->setPixmap(normalModel);
    attackCD->start(2000);
}

void Enemy::die()
{
    model->setPixmap(deadModel);
    attackHitBox->hide();
    dead=true;
    //model->setPixmap(deadModel);
    prepAttackT->stop();
    attackT->stop();
    attackCD->stop();
    qDebug() << "ded";
}
