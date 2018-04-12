#ifndef MAPCHUNK_H
#define MAPCHUNK_H
#include <QString>
#include <QVector>
#include "terrain.h"
#include "enemy.h"
#include "spearman.h"
#include "firewziard.h"
#include <QDebug>
#include <QGraphicsScene>
#include <chunkdata.h>
#include "terraindata.h"

class MapChunk
{
public:
    MapChunk();
    int screenWidth, screenHeight;
    QGraphicsScene *scene;
    int level;
    QString theme; //forest, winter, town, etc.
    int deleteDistance=0;

    QVector<TerrainData> *terrainList;
    QVector<ChunkData> *chunkList;

    QVector<Terrain*> terrains;
    QVector<Enemy*> enemies;
    void setParams(QGraphicsScene *scn, int lvl, QString thm, QVector<TerrainData> &trns, QVector<ChunkData> &chnks);
    void setParams(QGraphicsScene *scn, int lvl, QString thm, QVector<TerrainData> &trns, QVector<ChunkData> &chnks, bool frst);
    bool first=false;
    void createChunk();
    void deleteChunk();
public slots:
    void slideLeft();
};

#endif // MAPCHUNK_H
