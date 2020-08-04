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
    this->setScale(0.95);
    setShapeMode(BoundingRectShape);
    timer_anim = new QTimer();

    connect(timer_anim,&QTimer::timeout,this,&player1::animate);
    timer_anim->start(60);

    movtimer = new QTimer();
    connect(movtimer,SIGNAL(timeout()),this,SLOT(move()));
    movtimer->start(5);

    acelerate = new QTimer();
    connect(acelerate,SIGNAL(timeout()),this,SLOT(change_speed()));
    acelerate->start(30);
}

player1::~player1()
{
    delete movtimer;
    delete acelerate;
    delete timer_anim;
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
    if(shots<=50){
        if(event->key() == Qt::Key_F)
        {
            if(!event->isAutoRepeat())
            {
                bullet *Bullet = new bullet('l');
                Bullet->setPos(x()-26,y()+25);
                scene()->addItem(Bullet);
                shots++;
            }
        }

        if(event->key() == Qt::Key_H)
        {
            if(!event->isAutoRepeat())
            {
                bullet *Bullet = new bullet('r');
                Bullet->setPos(x()+80,y()+25);
                scene()->addItem(Bullet);
                shots++;
            }
        }

        if(event->key() == Qt::Key_T)
        {
            if(!event->isAutoRepeat())
            {
                bullet *Bullet = new bullet('u');
                Bullet->setPos(x()+30,y()-15);
                scene()->addItem(Bullet);
                shots++;
            }
        }

        if(event->key() == Qt::Key_G)
        {
            if(!event->isAutoRepeat())
            {
                bullet *Bullet = new bullet('d');
                Bullet->setPos(x()+15,y()+105);
                scene()->addItem(Bullet);
                shots++;
            }
        }
    }
    if(event->key() == Qt::Key_P)
    {
        TecladoBloqueado=true;
        emit buttonClicked2();

    }

    // FOR PLAYER 2 //////////////////////////////////////////////////////////
    if(Game->getmodo()==2){
        if(event->key() == Qt::Key_Left)
        {
            if(!event->isAutoRepeat())
                Game->player_2->L=1;
            Game->player_2->aim='l';
        }
        if(event->key() == Qt::Key_Right)
        {
            if(!event->isAutoRepeat())
                Game->player_2->R=1;
            Game->player_2->aim='r';
        }
        if(event->key() == Qt::Key_Up)
        {
            if(!event->isAutoRepeat())
                Game->player_2->U=1;
            Game->player_2->aim='u';
        }
        if(event->key() == Qt::Key_Down)
        {
            if(!event->isAutoRepeat())
                Game->player_2->D=1;
            Game->player_2->aim='d';
        }
        if(Game->player_2->shots<3){
            if(event->key() == Qt::Key_Space)
            {
                if(!event->isAutoRepeat())
                {

                    bullet *Bullet = new bullet(Game->player_2->aim);
                    Bullet->setPos(Game->player_2->x()+30,Game->player_2->y()+30);
                    scene()->addItem(Bullet);
                    Game->player_2->shots++;
                }
            }
        }
   }


}

void player1::keyReleaseEvent(QKeyEvent *event)
{
    if(TecladoBloqueado==true){
        return;
    }
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

    // FOR PLAYER 2 //////////////////////////////////////////////////
    if(Game->getmodo()==2)
    {
        if(event->key() == Qt::Key_Left)
        {
            if(!event->isAutoRepeat())
                Game->player_2->L=0;
        }
        if(event->key() == Qt::Key_Right)
        {
            if(!event->isAutoRepeat())
                Game->player_2->R=0;
        }
        if(event->key() == Qt::Key_Up)
        {
            if(!event->isAutoRepeat())
                Game->player_2->U=0;
        }
        if(event->key() == Qt::Key_Down)
        {
            if(!event->isAutoRepeat())
                Game->player_2->D=0;
        }
    }
}

void player1::RestarVida(int recibido)
{

    Vida-=recibido;
    Game->hbar->setWidth(Vida);
    if(Vida<=0)
        emit buttonClicked();
}

void player1::PonerTodoEnCero()
{
     L=0;
     R=0;
     U=0;
     D=0;
}

void player1::spawn()
{
    //create enemies
    enemy * Enemy = new enemy();
    scene()->addItem(Enemy);
}

float player1::get_vida()
{
    return Vida;
}

void player1::set_vida(int val)
{
    Vida=val;
}

void player1::move()
{
    float tempx=x();
    float tempy=y();
    //qDebug()<<tempx;
    if((x()+Vx>0 && x()+Vx<1900 && y()+Vy>100 && y()+Vy<1100) and TecladoBloqueado==false){
        setPos(x()+Vx,y()+Vy);
        //qDebug()<<x();
    }
    else {
        Vx=0;
        Vy=0;
    }
    Game->view->centerOn(x(),y());
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i=0, n = colliding_items.size(); i<n ; i++)
    {
        if(typeid (*(colliding_items[i])) == typeid(obstaculo))
        {
            Vx=0;
            Vy=0;
            setPos(tempx,tempy);
//            setPos(x(),y());
            break;
        }

        if(Game->getmodo()==1){
            if(typeid(*(colliding_items[i])) == typeid(healer))
            {
                Game->Healer->setPos(-20,-20);
                Vida+=50;
                if(Vida>100)
                    Vida=100;
            }
        }

        if(typeid(*(colliding_items[i])) == typeid(ammo))
        {
            Game->Ammo->setPos(-20,-20);
            shots=0;
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
        QPixmap cropped = image.copy(75*(i-1),0,70,100);
        setPixmap(QPixmap(cropped));
    }

    if(R==1)
    {
        QPixmap image(":/MOV/R.png");
        anim_counter();
        QPixmap cropped = image.copy(77*(i-1),0,70,100);
        setPixmap(QPixmap(cropped));
    }

    if(U==1)
    {
        QPixmap image(":/MOV/U.png");
        anim_counter();
        QPixmap cropped = image.copy(63*(i-1),0,70,100);
        setPixmap(QPixmap(cropped));
    }

    if(D==1)
    {
        QPixmap image(":/MOV/D.png");
        anim_counter();
        QPixmap cropped = image.copy(60*(i-1),0,70,100);
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
        QPixmap cropped = image.copy(66*(i-1),0,70,100);
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
