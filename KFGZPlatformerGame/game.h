#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include "character.h"
#include <QPushButton>

class Game: public QGraphicsView{
    Q_OBJECT
public:
    Game();
    ~Game();

    QGraphicsScene * scene;
    int screenHeight, screenWidth;
    Character *player;
    QPushButton * exitButton;
public slots:
    void exitGame();
};

#endif // GAME_H
