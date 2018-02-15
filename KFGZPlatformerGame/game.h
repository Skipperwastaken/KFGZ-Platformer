#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>

class Game: public QGraphicsView{
    Q_OBJECT
public:
    Game(QWidget * parent=0);

    QGraphicsScene * scene;

    int screenHeight, screenWidth;
};

#endif // GAME_H
