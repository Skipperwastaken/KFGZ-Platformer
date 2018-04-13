#include "mapchunk.h"
#include <typeinfo>
#include <QRandomGenerator>

MapChunk::MapChunk()
{
}

void MapChunk::setParams(QGraphicsScene *scn, int lvl, QString thm, QVector<TerrainData> &trns, QVector<ChunkData> &chnks)
{
    scene = scn;
    level = lvl;
    theme = thm;
    screenHeight = scene->height();
    screenWidth = scene->width();
    terrainList=&trns;
    chunkList=&chnks;
}

void MapChunk::setParams(QGraphicsScene *scn, int lvl, QString thm, QVector<TerrainData> &trns, QVector<ChunkData> &chnks, bool frst)
{
    scene = scn;
    level = lvl;
    theme = thm;
    screenHeight = scene->height();
    screenWidth = scene->width();
    terrainList=&trns;
    chunkList=&chnks;
    first=frst;
    if(first)
        deleteDistance=screenHeight/9*16;
}

void MapChunk::slideLeft()
{
    for(int i=0; i < terrains.length(); i++)
        terrains[i]->moveBy(-1, 0);
    for(int i=0; i < enemies.length(); i++)
        enemies[i]->moveBy(-1, 0);
    if(deleteDistance++>screenHeight/9*16*2)
    {
        deleteChunk();
        deleteDistance=0;
    }
    //if(terrains.at(0)->pos().x() < screenWidth/2-screenHeight/9*24)
    //    deleteChunk();
}

void MapChunk::createChunk()
{
    //qDebug() << "Create chunk";
    //get random num
    int randomChunkID=QRandomGenerator::global()->generate()%chunkList->length();
    //sok sikert ennek megertesehez, sok a kommentezett debug, mert sokat szenvedtem vele
    //a chunkok kozul a kivalasztottbol a teraindata alapjan megalkotja a terrain objektumot
    //qDebug() << "creating terrains";
    //qDebug() << "Number of terrains should be : " << chunkList->at(randomChunkID).terrainID.length();
    for(int i=0; i < chunkList->at(randomChunkID).terrainID.length();i++)
        terrains.append(new Terrain(0, 0, terrainList->at(chunkList->at(randomChunkID).terrainID.at(i)).w, terrainList->at(chunkList->at(randomChunkID).terrainID.at(i)).h, chunkList->at(randomChunkID).terrainID.at(i)));

    for(int i=0; i < chunkList->at(randomChunkID).enemyType.length();i++)
    {
        switch (chunkList->at(randomChunkID).enemyType.at(i)) {
        case 0: //spearman
            enemies.append(new SpearMan);
            break;
        default:
            enemies.append(new SpearMan);
            break;
        }
    }

    //terrainnak megadja a helyet es hozzaadja a scenehez
    //qDebug() << "adding terrain to scene";
    //qDebug() << "Number of terrains: " << terrains.length();
    for(int i=0;i<terrains.length();i++)
    {
        terrains[i]->setPos(screenWidth/2-screenHeight/9*8+chunkList->at(randomChunkID).terrainX.at(i)+(first ? 0 : screenHeight/9*16), chunkList->at(randomChunkID).terrainY.at(i));
        scene->addItem(terrains.at(i));
        //qDebug() << terrains.at(i)->pos().x() << " | " << terrains.at(i)->pos().y();
    }

    for(int i=0; i < enemies.length(); i++)
    {
        enemies[i]->setPos(screenWidth/2-screenHeight/9*8+chunkList->at(randomChunkID).enemyX.at(i)+(first ? 0 : screenHeight/9*16), chunkList->at(randomChunkID).enemyY.at(i));
        scene->addItem(enemies[i]);
    }

    first=false;
    //qDebug() << "Create chunk end";
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
