#include <QGuiApplication>
#include <QScreen>
#include <QDebug>
#include "menu.h"
#include "game.h"
#include <Qdialog>


Menu::Menu()
{
    //Az a fontos dolog...telók nem ugyanolyanok dsdsds
    QScreen *screen = QGuiApplication::primaryScreen();
    screenWidth = screen->geometry().width();
    screenHeight = screen->geometry().height();
    //qDebug() << screenHeight << " " << screenWidth;

    //creating scene
    scene = new QGraphicsScene(this);
    setSceneRect(0,0,screenWidth-2,screenHeight-2);

    //view
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(screenWidth,screenHeight);

    //creating buttons
    //play button

    playButton = new QPushButton(QString("Play"));
    playButton->setGeometry(QRect(QPoint(screenWidth/30,screenHeight-(screenHeight/4)-3*(screenHeight/6)-3*(screenHeight/30)),QSize(screenWidth/3, screenHeight/6)));
    scene->addWidget(playButton);
    connect(playButton, &QAbstractButton::clicked,
            this, &Menu::openGameModeSelect);

    //shop button
    shopButton = new QPushButton(QString("Shop"));
    shopButton->setGeometry(QRect(QPoint(screenWidth/30,screenHeight-(screenHeight/4)-2*(screenHeight/6)-2*(screenHeight/30)),QSize(screenWidth/3, screenHeight/6)));
    scene->addWidget(shopButton);
    connect(shopButton, &QAbstractButton::clicked,
            this, &Menu::openShop);

    //shop back button
    backShopButton = new QPushButton(QString("Back"));
    backShopButton->setGeometry(10, 10, screenHeight/10, screenHeight/10);
    scene->addWidget(backShopButton);
    connect(backShopButton, &QAbstractButton::clicked,
            this, &Menu::closeShop);
    backShopButton->hide();


    //settings button

    settingsButton = new QPushButton(QString("Settings"));
    settingsButton->setGeometry(QRect(QPoint(screenWidth/30,screenHeight-(screenHeight/4)-(screenHeight/6)-(screenHeight/30)),QSize(screenWidth/3, screenHeight/6)));
    scene->addWidget(settingsButton);
    connect(settingsButton, &QAbstractButton::clicked,
            this, &Menu::openSettings);

    //settings back button

    backSettingsButton = new QPushButton(QString("Back"));
    backSettingsButton->setGeometry(10, 10, screenHeight/10, screenHeight/10);
    scene->addWidget(backSettingsButton);
    connect(backSettingsButton, &QAbstractButton::clicked,
            this, &Menu::closeSettings);
    backSettingsButton->hide();
    //quit button

    quitButton = new QPushButton(QString("Quit"));
    quitButton->setGeometry(QRect(QPoint(screenWidth/30,screenHeight-(screenHeight/4)),QSize(screenWidth/3, screenHeight/6)));
    scene->addWidget(quitButton);
    connect(quitButton, &QAbstractButton::clicked,
            this, &Menu::quitApp);

    //Creating level select/game mode buttons
    //Game mode back button
    backButton = new QPushButton(QString("Back"));
    backButton->setGeometry(10, 10, screenHeight/10, screenHeight/10);
    scene->addWidget(backButton);
    connect(backButton, &QAbstractButton::clicked,
            this, &Menu::closeGameModeSelect);
    backButton->hide();

    //Game mode: endless button
    endlessGameButton = new QPushButton(QString("Endless"));
    endlessGameButton->setGeometry(QRect(QPoint(screenWidth/8,screenHeight/4),QSize(screenWidth/4, screenHeight/2)));
    scene->addWidget(endlessGameButton);
    connect(endlessGameButton, &QAbstractButton::clicked,
            this, &Menu::startGame);
    endlessGameButton->hide();

    //Game mode: story button
    storyGameButton = new QPushButton(QString("Story"));
    storyGameButton->setGeometry(QRect(QPoint(screenWidth/8*5,screenHeight/4),QSize(screenWidth/4, screenHeight/2)));
    scene->addWidget(storyGameButton);
    connect(storyGameButton, &QAbstractButton::clicked,
            this, &Menu::openStoryMode);
    storyGameButton->hide();

    //Story mode back button
    backStoryModeButton = new QPushButton(QString("Back"));
    backStoryModeButton->setGeometry(10, 10, screenHeight/10, screenHeight/10);
    scene->addWidget(backStoryModeButton);
    connect(backStoryModeButton, &QAbstractButton::clicked,
            this, &Menu::closeStoryMode);
    backStoryModeButton->hide();

    //fullscreen

    showFullScreen();
}

Menu::~Menu()
{
    qDebug() << "Menu deleted";
}

void Menu::startGame()
{
    game = new Game;
    /* TODO gameProxy = new QGraphicsProxyWidget(scene);
    gameProxy->setWidget(game);
    gameProxy->setZValue(10);*/
    game->setAttribute(Qt::WA_DeleteOnClose);
}

void Menu::quitApp()
{
    close();
}

void Menu::openShop()
{
    playButton->hide();
    shopButton->hide();
    settingsButton->hide();
    quitButton->hide();
    backShopButton->show();
}

void Menu::closeShop()
{
    playButton->show();
    shopButton->show();
    settingsButton->show();
    quitButton->show();
    backShopButton->hide();
}
void Menu::openSettings()
{
    playButton->hide();
    shopButton->hide();
    settingsButton->hide();
    quitButton->hide();
    backSettingsButton->show();
}

void Menu::closeSettings()
{
    playButton->show();
    shopButton->show();
    settingsButton->show();
    quitButton->show();
    backSettingsButton->hide();
}

void Menu::openGameModeSelect()
{
    playButton->hide();
    shopButton->hide();
    settingsButton->hide();
    quitButton->hide();
    backButton->show();
    endlessGameButton->show();
    storyGameButton->show();
}

void Menu::closeGameModeSelect()
{
    playButton->show();
    shopButton->show();
    settingsButton->show();
    quitButton->show();
    backButton->hide();
    endlessGameButton->hide();
    storyGameButton->hide();
}

void Menu::openStoryMode()
{
    backButton->hide();
    endlessGameButton->hide();
    storyGameButton->hide();
    backStoryModeButton->show();
}

void Menu::closeStoryMode()
{
    backButton->show();
    endlessGameButton->show();
    storyGameButton->show();
    backStoryModeButton->hide();
}
