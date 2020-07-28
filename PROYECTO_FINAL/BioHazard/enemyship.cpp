#include "enemyship.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>
#include <QList>
#include <stdlib.h>
#include "game2.h"
#include "bullet2.h"

extern game2 * Game2;

enemyship::enemyship(QGraphicsItem * parent): QObject(), QGraphicsPixmapItem()
{
    //set random posicion
    int random_number = rand() % 500;
    setPos(800,random_number);

    //draw the enemy
    setPixmap(QPixmap(":/2D/Ship.png"));

    //connect
    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this, SLOT(move()));

    timer->start(45);

    QTimer *anim = new QTimer();
    connect(anim,SIGNAL(timeout()),this,SLOT(animate()));
    anim->start(20);
}

void enemyship::move()
{
    //move enemy left
    setPos(x()-15,y());
    if(x()<=0){
        //decrease the score
        Game2->score->reduce(50);
        scene()->removeItem(this);
        delete this;
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

void enemyship::animate()
{
    QPixmap image(":/2D/Ship.png");
    anim_counter();
    QPixmap cropped = image.copy(173*(i),0,173,64);
    setPixmap(QPixmap(cropped));
}

void enemyship::anim_counter()
{
    if(i==3)
        i=0;
    else
        i++;
}
