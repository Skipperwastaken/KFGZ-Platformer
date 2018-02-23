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
#include "terrain.h"
#include <QDebug>
#include <QGuiApplication>
#include <QScreen>
#include <QGraphicsPixmapItem>

class Game: public QGraphicsView
{
    Q_OBJECT
public:
    Game();
    ~Game();

    QGraphicsScene * scene;
    int screenHeight, screenWidth;
    Character *player;

    QPushButton * pauseB;
    QGraphicsPixmapItem * pauseMenu;
    QPushButton * resumeB;
    QPushButton * settingB;
    QPushButton * exitB;

    QTimer *mapSlideTimer;
    int mapSlideSpeed;
    Terrain *wall;

    SpearMan *spearman;
    //timer ami alapjan az ellenfelek es a jatekos kozelseget nezi
    QTimer *checkForAttactT;
    int checkForAttackSpeed;

    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);
public slots:
    void checkForAttact();
    void exitGame();
    void pauseGame();
    void resumeGame();
    void testMove();
};

#endif // GAME_H
