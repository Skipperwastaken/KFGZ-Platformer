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
    qDebug() << screenHeight << " " << screenWidth;

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

    //shop button
    shopButton = new QPushButton(QString("Shop"));
    shopButton->setGeometry(QRect(QPoint(screenWidth/30,screenHeight-(screenHeight/4)-2*(screenHeight/6)-2*(screenHeight/30)),QSize(screenWidth/3, screenHeight/6)));
    scene->addWidget(shopButton);

    //settings button

    settingsButton = new QPushButton(QString("Settings"));
    settingsButton->setGeometry(QRect(QPoint(screenWidth/30,screenHeight-(screenHeight/4)-(screenHeight/6)-(screenHeight/30)),QSize(screenWidth/3, screenHeight/6)));
    scene->addWidget(settingsButton);

    //quit button

    quitButton = new QPushButton(QString("Quit"));
    quitButton->setGeometry(QRect(QPoint(screenWidth/30,screenHeight-(screenHeight/4)),QSize(screenWidth/3, screenHeight/6)));
    scene->addWidget(quitButton);
    connect(quitButton,SIGNAL(clicked()),this, SLOT(quitGame()));




    //fullscreen

    showFullScreen();

}

void Menu::quitGame()
{
    close();
}

