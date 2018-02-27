#include "game.h"

Game::Game()
{

    /*elmentjuk a kepernyo magassagat es szelesseget, ez fontos, mert nem minden telon ugyanaz,
    a dolgok meretet pedig ez alapjan szamoljuk*/
    QScreen *screen = QGuiApplication::primaryScreen();
    screenWidth = screen->geometry().width();
    screenHeight = screen->geometry().height();
    qDebug() << "Screen height: " << screenHeight << ", Screen width: " << screenWidth;

    // scene
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,screenWidth-2,screenHeight-2);

    //view, ez amit a jatekos lat
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(screenWidth,screenHeight);

    //map balra mozgatasa
    mapSlideTimer = new QTimer(this);
    connect(mapSlideTimer, &QTimer::timeout,
            this, &Game::testMove);



    // jatekos letrehozasa
    player = new Character;
    player->setPos(screenWidth/4,screenHeight/2);  //itt majd lesz rendes helye is
    scene->addItem(player);

    //ideiglenes map teszt
    chunk.setParams(scene, 1, "asd");
    qDebug() << scene->items();
    chunk.createChunk();
    qDebug() << scene->items();
    /*Terrain *ground = new Terrain(0, screenHeight*4/5, screenWidth, screenHeight/5, 1);
    wall = new Terrain(0, 0, 100, 100, 2);
    Terrain *bar = new Terrain(0, 0, 100, 100, 3);
    Terrain *bar2 = new Terrain(0, 0, 100, 100, 4);
    wall->setPos(screenWidth/2-250, screenHeight*4/5-100);
    bar->setPos(screenWidth/2+50, screenHeight*4/5-200);
    bar2->setPos(screenWidth/2+250, screenHeight*4/5-350);
    scene->addItem(ground);
    scene->addItem(wall);
    scene->addItem(bar);
    scene->addItem(bar2);
    //ellenfelkereso timer
    checkForAttackSpeed=10;
    checkForAttactT = new QTimer(this);
    connect(checkForAttactT, &QTimer::timeout,
            this, &Game::checkForAttact);
    checkForAttactT->start(checkForAttackSpeed);
    //ellenfel hozzadasa, szinten csak ideiglenes
    //qDebug() << "1";
    spearman = new SpearMan;
    //qDebug() << "2";
    spearman->setPos(screenWidth/2, screenHeight*4/5-400);
    //qDebug() << "3";
    scene->addItem(spearman);
    //qDebug() << "4";*/


    //pause menu
    pauseMenu = new QGraphicsPixmapItem(QPixmap(":/images/images/pauseMenu.png").scaled(QSize(screenHeight*4/5, screenHeight*4/5)));
    scene->addItem(pauseMenu);
    pauseMenu->setPos(screenWidth/2-screenHeight*2/5, screenHeight/5);
    pauseMenu->hide();

    pauseB = new QPushButton(QString("Pause"));
    pauseB->setGeometry(10, 10, screenHeight/10, screenHeight/10);
    scene->addWidget(pauseB);
    connect(pauseB, &QAbstractButton::clicked,
            this, &Game::pauseGame);
    resumeB = new QPushButton(QString("Resume"));
    scene->addWidget(resumeB);
    resumeB->setGeometry(screenWidth/2-screenHeight/4, screenHeight*2/5, screenHeight/2, screenHeight/10);
    resumeB->hide();
    connect(resumeB, &QAbstractButton::clicked,
            this, &Game::resumeGame);

    exitB = new QPushButton(QString("Exit"));
    scene->addWidget(exitB);
    exitB->setGeometry(screenWidth/2-screenHeight/4, screenHeight*3/5, screenHeight/2, screenHeight/10);
    exitB->hide();
    connect(exitB, &QAbstractButton::clicked,
            this, &Game::exitGame);

    //ha minden elokeszulet kesz, megnyitjuk az ablakot, androidon nincs tálca, úgyhogy windowson is fullscreennel kell tesztelni
    showFullScreen();
    mapSlideSpeed=100;
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

void Game::checkForAttact()
{
    if(std::abs(player->pos().y()-spearman->pos().y()) < 200 && std::abs(player->pos().x()-spearman->pos().x()) < 200)
    {
        //qDebug() << "spearman close";
        //spearman->prepAttack();
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
    exitB->show();
    player->moveTimer->stop();
    mapSlideTimer->stop();
    //checkForAttactT->stop();
}

void Game::resumeGame()
{
    pauseMenu->hide();
    resumeB->hide();
    exitB->hide();
    player->moveTimer->start(1);
    mapSlideTimer->start(mapSlideSpeed);
    //checkForAttactT->start(checkForAttackSpeed);
}

void Game::testMove()
{
    //wall->setPos(wall->pos().x()-1, wall->pos().y());
}
