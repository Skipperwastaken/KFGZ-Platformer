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

void MapChunk::slideLeft()
{

}

void MapChunk::createChunk()
{
    terrains.append(new Terrain(0, 0, screenWidth, screenHeight/5, 1));
    terrains.append(new Terrain(0, 0, screenHeight/10, screenHeight/10, 1));
    enemies.append(new SpearMan);
    /*
    wall = new Terrain(0, 0, 100, 100, 2);
    Terrain *bar = new Terrain(0, 0, 100, 100, 3);
    Terrain *bar2 = new Terrain(0, 0, 100, 100, 4);
    wall->setPos(screenWidth/2-250, screenHeight*4/5-100);
    bar->setPos(screenWidth/2+50, screenHeight*4/5-200);
    bar2->setPos(screenWidth/2+250, screenHeight*4/5-350);
    scene->addItem(ground);
    scene->addItem(wall);
    scene->addItem(bar);
    scene->addItem(bar2);*/
    terrains[0]->setPos(0, screenHeight*4/5);
    terrains[1]->setPos(screenWidth/3, screenHeight*7/10);
    enemies[0]->setPos(screenWidth/2, screenHeight*4/5-200);
    for(int i=0; i < terrains.length(); i++)
        scene->addItem(terrains[i]);
    for(int i=0; i < enemies.length(); i++)
        scene->addItem(enemies[i]);
}
