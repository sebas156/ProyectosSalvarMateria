#include "enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>
#include <QList>
#include <stdlib.h>
#include <QGraphicsItem>

enemy::enemy()
{
    //set random position
    int random_number = rand()% 700;
    setPos(random_number,0);

    //draw the enemy
    setRect(0,0,100,100);

    //connect
    QTimer *timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    timer->start(50);
}

void enemy::move()
{
    //move enemy (up)
    setPos(x(),y()+5);
    if(pos().y()<0-rect().height())
    {
        scene()->removeItem(this);
        delete this;
    }
}
