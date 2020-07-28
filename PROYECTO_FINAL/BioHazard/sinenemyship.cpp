#include "sinenemyship.h"
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

sinenemyship::sinenemyship(QGraphicsItem * parent): QObject(), QGraphicsPixmapItem()
{
    //set random posicion
    int random_number = rand() % 500;
    setPos(800,random_number);

    //draw the enemy
    setPixmap(QPixmap(":/2D/Ship2.png"));

    //connect
    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this, SLOT(move()));

    timer->start(10);

    QTimer *anim = new QTimer();
    connect(anim,SIGNAL(timeout()),this,SLOT(animate()));
    anim->start(20);

}

void sinenemyship::move()
{
    if(x()<=0){
        //decrease the score
        Game2->score->reduce(50);
        scene()->removeItem(this);
        delete this;
    }

    if(mode==1){
        //move enemy in a sinewave path
        setPos(x()-5,y()+30*sin((pi*(x()-10))/180));
    }

    if(mode==2){
        //move enemy in a sinewave path (damped)
        setPos(x()-5,(y()+(0.002*((pi*(x()-10))/180)*((pi*(x()-10))/180)*30*sin((pi*(x()-10))/180)))  );
    }

    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i = 0, n = colliding_items.size(); i < n; i++){
        if(typeid(*(colliding_items[i])) == typeid (spaceship)){
            collidingItems().clear();
            scene()->removeItem(this);
            delete this;
            Game2->health->decrease(5);
            Game2->score->reduce(50);
        }
    }

}

void sinenemyship::animate()
{
    QPixmap image(":/2D/Ship2.png");
    anim_counter();
    QPixmap cropped = image.copy(87*(i),0,87,28);
    setPixmap(QPixmap(cropped));
}

void sinenemyship::anim_counter()
{
    if(i==3)
        i=0;
    else
        i++;
}

