#include "enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>
#include <QList>
#include <stdlib.h>
#include <QGraphicsItem>

enemy::enemy()
{
    QPen BlackPen(Qt::black);
    QBrush RedBrush(Qt::yellow);
    //set random position
    int random_number = rand()% 700;
    posx=random_number;
    posy=0;
    //draw the enemy
    setRect(0,0,50,50);

}
