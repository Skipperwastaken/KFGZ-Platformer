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
#include <QVector>
#include "enemy.h"
#include "mapchunk.h"
#include <QGraphicsProxyWidget>

class Game: public QGraphicsView
{
    Q_OBJECT
public:
    Game(QWidget *parent=0);
    ~Game();

    QGraphicsScene * scene;
    int screenHeight, screenWidth;
    Character *player;

    QPushButton * pauseB;
    QGraphicsPixmapItem * pauseMenu;
    QGraphicsProxyWidget * resumeProxy;
    QPushButton * resumeB;
    QGraphicsProxyWidget * settingProxy;
    QPushButton * settingB;
    QGraphicsProxyWidget * exitProxy;
    QPushButton * exitB;

    QVector<MapChunk> chunk;
    QTimer *mapSlideTimer;
    int mapSlideSpeed;

    //timer ami alapjan az ellenfelek es a jatekos kozelseget nezi
    QTimer *checkForAttactT;
    int checkForAttackSpeed;

    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);
public slots:
    void slideLeft();
    void checkForAttact();
    void exitGame();
    void pauseGame();
    void resumeGame();
};

#endif // GAME_H
