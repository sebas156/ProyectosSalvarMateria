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
    setRect(0,0,46,46);

}

void enemy::reducir_salud()
{
    salud-=reduccion;
//    if(salud<=0)
//        estado=0;
}
