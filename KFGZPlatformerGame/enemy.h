#ifndef ENEMY_H
#define ENEMY_H
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include <QPixmap>

class Enemy:public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Enemy();
    QGraphicsPixmapItem *model;
    QGraphicsPixmapItem *attackHitBox;
    QPixmap normalModel, prepModel, attackModel; //ideiglenes, kesobb lesznek animaciok
    QTimer *prepAttackT, *attackT;
    int prepTime;

signals:
    void hit();
public slots:
    void prepAttack(); //a kap jelet a karakter kozelsegere, akkor elkezd felkeszulni a tamadasra
    void attack();     //tamad, itt nezi h el talalta e
    void finishAttack(); // egy ideig kint van az atack hitbox, hogy lathato legyen, utana ez tuntei el
};

#endif // ENEMY_H
