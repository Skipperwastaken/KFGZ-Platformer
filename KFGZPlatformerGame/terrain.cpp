#include "terrain.h"

Terrain::Terrain(int x, int y, int width, int height, int ID)
:   QGraphicsRectItem(x, y, width, height)
{
    //melyik texturat hasznalja
    textureID=ID;
    //egyelore csak szint ad neki, kesobb majd lesz itt egy pixmap
    setBrush(QBrush(QColor(ID*23423432%255, ID*2342%255, ID*2345%255)));
}

Terrain::~Terrain()
{
    //qDebug() << "terrain id: " << textureID << "deleted";
}
