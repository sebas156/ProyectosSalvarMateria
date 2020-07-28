#include "bullet2.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include "enemyship.h"
#include "game2.h"
#include "sinenemyship.h"

extern game2 * Game2;

bullet2::bullet2(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem()
{
    //draw the bullet
    setPixmap(QPixmap(":/2D/laser.png"));
    this->setScale(0.3);

    //connect
    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this, SLOT(move()));
    timer->start(10);

}

void bullet2::move()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i = 0, n = colliding_items.size(); i < n; i++){
        if(typeid(*(colliding_items[i])) == typeid (enemyship) ){

            //Increase score
            Game2->score->increase(50);

            //remove the both
            if(typeid(*(colliding_items[i]))!=typeid(sinenemyship)){
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);
            //delete both
            delete colliding_items[i];
            delete this;
            }
        }

        if(typeid(*(colliding_items[i])) == typeid (sinenemyship)){

            //Increase score
            Game2->score->increase(50);
            if(typeid(*(colliding_items[i]))!=typeid(enemyship)){
            //remove the both
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);
            //delete both
            delete colliding_items[i];
            delete this;
            }
        }
    }



    //move bullet right
    setPos(x()+20,y());
    if(x()>=600){
        scene()->removeItem(this);
        delete this;
    }
}
