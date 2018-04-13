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
#include "firewziard.h"
#include "terrain.h"
#include <QDebug>
#include <QGuiApplication>
#include <QScreen>
#include <QGraphicsPixmapItem>
#include <QVector>
#include "enemy.h"
#include "mapchunk.h"
#include <QGraphicsProxyWidget>
#include "terraindata.h"
#include <QFile>
#include <QGraphicsTextItem>

class Game: public QGraphicsView
{
    Q_OBJECT
public:
    Game(QWidget *parent=0);
    ~Game();

    int highScore=0, currentScore=0;
    QGraphicsTextItem * scoreText;

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

    QGraphicsPixmapItem * deathMenu;
    QGraphicsTextItem * finalScore;
    QGraphicsProxyWidget * ohNoProxy;
    QPushButton * ohNoB;



    QVector<TerrainData> terrains;
    void readTerrainFile();
    QVector<ChunkData> chunks;
    void readChunkFile();
    QVector<MapChunk> chunk;
    QTimer *mapSlideTimer;
    int mapSlideSpeed;

    //timer ami alapjan az ellenfelek es a jatekos kozelseget nezi
    QTimer *checkForAttactT;
    int checkForAttackSpeed;

    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);

    //fps
    QTimer *screenUpdateT;
    int fps;
public slots:
    void updateScreen();
    void slideLeft();
    void checkForAttact();
    void exitGame();
    void pauseGame();
    void resumeGame();
    void died();
    void increaseScore(int amount);
};

#endif // GAME_H
