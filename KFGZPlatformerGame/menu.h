#ifndef MENU_H
#define MENU_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QPushButton>
#include <QTextEdit>
#include <QLineEdit>
#include "game.h"

class Menu: public QGraphicsView{
    Q_OBJECT
public:
    Menu();

    QGraphicsScene * scene;
    int screenHeight, screenWidth;
    QPushButton * playButton;
    QPushButton * shopButton;
    QPushButton * settingsButton;
    QPushButton * quitButton;
    Game * game;
public slots:
    void startGame();
    void quitApp();


};


#endif // MENU_H
