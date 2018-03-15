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
    QPushButton * backSettingsButton;
    QPushButton * quitButton;
    //Game mode select buttons:
    QPushButton * backButton;
    QPushButton * endlessGameButton;
    QPushButton * storyGameButton;
    //Story mode buttons:
    QPushButton * backStoryModeButton;
    //Shop buttons
    QPushButton * backShopButton;
    QPushButton * leftHelmetButton;
    QPushButton * leftChestButton;
    QPushButton * leftGlovesButton;
    QPushButton * leftPantsButton;
    QPushButton * leftShoesButton;
    QPushButton * leftWeaponButton;
    QPushButton * rightHelmetButton;
    QPushButton * rightChestButton;
    QPushButton * rightGlovesButton;
    QPushButton * rightPantsButton;
    QPushButton * rightShoesButton;
    QPushButton * rightWeaponButton;
    Game * game;

public slots:
    void startGame();
    void quitApp();
    void openGameModeSelect();
    void closeGameModeSelect();
    void openShop();
    void closeShop();
    void openSettings();
    void closeSettings();
    void openStoryMode();
    void closeStoryMode();

};



#endif // MENU_H
