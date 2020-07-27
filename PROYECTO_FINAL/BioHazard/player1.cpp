#include "player1.h"
#include "enemy.h"
#include <QKeyEvent>
#include "bullet.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QTimer>
#include <QTransform>
#include <QPainter>
#include "game.h"

extern game * Game;

player1::player1():QGraphicsPixmapItem()
{
    //setPixmap(QPixmap(":/MOV/D.png"));
    //QPixmap sprite(":/MOV/D.png");
    //QPixmap cropped = sprite.copy(0,0,70,100);
    //setPixmap(QPixmap(cropped));

    setPixmap(QPixmap(":/MOV/D.png").copy(0,0,70,100));
    setShapeMode(BoundingRectShape);
    timer_anim = new QTimer();

    connect(timer_anim,&QTimer::timeout,this,&player1::animate);
    timer_anim->start(60);

    QTimer *movtimer = new QTimer();
    connect(movtimer,SIGNAL(timeout()),this,SLOT(move()));
    movtimer->start(5);

    QTimer *acelerate = new QTimer();
    connect(acelerate,SIGNAL(timeout()),this,SLOT(change_speed()));
    acelerate->start(30);
}

void player1::keyPressEvent(QKeyEvent *event)
{

    if(event->key() == Qt::Key_A)
    {
        if(!event->isAutoRepeat())
            L=1;
    }
    if(event->key() == Qt::Key_D)
    {
        if(!event->isAutoRepeat())
            R=1;
    }
    if(event->key() == Qt::Key_W)
    {
        if(!event->isAutoRepeat())
            U=1;
    }
    if(event->key() == Qt::Key_S)
    {
        if(!event->isAutoRepeat())
            D=1;
    }

    if(event->key() == Qt::Key_Left)
    {
        bullet *Bullet = new bullet('l');
        Bullet->setPos(x()-10,y()+25);
        scene()->addItem(Bullet);
    }

    if(event->key() == Qt::Key_Right)
    {
        bullet *Bullet = new bullet('r');
        Bullet->setPos(x()+75,y()+25);
        scene()->addItem(Bullet);
    }

    if(event->key() == Qt::Key_Up)
    {
        bullet *Bullet = new bullet('u');
        Bullet->setPos(x()+30,y()-10);
        scene()->addItem(Bullet);
    }

    if(event->key() == Qt::Key_Down)
    {
        bullet *Bullet = new bullet('d');
        Bullet->setPos(x()+15,y()+75);
        scene()->addItem(Bullet);
    }

}

void player1::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_A)
    {
        if(!event->isAutoRepeat())
            L=0;
    }
    if(event->key() == Qt::Key_D)
    {
        if(!event->isAutoRepeat())
            R=0;
    }
    if(event->key() == Qt::Key_W)
    {
        if(!event->isAutoRepeat())
            U=0;
    }
    if(event->key() == Qt::Key_S)
    {
        if(!event->isAutoRepeat())
            D=0;
    }
    emit buttonPressed();
}

void player1::RestarVida(int recibido)
{

    Vida-=recibido;
    if(Vida<=0)
        emit buttonClicked();
}

void player1::spawn()
{
    //create enemies
    enemy * Enemy = new enemy();
    scene()->addItem(Enemy);
}

void player1::move()
{
    float tempx=x();
    float tempy=y();
    if(x()+Vx>0 && x()+Vx<1900 && y()+Vy>100 && y()+Vy<1100)
    setPos(x()+Vx,y()+Vy);
    Game->view->centerOn(x(),y());
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i=0, n = colliding_items.size(); i<n ; i++)
    {
        if(typeid (*(colliding_items[i])) == typeid(obstaculo))
        {
            Vx=0;
            Vy=0;
            setPos(tempx,tempy);
            setPos(x(),y());
            break;
        }
    }
}

void player1::change_speed()
{
    if(L==1 && Vx >= -Vf)
        Vx-=a;
    if(R==1 && Vx <= Vf)
        Vx+=a;
    if(U==1 && Vy >= -Vf)
        Vy-=a;
    if(D==1 && Vy <= Vf)
        Vy+=a;

    if(L==0 && Vx < 0)
        Vx+=a;
    if(R==0 && Vx > 0)
        Vx-=a;
    if(U==0 && Vy < 0)
        Vy+=a;
    if(D==0 && Vy > 0)
        Vy-=a;

    if(Vx<a && Vx >-a)
        Vx=0;
    if(Vy<a && Vy >-a)
        Vy=0;

}

void player1::animate()
{
    if(aim=='L')
    {
        QPixmap image(":/MOV/L.png");
        anim_counter();
        QPixmap cropped = image.copy(75*(i-1),0,75,100);
        setPixmap(QPixmap(cropped));
    }

    if(aim=='R')
    {
        QPixmap image(":/MOV/R.png");
        anim_counter();
        QPixmap cropped = image.copy(77*(i-1),0,77,100);
        setPixmap(QPixmap(cropped));
    }

    if(aim=='U')
    {
        QPixmap image(":/MOV/U.png");
        anim_counter();
        QPixmap cropped = image.copy(63*(i-1),0,63,100);
        setPixmap(QPixmap(cropped));
    }

    if(aim=='D')
    {
        QPixmap image(":/MOV/D.png");
        anim_counter();
        QPixmap cropped = image.copy(60*(i-1),0,60,100);
        setPixmap(QPixmap(cropped));
    }

    ////

    if(L==1)
    {
        QPixmap image(":/MOV/L.png");
        anim_counter();
        QPixmap cropped = image.copy(75*(i-1),0,75,100);
        setPixmap(QPixmap(cropped));
    }

    if(R==1)
    {
        QPixmap image(":/MOV/R.png");
        anim_counter();
        QPixmap cropped = image.copy(77*(i-1),0,77,100);
        setPixmap(QPixmap(cropped));
    }

    if(U==1)
    {
        QPixmap image(":/MOV/U.png");
        anim_counter();
        QPixmap cropped = image.copy(63*(i-1),0,63,100);
        setPixmap(QPixmap(cropped));
    }

    if(D==1)
    {
        QPixmap image(":/MOV/D.png");
        anim_counter();
        QPixmap cropped = image.copy(60*(i-1),0,60,100);
        setPixmap(QPixmap(cropped));
    }

    if(L==1 && U==1)
    {
        QPixmap image(":/MOV/UL.png");
        anim_counter();
        QPixmap cropped = image.copy(70*(i-1),0,70,100);
        setPixmap(QPixmap(cropped));
    }

    if(L==1 && D==1)
    {
        QPixmap image(":/MOV/DL.png");
        anim_counter();
        QPixmap cropped = image.copy(66*(i-1),0,66,100);
        setPixmap(QPixmap(cropped));
    }

    if(R==1 && U==1)
    {
        QPixmap image(":/MOV/UR.png");
        anim_counter();
        QPixmap cropped = image.copy(70*(i-1),0,70,100);
        setPixmap(QPixmap(cropped));
    }

    if(R==1 && D==1)
    {
        QPixmap image(":/MOV/DR.png");
        anim_counter();
        QPixmap cropped = image.copy(70*(i-1),0,70,100);
        setPixmap(QPixmap(cropped));
    }

}

void player1::anim_counter()
{
    if(i>3)
        i=0;
    i++;
}
