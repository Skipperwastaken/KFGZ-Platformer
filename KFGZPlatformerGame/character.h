#ifndef CHARACTER_H
#define CHARACTER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include <QKeyEvent>
#include <QTimer>

class Character:public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Character(QGraphicsItem * parent=0);
    QGraphicsLineItem *top, *right, *bottom, *left;
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);
    QTimer *moveTimer;
    int yVelocity=-5;
public slots:
    void move();
};

#endif // CHARACTER_H
