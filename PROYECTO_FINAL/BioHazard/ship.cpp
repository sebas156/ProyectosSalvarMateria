#include "ship.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>
#include <QList>
#include <stdlib.h>
#include "game2.h"
#include "bullet2.h"
#include "math.h"

extern game2 * Game2;

#define pi 3.1416
#define e 2.7182

//constructor de la clase ship. recibe como parámetro qué tipo de nave spawnear. tipo 0 (rectilinea), tipo 1 (harmónico simple) y tipo 2 (armónico simple amortiguado)
//herada.

ship::ship(int type, QGraphicsItem * parent): QObject(), QGraphicsPixmapItem()
{
    TYPE=type;
    //set random posicion
    int random_number = rand() % 500;
    setPos(800,random_number);

    //draw the enemy
    if(TYPE==0)
        setPixmap(QPixmap(":/2D/Ship.png"));
    if(TYPE==1 || TYPE==2)
        setPixmap(QPixmap(":/2D/Ship2.png"));

    //connect
    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this, SLOT(move()));
    if(TYPE==0)
        timer->start(45);
    if(TYPE==1||TYPE==2)
        timer->start(10);

    QTimer *anim = new QTimer();
    connect(anim,SIGNAL(timeout()),this,SLOT(animate()));
    anim->start(20);

}

void ship::move()
{
    if(x()<=0){
        //decrease the score
        Game2->score->reduce(50);
        scene()->removeItem(this);
        delete this;
    }
    if(TYPE==0)
    {
        //move enemy in rectilinear path
        setPos(x()-15,y());
    }

    if(TYPE==1){
        //move enemy in a sinewave path
        setPos(x()-5,y()+30*sin((pi*(x()-10))/180));
    }

    if(TYPE==2){
        //move enemy in a sinewave path (damped)
        setPos(x()-5,(y()+(0.002*((pi*(x()-10))/180)*((pi*(x()-10))/180)*30*sin((pi*(x()-10))/180)))  );
    }

    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i = 0, n = colliding_items.size(); i < n; i++){
        if(typeid(*(colliding_items[i])) == typeid (spaceship)){
            collidingItems().clear();
            scene()->removeItem(this);
            delete this;
            Game2->ship->reduce_health();
            Game2->score->reduce(50);
        }
    }
}

void ship::animate()
{
    if(TYPE==0){
        QPixmap image(":/2D/Ship.png");
        anim_counter();
        QPixmap cropped = image.copy(173*(i),0,173,64);
        setPixmap(QPixmap(cropped));
    }
    if(TYPE==1 || TYPE==2)
    {
        QPixmap image(":/2D/Ship2.png");
        anim_counter();
        QPixmap cropped = image.copy(87*(i),0,87,28);
        setPixmap(QPixmap(cropped));
    }
}

void ship::anim_counter()
{
    if(i==3)
        i=0;
    else
        i++;
}

