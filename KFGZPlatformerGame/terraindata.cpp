#include "terraindata.h"
#include <QDebug>
TerrainData::TerrainData()
{
    qDebug() << "Terrain data created";
}

void TerrainData::setData(int width, int height)
{
    h=height;
    w=width;
}
