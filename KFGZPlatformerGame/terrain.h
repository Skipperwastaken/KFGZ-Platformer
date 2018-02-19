#ifndef TERRAIN_H
#define TERRAIN_H

#include <QGraphicsRectItem>
#include <QBrush>
#include <QDebug>

class Terrain: public QGraphicsRectItem
{
public:
    Terrain(int x, int y, int width, int height, int ID);
    ~Terrain();
private:
    int textureID;
};

#endif // TERRAIN_H
