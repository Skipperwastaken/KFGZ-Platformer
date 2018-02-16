#ifndef CHARACTER_H
#define CHARACTER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include <QKeyEvent>

class Character:public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Character(QGraphicsItem * parent=0);
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);
public slots:
    void move();
};

#endif // CHARACTER_H
