#include "game.h"

Game::Game(QWidget *parent): QGraphicsView(parent)
{

    /*elmentjuk a kepernyo magassagat es szelesseget, ez fontos, mert nem minden telon ugyanaz,
    a dolgok meretet pedig ez alapjan szamoljuk*/
    QScreen *screen = QGuiApplication::primaryScreen();
    screenWidth = screen->geometry().width();
    screenHeight = screen->geometry().height();
    qDebug() << "Screen height: " << screenHeight << ", Screen width: " << screenWidth;

    // scene
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,screenWidth,screenHeight);

    //view, ez amit a jatekos lat
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(screenWidth,screenHeight);


    // jatekos letrehozasa
    player = new Character;
    player->setPos(screenWidth/4,screenHeight/2);  //itt majd lesz rendes helye is
    scene->addItem(player);

    //map chunkok letrehozasa
    MapChunk tmpMC;
    for(int i = 0 ; i < 2; i++)
        chunk.append(tmpMC);
    chunk[0].setParams(scene, 0, "asd", true);
    chunk[1].setParams(scene, 0, "asd");
    for(int i = 0 ; i < 2; i++)
        chunk[i].createChunk();
    //map balra mozgatasa
    mapSlideTimer = new QTimer(this);
    connect(mapSlideTimer, &QTimer::timeout,
        this, &Game::slideLeft);

    //ellenfelkereso timer
    checkForAttackSpeed=10;
    checkForAttactT = new QTimer(this);
    connect(checkForAttactT, &QTimer::timeout,
            this, &Game::checkForAttact);
    checkForAttactT->start(checkForAttackSpeed);

    //pause menu
    pauseMenu = new QGraphicsPixmapItem(QPixmap(":/images/images/pauseMenu.png").scaled(QSize(screenHeight*4/5, screenHeight*4/5)));
    scene->addItem(pauseMenu);
    pauseMenu->setPos(screenWidth/2-screenHeight*2/5, screenHeight/5);
    pauseMenu->setZValue(10);
    pauseMenu->hide();

    pauseB = new QPushButton(QString("Pause"));
    pauseB->setGeometry(10, 10, screenHeight/10, screenHeight/10);
    scene->addWidget(pauseB);
    connect(pauseB, &QAbstractButton::clicked,
            this, &Game::pauseGame);

    resumeB = new QPushButton(QString("Resume"));
    resumeProxy = new QGraphicsProxyWidget(pauseMenu);
    resumeProxy->setWidget(resumeB);
    resumeB->setGeometry(screenHeight/10, screenHeight*4/30, screenHeight*6/10, screenHeight/10);
    resumeB->hide();
    connect(resumeB, &QAbstractButton::clicked,
            this, &Game::resumeGame);

    settingB = new QPushButton(QString("Settings"));
    settingProxy = new QGraphicsProxyWidget(pauseMenu);
    settingProxy->setWidget(settingB);
    settingB->setGeometry(screenHeight/10, screenHeight*8/30, screenHeight*6/10, screenHeight/10);
    resumeB->hide();

    exitB = new QPushButton(QString("Exit"));
    exitProxy = new QGraphicsProxyWidget(pauseMenu);
    exitProxy->setWidget(exitB);
    exitB->setGeometry(screenHeight/10, screenHeight*12/30, screenHeight*6/10, screenHeight/10);
    exitB->hide();
    connect(exitB, &QAbstractButton::clicked,
            this, &Game::exitGame);

    //ha minden elokeszulet kesz, megnyitjuk az ablakot, androidon nincs tálca, úgyhogy windowson is fullscreennel kell tesztelni
    showFullScreen();
    mapSlideSpeed=3;
    mapSlideTimer->start(mapSlideSpeed);
}

//jatekos iranyitasa, lehetne a character classban is, de ott nehezebb bug mentesre megcsinalni
void Game::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_W){
        if(!event->isAutoRepeat() && player->jumpsLeft>0)
        {
            player->yVelocity=0.6;
            player->jumpsLeft--;
        }
        player->jumping=true;
        //qDebug() << "Jump";
    }
    if (event->key() == Qt::Key_A){
        player->goingLeft=true;
        //qDebug() << "Left";
    }
    if (event->key() == Qt::Key_D){
        player->goingRight=true;
        //qDebug() << "Right";
    }
    if (event->key() == Qt::Key_S){
        player->sliding=true;
        //qDebug() << "Slide";
    }
}

void Game::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_W){
        player->jumping=false;
        //qDebug() << "Jump key released";
    }
    if (event->key() == Qt::Key_A){
        player->goingLeft=false;
        //qDebug() << "Left key released";
    }
    if (event->key() == Qt::Key_D){
        player->goingRight=false;
        //qDebug() << "Right key released";
    }
    if (event->key() == Qt::Key_S){
        player->sliding=false;
        //qDebug() << "Slide key released";
    }
}

void Game::slideLeft()
{
    for(int i=0; i < 2; i++)
    {
        chunk[i].slideLeft();
    }
}

void Game::checkForAttact()
{
    for(int j=0; j < 2; j++)
    {
        for(int i=0; i < chunk[j].enemies.length(); i++)
        {
            if(!chunk.at(j).enemies.at(i)->dead)
            {
                if(std::abs(player->pos().y() - chunk[j].enemies.at(i)->pos().y()) < 200 && std::abs(player->pos().x()-chunk[j].enemies.at(i)->pos().x()) < 200)
                {
                    QList<QGraphicsItem*> enemyCollisions = chunk.at(j).enemies.at(i)->model->collidingItems();
                    for (int w = 0, n = enemyCollisions.size(); w < n; ++w)
                    {

                        if (typeid(*(enemyCollisions.at(w))) == typeid(Character))
                        {
                            //qDebug() << "player hits someone";
                            chunk[j].enemies[i]->die();
                            //TODO: player attack animation
                            return;
                        }
                    }
                    //qDebug() << "spearman close";
                    chunk[j].enemies.at(i)->prepAttack();
                }
            }
        }
    }
}

Game::~Game()
{
    qDebug() << "game deleted";
}


void Game::exitGame()
{
    close();
}

void Game::pauseGame()
{
    //TODO: ha mar elkezdodott egy attack, akkor azt nem pausolja
    pauseMenu->show();
    resumeB->show();
    settingB->show();
    exitB->show();
    player->moveTimer->stop();
    mapSlideTimer->stop();
    checkForAttactT->stop();
}

void Game::resumeGame()
{
    pauseMenu->hide();
    resumeB->hide();
    settingB->show();
    exitB->hide();
    player->moveTimer->start(1);
    mapSlideTimer->start(mapSlideSpeed);
    checkForAttactT->start(checkForAttackSpeed);
}
