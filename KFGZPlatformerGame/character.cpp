#include "character.h"
#include "terrain.h"


Character::Character(QGraphicsItem *parent): QGraphicsRectItem(parent)
{
    // karakter kepe, kesobb majd animalni kell
    setRect(0, 0, 100, 200);
    setPen(QPen(QColor(0,0,0,0)));
    model=new QGraphicsPixmapItem(QPixmap(":/images/images/character.png").scaled(QSize(100, 200)), this);
    model->setShapeMode(QGraphicsPixmapItem::HeuristicMaskShape);

    //QLine itemek, ezekkel tud erintkezni a kornyezettel a karakter
    top = new QGraphicsLineItem(20, 1, 80, 1, this);
    top->setPen(QPen(QColor(0,0,0,0), 0));
    right = new QGraphicsLineItem(99, 20, 99, 180, this);
    right->setPen(QPen(QColor(0,0,0,0), 4));
    bottom = new QGraphicsLineItem(20, 199, 80, 199, this);
    bottom->setPen(QPen(QColor(0,0,0,0), 4));
    left = new QGraphicsLineItem(1, 20, 1, 180, this);
    left->setPen(QPen(QColor(0,0,0,0), 4));

    //timer, annyi idokozonkent mozog a karakter
    moveTimer=new QTimer(this);
    connect(moveTimer,SIGNAL(timeout()),this,SLOT(move()));
    moveTimer->start(10);

    //csuszas
    slidingTimer=new QTimer(this);
    connect(slidingTimer,SIGNAL(timeout()),this,SLOT(stopSliding()));
    slidingTimer->setSingleShot(true);
    slidingCD=new QTimer(this);
    slidingCD->setSingleShot(true);
}

Character::~Character()
{
    qDebug() << "Character deleted";
}

void Character::move()
{
    if(pos().y()>1500)
        emit died();
    //gravitacio
    yVelocity -= (jumping && yVelocity>0 ? 0.08 : 0.14);

    //fal erzekeles reset
    wallLeft=false;
    wallRight=false;

    //foldon van-e
    bottomCollidingItems = bottom->collidingItems();
    for (int i = 0, n = bottomCollidingItems.size(); i < n; ++i)
    {
        //ha erintkezik a folddel, akkor nem eshet es csak akkor csuszhat
        if (typeid(*(bottomCollidingItems.at(i))) == typeid(Terrain))
        {
            //eses megallitasa
            yVelocity = (yVelocity < 0 ? 0 : yVelocity);
            int tempNum=bottomCollidingItems[i]->scenePos().y();
            //qDebug() << tempNum << " " << pos().y()+200;
            if(tempNum<pos().y()+200)
            {
                //qDebug() << "in ground";
                setPos(x(), tempNum-200);
            }
            //ha leer a foldre akkor ugorhat ujra
            jumpsLeft =1;
            //csuszas
            if(!slidingTimer->isActive() && !slidingCD->isActive() && sliding)
            {
                //TODO: elkezd csuszni
                top->setLine(20, 101, 80, 101);
                right->setLine(99, 120, 99, 180);
                left->setLine(1, 120, 1, 180);

                //qDebug() << "started sliding";
                slidingTimer->start(1000);
            }

        }
    }
    if(!sliding && slidingTimer->remainingTime()<500 && slidingTimer->isActive())
    {
        slidingTimer->stop();
        stopSliding();
        //qDebug() << "sliding stopped, released slide button";
    }
    if(yVelocity!=0 && slidingTimer->isActive())
    {
        slidingTimer->stop();
        stopSliding();
        //qDebug() << "sliding stopped, left ground";
    }
    topCollidingItems = top->collidingItems();
    for (int i = 0, n = topCollidingItems.size(); i < n; ++i)
    {
        if (typeid(*(topCollidingItems.at(i))) == typeid(Terrain)) //ha erintkezik plafonnal, akkor stop
        {
            //ugras megallitasa
            yVelocity = (yVelocity > 0 ? 0 : yVelocity);
        }
    }

    //jobb oldalrol jonni fog a fal, igy ott jobban megkell csinalni a falnak utkozest
    //ha mas iranyba is mozognanak feluletek, akkor ott is megkene ilyenre csinalni
        //qDebug() << "rightWall";
    rightCollidingItems = right->collidingItems();
    for (int i = 0, n = rightCollidingItems.size(); i < n; ++i)
    {
        if (typeid(*(rightCollidingItems.at(i))) == typeid(Terrain)) //vane fal mellette
        {
            //() << rightCollidingItems[i]->scenePos().x() << " " << pos().x();
            if(rightCollidingItems[i]->scenePos().x()-100<pos().x())
            {
                setPos(rightCollidingItems[i]->scenePos().x()-100, y());
            }
        }
    }

    if(goingLeft)
    {
        leftCollidingItems = left->collidingItems();
        for (int i = 0, n = leftCollidingItems.size(); i < n; ++i)
        {
            if (typeid(*(leftCollidingItems.at(i))) == typeid(Terrain)) //vane fal mellette
            {
                if(leftCollidingItems[i]->scenePos().x()+leftCollidingItems[i]->boundingRect().width()>pos().x())
                {
                    setPos(leftCollidingItems[i]->scenePos().x()+leftCollidingItems[i]->boundingRect().width(), y());
                }
                //qDebug() << "wallLeft";
                //wallLeft=true;
            }
        }
    }
    //oldalra mozgas
    //ha levegoben van vagy csuszik, akkor lassabban mozog oldalra, mint ha futna a foldon
    if(goingRight && !wallRight)
    {
        setPos(x()+(yVelocity == 0 && !slidingTimer->isActive() ? 4 : 2.5), y());
        emit moved(yVelocity == 0 && !slidingTimer->isActive() ? 4 : 2.5);
        qDebug() << "goingright";
    }
    if(goingLeft && !wallLeft)
    {
        setPos(x()-(!slidingTimer->isActive()  ? 4 : 2.5), y());
        emit moved(!slidingTimer->isActive()  ? -4 : -2.5);
    }
    emit moved(3);
    //ha erintkezik a folddel, akkor a yvelocity 0, ha esik, akkor negativ, ha ugrik akkr pozitiv
    setPos(x(), y()-yVelocity);
}

void Character::stopSliding()
{
    //TODO: stop sliding
    top->setLine(20, 1, 80, 1);
    for (int i = 0, n = topCollidingItems.size(); i < n; ++i)
    {
        if (typeid(*(topCollidingItems.at(i))) == typeid(Terrain))
        {
            top->setLine(20, 101, 80, 101);
            slidingTimer->start(10);
            return;
        }
    }
    right->setLine(99, 20, 99, 180);
    left->setLine(1, 20, 1, 180);
    slidingCD->start(500);
}
