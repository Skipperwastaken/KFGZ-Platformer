#ifndef CHARACTER_H
#define CHARACTER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include <QKeyEvent>
#include <QTimer>
#include <QList>
#include <QPen>


class Character:public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Character(QGraphicsItem * parent=0);
    QGraphicsLineItem *top, *right, *bottom, *left;
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);
    QTimer *moveTimer;
    double yVelocity=-5;
    bool jumping=false; //levan-e nyomva az ugras, lehetne magassabbat ugrani, ha hosszan van lenyomva
    int jumpsLeft=1; //hany ugras van vissza, majd lehet double jumpot is belerakni, plusz kell programozas szempontbol is
    bool goingLeft=false, goingRight=false, wallRight=false, wallLeft=false; //levane nyomva egy gomb, amivel oldalra megy a karakter
    bool sliding=false; //levan-e nyomva a gomb amivel csúszik
    int slidingTime=0; //lenyomaskor elkezd szamolni, 1 secig tud csuszni, utana felsecig nem tud, mindketto ezzel van szamolva
public slots:
    void move();
};

#endif // CHARACTER_H
