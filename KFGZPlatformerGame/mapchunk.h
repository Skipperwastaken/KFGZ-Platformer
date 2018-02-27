#ifndef MAPCHUNK_H
#define MAPCHUNK_H
#include <QString>
#include <QVector>
#include "terrain.h"
#include "enemy.h"
#include "spearman.h"
#include <QDebug>
#include <QGraphicsScene>

class MapChunk
{
public:
    MapChunk();
    int screenWidth, screenHeight;
    QGraphicsScene *scene;
    int level;
    QString theme; //forest, winter, town, etc.
    QVector<Terrain*> terrains;
    QVector<Enemy*> enemies;
    void setParams(QGraphicsScene *scn, int lvl, QString thm);
    void slideLeft();
    void createChunk();
};

#endif // MAPCHUNK_H
