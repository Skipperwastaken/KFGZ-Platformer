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
    ~Menu();
    QGraphicsScene * scene;
    int screenHeight, screenWidth;
    //Main menu buttons:
    QPushButton * playButton;
    QPushButton * shopButton;
    QPushButton * settingsButton;
    QPushButton * quitButton;
    //Shop buttons:
    QPushButton * backShopButton;
    //Settings buttons:
    QPushButton * backSettingsButton;
    //Game mode select buttons:
    QPushButton * backButton;
    QPushButton * endlessGameButton;
    QPushButton * storyGameButton;
    //Story mode buttons:
    QPushButton * backStoryModeButton;
    QGraphicsProxyWidget *gameProxy;
    Game * game;

public slots:
    void startGame();
    void quitApp();
    void openShop();
    void closeShop();
    void openSettings();
    void closeSettings();
    void openGameModeSelect();
    void closeGameModeSelect();
    void openStoryMode();
    void closeStoryMode();
};


#endif // MENU_H
