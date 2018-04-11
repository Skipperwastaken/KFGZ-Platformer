#ifndef CHUNKDATA_H
#define CHUNKDATA_H

#include <QVector>
#include "terraindata.h"
#include <QString>


class ChunkData
{
public:
    ChunkData();
    QVector<int> terrainID;
    QVector<int> terrainX;
    QVector<int> terrainY;
    QVector<int> enemyType;
    QVector<int> enemyX;
    QVector<int> enemyY;
};

#endif // CHUNKDATA_H
