#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include "character.h"
#include <QPushButton>
#include <QKeyEvent>
#include <QTimer>
#include <cmath>
#include "spearman.h"

class Game: public QGraphicsView
{
    Q_OBJECT
public:
    Game();
    ~Game();

    QGraphicsScene * scene;
    int screenHeight, screenWidth;
    Character *player;
    QPushButton * exitButton;

    SpearMan *spearman;
    //timer ami alapjan az ellenfelek es a jatekos kozelseget nezi
    QTimer *checkForAttactT;

    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);
public slots:
    void checkForAttact();
    void exitGame();
};

#endif // GAME_H
