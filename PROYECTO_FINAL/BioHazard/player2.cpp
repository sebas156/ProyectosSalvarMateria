#include "player2.h"
#include <QKeyEvent>
#include "bullet.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QTimer>
#include <QTransform>
#include <QPainter>
#include "game.h"
#include "healer.h"

extern game * Game;

player2::player2():QGraphicsPixmapItem()
{
    setPixmap(QPixmap(":/MOV/D2.png").copy(0,0,70,100));
    this->setScale(0.95);
    setShapeMode(BoundingRectShape);
    timer_anim = new QTimer();

    connect(timer_anim,&QTimer::timeout,this,&player2::animate);
    timer_anim->start(60);

    QTimer *movtimer = new QTimer();
    connect(movtimer,SIGNAL(timeout()),this,SLOT(move()));
    movtimer->start(5);

    QTimer *acelerate = new QTimer();
    connect(acelerate,SIGNAL(timeout()),this,SLOT(change_speed()));
    acelerate->start(30);
}

void player2::RestarVida(int recibido)
{

    Vida-=recibido;
    if(Vida<=0)
        emit buttonClicked();
}

float player2::get_vida()
{
    return Vida;
}

void player2::PonerTodoEnCero()
{
    L=0;
    R=0;
    U=0;
    D=0;
}

void player2::move()
{
    float tempx=x();
    float tempy=y();
    if(x()+Vx>0 && x()+Vx<1900 && y()+Vy>100 && y()+Vy<1100)
    setPos(x()+Vx,y()+Vy);
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i=0, n = colliding_items.size(); i<n ; i++)
    {
        if(typeid (*(colliding_items[i])) == typeid(obstaculo))
        {
            Vx=0;
            Vy=0;
            setPos(tempx,tempy);
            //setPos(x(),y());
            break;
        }

        if(typeid(*(colliding_items[i])) == typeid(healer))
        {
            Game->Healer->setPos(-20,-20);
            Vida+=50;
            if(Vida>100)
                Vida=100;
        }

        if(typeid(*(colliding_items[i])) == typeid(ammo))
        {
            Game->Ammo->setPos(-20,-20);
            shots=0;
        }
    }
}

void player2::change_speed()
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

void player2::animate()
{
    if(aim=='L')
    {
        QPixmap image(":/MOV/L2.png");
        anim_counter();
        QPixmap cropped = image.copy(75*(i-1),0,75,100);
        setPixmap(QPixmap(cropped));
    }

    if(aim=='R')
    {
        QPixmap image(":/MOV/R2.png");
        anim_counter();
        QPixmap cropped = image.copy(77*(i-1),0,77,100);
        setPixmap(QPixmap(cropped));
    }

    if(aim=='U')
    {
        QPixmap image(":/MOV/U2.png");
        anim_counter();
        QPixmap cropped = image.copy(63*(i-1),0,63,100);
        setPixmap(QPixmap(cropped));
    }

    if(aim=='D')
    {
        QPixmap image(":/MOV/D2.png");
        anim_counter();
        QPixmap cropped = image.copy(60*(i-1),0,60,100);
        setPixmap(QPixmap(cropped));
    }

    ////

    if(L==1)
    {
        QPixmap image(":/MOV/L2.png");
        anim_counter();
        QPixmap cropped = image.copy(75*(i-1),0,70,100);
        setPixmap(QPixmap(cropped));
    }

    if(R==1)
    {
        QPixmap image(":/MOV/R2.png");
        anim_counter();
        QPixmap cropped = image.copy(77*(i-1),0,70,100);
        setPixmap(QPixmap(cropped));
    }

    if(U==1)
    {
        QPixmap image(":/MOV/U2.png");
        anim_counter();
        QPixmap cropped = image.copy(63*(i-1),0,70,100);
        setPixmap(QPixmap(cropped));
    }

    if(D==1)
    {
        QPixmap image(":/MOV/D2.png");
        anim_counter();
        QPixmap cropped = image.copy(60*(i-1),0,70,100);
        setPixmap(QPixmap(cropped));
    }

    if(L==1 && U==1)
    {
        QPixmap image(":/MOV/UL2.png");
        anim_counter();
        QPixmap cropped = image.copy(70*(i-1),0,70,100);
        setPixmap(QPixmap(cropped));
    }

    if(L==1 && D==1)
    {
        QPixmap image(":/MOV/DL2.png");
        anim_counter();
        QPixmap cropped = image.copy(66*(i-1),0,70,100);
        setPixmap(QPixmap(cropped));
    }

    if(R==1 && U==1)
    {
        QPixmap image(":/MOV/UR2.png");
        anim_counter();
        QPixmap cropped = image.copy(70*(i-1),0,70,100);
        setPixmap(QPixmap(cropped));
    }

    if(R==1 && D==1)
    {
        QPixmap image(":/MOV/DR2.png");
        anim_counter();
        QPixmap cropped = image.copy(70*(i-1),0,70,100);
        setPixmap(QPixmap(cropped));
    }

}

void player2::anim_counter()
{
    if(i>3)
        i=0;
    i++;
}
