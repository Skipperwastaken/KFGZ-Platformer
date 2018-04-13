#ifndef CHARACTER_H
#define CHARACTER_H

#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include <QTimer>
#include <QList>
#include <QPen>
#include <enemy.h>
#include <QGraphicsProxyWidget>
#include <QDebug>
#include <QColor>


class Character:public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Character(QGraphicsItem * parent=0);
    ~Character();
    QGraphicsPixmapItem *model;
    QGraphicsLineItem *top, *right, *bottom, *left;
    QList<QGraphicsItem *> topCollidingItems, rightCollidingItems, bottomCollidingItems, leftCollidingItems;
    QTimer *moveTimer;
    double yVelocity=0.0008;
    bool jumping=false; //levan-e nyomva az ugras, lehet magassabbat ugrani, ha hosszan van lenyomva
    int jumpsLeft=1; //hany ugras van vissza
    bool goingLeft=false, goingRight=false, wallRight=false, wallLeft=false; //levane nyomva egy gomb, amivel oldalra megy a karakter
    bool sliding=false;
    QTimer *slidingTimer, *slidingCD; //ido, ameddig csuszik es amig ujra csuszhat
signals:
    void died();
    void moved(int amount);
public slots:
    void move();
    void stopSliding();
};

#endif // CHARACTER_H
