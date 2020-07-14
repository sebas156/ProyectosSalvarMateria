#include "bullet.h"
#include "game.h"
#include "enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QPainter>

extern game *Game;

bullet::bullet(char dir)
{
    if(dir=='l')
        L=1;
    if(dir=='r')
        R=1;
    if(dir=='u')
        U=1;
    if(dir=='d')
        D=1;

    //draw the bullet
    setRect(0,0,5,5);

    //connect
    QTimer *timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    timer->start(5);
}

void bullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::white);
    painter->drawEllipse(boundingRect());
}

void bullet::move()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i=0, n = colliding_items.size(); i<n ; i++)
    {
        if(typeid (*(colliding_items[i])) == typeid(enemy))
        {
            //set score

            //remove both
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);
            //delete both
            delete colliding_items[i];
            delete this;
        }
    }

    if(L==1)
        setPos(x()-10,y());
    if(R==1)
        setPos(x()+10,y());
    if(U==1)
        setPos(x(),y()-10);
    if(D==1)
        setPos(x(),y()+10);

    if(pos().y()<0-rect().height() || pos().y()>1200 || pos().x()<0 || pos().x()>2000)
    {
        scene()->removeItem(this);
        delete this;
    }
}
