#include "mapchunk.h"
#include <typeinfo>

MapChunk::MapChunk()
{
}

void MapChunk::setParams(QGraphicsScene *scn, int lvl, QString thm)
{
    scene = scn;
    level = lvl;
    theme = thm;
    screenHeight = scene->height();
    screenWidth = scene->width();
}

void MapChunk::setParams(QGraphicsScene *scn, int lvl, QString thm, bool frst)
{
    scene = scn;
    level = lvl;
    theme = thm;
    screenHeight = scene->height();
    screenWidth = scene->width();
    first=frst;
}

void MapChunk::slideLeft()
{
    for(int i=0; i < terrains.length(); i++)
        terrains[i]->moveBy(-1, 0);
    for(int i=0; i < enemies.length(); i++)
        enemies[i]->moveBy(-1, 0);
    if(terrains.at(0)->pos().x() < -screenWidth)
        deleteChunk();
}

void MapChunk::createChunk()
{
    terrains.append(new Terrain(0, 0, screenWidth, screenHeight/5, 1));
    terrains.append(new Terrain(0, 0, screenHeight/10, screenHeight/10, 1));
    enemies.append(new FireWizard);

    terrains[0]->setPos(0+(first ? 0 : screenWidth), screenHeight*4/5);
    terrains[1]->setPos(screenWidth/3+(first ? 0 : screenWidth), screenHeight*7/10);
    enemies[0]->setPos(screenWidth/2+(first ? 0 : screenWidth), screenHeight*4/5-200);
    for(int i=0; i < terrains.length(); i++)
        scene->addItem(terrains[i]);
    for(int i=0; i < enemies.length(); i++)
        scene->addItem(enemies[i]);
    first=false;
}

void MapChunk::deleteChunk()
{
    qDebug() << "deleteChunk";
    for(int i=0; i < terrains.length(); i++)
    {
        scene->removeItem(terrains[i]);
        delete terrains[i];
    }
    terrains.clear();
    for(int i=0; i < enemies.length(); i++)
    {
        scene->removeItem(enemies[i]);
        delete enemies[i];
    }
    enemies.clear();
    createChunk();
}
