#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include "character.h"

class Game: public QGraphicsView{
    Q_OBJECT
public:
    Game(QWidget * parent=0);

    QGraphicsScene * scene;

    int screenHeight, screenWidth;

    Character *player;
};

#endif // GAME_H
