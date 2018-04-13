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
    readTerrainFile();
    readChunkFile();
    MapChunk tmpMC;
    for(int i = 0 ; i < 2; i++)
        chunk.append(tmpMC);
    chunk[0].setParams(scene, 0, "asd", terrains, chunks, true);
    chunk[1].setParams(scene, 0, "asd", terrains, chunks);
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

    //meghaltal menu
    deathMenu = new QGraphicsPixmapItem(QPixmap(":/images/images/deathPopup.png").scaled(QSize(screenHeight*4/5, screenHeight*4/5)));
    scene->addItem(deathMenu);
    deathMenu->setPos(screenWidth/2-screenHeight*2/5, screenHeight/5);
    deathMenu->setZValue(10);
    deathMenu->hide();

    connect(player, &Character::died,
            this, &Game::died);

    ohNoB = new QPushButton(QString("Oh no!"));
    ohNoProxy = new QGraphicsProxyWidget(deathMenu);
    ohNoProxy->setWidget(ohNoB);
    ohNoB->setGeometry(screenHeight/10, screenHeight*12/30, screenHeight*6/10, screenHeight/10);
    ohNoB->hide();
    connect(ohNoB, &QAbstractButton::clicked,
            this, &Game::exitGame);

    finalScore=new QGraphicsTextItem;
    scene->addItem(finalScore);
    finalScore->setPos(screenWidth/2-130, screenHeight/2-100);
    finalScore->setFont(QFont("times",32));
    finalScore->setZValue(1111);
    finalScore->hide();

    //ha minden elokeszulet kesz, megnyitjuk az ablakot, androidon nincs tálca, úgyhogy windowson is fullscreennel kell tesztelni
    showFullScreen();
    mapSlideSpeed=3;
    mapSlideTimer->start(mapSlideSpeed);

    //setViewportUpdateMode(NoViewportUpdate);
    //screenUpdateT = new QTimer(this);
    //fps=60;
    //screenUpdateT->start(1000/fps);
    //connect(screenUpdateT, &QTimer::timeout,
    //        this, &Game::updateScreen);

    scoreText=new QGraphicsTextItem;
    scene->addItem(scoreText);
    scoreText->setPos(screenWidth-140, 10);
    scoreText->setFont(QFont("times",16));
    scoreText->setZValue(1111);
    scoreText->setPlainText(QString("Distance: ") + QString::number(highScore));
    connect(player, &Character::moved,
            this, &Game::increaseScore);


}

//jatekos iranyitasa, lehetne a character classban is, de ott nehezebb bug mentesre megcsinalni
void Game::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_W){
        if(!event->isAutoRepeat() && player->jumpsLeft>0)
        {
            player->yVelocity=6;
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

void Game::updateScreen()
{
    scene->update();
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
                if(!chunk.at(j).enemies.at(i)->killConnect)
                {
                    chunk[j].enemies[i]->killConnect=true;
                    connect(chunk[j].enemies[i], &Enemy::hit,
                            this, &Game::died);
                }
                if(std::abs(player->pos().y() - chunk.at(j).enemies.at(i)->pos().y()) < 200 && std::abs(player->pos().x()-chunk.at(j).enemies.at(i)->pos().x()) < 700)
                {
                    QList<QGraphicsItem*> enemyCollisions = chunk.at(j).enemies.at(i)->model->collidingItems();
                    for (int w = 0; w < enemyCollisions.size(); w++)
                    {
                        if (typeid(*(enemyCollisions.at(w))) == typeid(Character))
                        {
                            //qDebug() << "player hits someone";
                            chunk[j].enemies[i]->die();
                            //TODO: player attack animation
                            return;
                        }
                    }
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

void Game::readTerrainFile()
{
    TerrainData tmpTerrain;
    double a, b;
    int j=0;

    QFile terrainFiles(":/data/data/terrains.txt");
    if (!terrainFiles.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

    QTextStream in(&terrainFiles);
    qDebug() << in.atEnd();
    while(!in.atEnd())
    {
        in >> a;
        //qDebug() << a;
        in >> b;
        tmpTerrain.setData(a/100*screenHeight, b/100*screenHeight);
        tmpTerrain.id=j++;
        terrains.append(tmpTerrain);
    }
    qDebug() << "readTerrainFile finished loading";
    terrainFiles.close();
}

void Game::readChunkFile()
{
    ChunkData tmpChunk;
    double a=0;
    QString c;
    int inType=0; //0=terrain, 1 enemy

    QFile chunkFiles(":/data/data/chunkText.txt");
    if (!chunkFiles.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

    QTextStream chnkStream(&chunkFiles);
    qDebug() << chnkStream.atEnd();
    while(!chnkStream.atEnd())
    {
        qDebug() << "started reading readChunkFile";
        chnkStream >> c;
        qDebug() << c;
        if(c=="c")
        {
            if(tmpChunk.terrainID.length()!=0)
            {
                chunks.append(tmpChunk);

                tmpChunk.enemyType.clear();
                tmpChunk.enemyX.clear();
                tmpChunk.enemyY.clear();
                tmpChunk.terrainID.clear();
                tmpChunk.terrainX.clear();
                tmpChunk.terrainY.clear();
            }
        }
        else if(c=="t")
            inType=0;
        else if(c=="e")
            inType=1;
        else
        {
            a=c.toDouble();
            switch (inType) {
            case 0:
                tmpChunk.terrainID.append(a);
                //qDebug() << tmpChunk.terrainID.at(0);
                chnkStream >> a;
                tmpChunk.terrainX.append(a/100*screenHeight);
                chnkStream >> a;
                tmpChunk.terrainY.append(a/100*screenHeight);
                break;
            case 1:
                tmpChunk.enemyType.append(a);
                chnkStream >> a;
                tmpChunk.enemyX.append(a/100*screenHeight);
                chnkStream >> a;
                tmpChunk.enemyY.append(a/100*screenHeight);
                break;
            default:
                qDebug() <<  inType << " inType doesnt exist";
                break;
            }
        }
    }
    qDebug() << "readChunkFile finished loading";
    chunks.append(tmpChunk);
    chunkFiles.close();

/*
    ChunkData tmpChunk;

    tmpChunk.terrainID.append(0);
    tmpChunk.terrainX.append(0);
    tmpChunk.terrainY.append(screenHeight*4/5);

    tmpChunk.terrainID.append(1);
    tmpChunk.terrainX.append(screenWidth/2);
    tmpChunk.terrainY.append(screenHeight*3/5);

    tmpChunk.enemyType.append(0);
    tmpChunk.enemyX.append(screenWidth/4*3);
    tmpChunk.enemyY.append(screenHeight*4/5-200);

    chunks.append(tmpChunk);*/
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

void Game::died()
{
    pauseGame();
    deathMenu->show();
    ohNoB->show();
    player->moveTimer->stop();
    mapSlideTimer->stop();
    checkForAttactT->stop();
    finalScore->setPlainText(QString("Distance: ") + QString::number(highScore/100));
    finalScore->show();
}

void Game::increaseScore(int amount)
{
    qDebug() << "amount";
    currentScore+=amount;
    if(currentScore>highScore)
    {
        highScore=currentScore;
        scoreText->setPlainText(QString("Distance: ") + QString::number(highScore/100));
    }
    //TODO: delete these
    if(highScore/100>=500)
    {
        deathMenu->setPixmap(QPixmap(":/images/images/victoryPopup.png").scaled(QSize(screenHeight*4/5, screenHeight*4/5)));
        ohNoB->setText("Kérem a csokimat!");
        died();
    }
}
