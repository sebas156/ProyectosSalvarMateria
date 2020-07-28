#include "enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>
#include <QList>
#include <stdlib.h>
#include <QGraphicsItem>

enemy::enemy()
{
//    //set random position
//    int random_number = rand()% 700;
//    posx=random_number;
//    posy=0;
    //draw the enemy
//    setRect(0,0,46,46);

    setPixmap(QPixmap(":/MOV/mutant.png").copy(0,0,46,46));
    setShapeMode(BoundingRectShape);
    timer_anim = new QTimer();
    this->setScale(0.9);

    connect(timer_anim,&QTimer::timeout,this,&enemy::animate);
    timer_anim->start(60);

    connect(Atacar, &QTimer::timeout,this,&enemy::HabilitarAtaque);
    Atacar->start(3000);

}

void enemy::reducir_salud()
{
    salud-=reduccion;
//    if(salud<=0)
    //        estado=0;
}

void enemy::ColisionRetroceder(float AX, float AY)
{
    float tempx=x();
    float tempy=y();
    while (velocidad.Magnitud()>2) {
        velocidad.x = velocidad.x + AX*dt;
        velocidad.y = velocidad.y + AY*dt;
        posx = posx + velocidad.x*dt + (AX*dt*dt)/2;
        posy = posy + velocidad.y*dt + (AY*dt*dt)/2;
        this->setPos(posx,posy);
        QList<QGraphicsItem *> colliding_items = collidingItems();
        for(int i=0, n = colliding_items.size(); i<n ; i++)
        {
            if(typeid (*(colliding_items[i])) == typeid(obstaculo))
            {
                velocidad.MultiplicarEscalar(0);
                setPos(tempx,tempy);
                setPos(x(),y());
                break;
            }
        }
    }
}

void enemy::animate()
{
    QPixmap image(":/MOV/mutant.png");
    anim_counter();
    QPixmap cropped = image.copy(46*(i-1),0,46,46);
    setPixmap(QPixmap(cropped));
}

void enemy::anim_counter()
{
    if(i>2)
        i=0;
    i++;
}

void enemy::HabilitarAtaque()
{
    SePuedeAtacar=true;
}
