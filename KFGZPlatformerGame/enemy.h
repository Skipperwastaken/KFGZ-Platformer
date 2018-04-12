#ifndef ENEMY_H
#define ENEMY_H
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include <QPixmap>
#include <QDebug>
#include "character.h"

class Enemy:public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Enemy();
    QGraphicsPixmapItem *model;
    QGraphicsPixmapItem *attackHitBox;
    QPixmap normalModel, prepModel, attackModel, deadModel; //ideiglenes, kesobb lesznek animaciok
    QTimer *prepAttackT, *attackT, *attackHitboxT, *attackCD;
    int prepTime;
    void setNormalModel(QString mdl);
    bool dead=false;
signals:
    void hit();
public slots:
    void prepAttack(); //a kap jelet a karakter kozelsegere, akkor elkezd felkeszulni a tamadasra
    void attack();     //tamad, itt nezi h el talalta e
    void checkAttackHitbox();
    void finishAttack(); // egy ideig kint van az atack hitbox, hogy lathato legyen, utana ez tuntei el
    void die();
};

#endif // ENEMY_H
