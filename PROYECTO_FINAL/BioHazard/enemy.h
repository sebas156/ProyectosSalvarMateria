#ifndef ENEMY_H
#define ENEMY_H
#include <QGraphicsRectItem>
#include <QObject>
#include <QBrush>
#include <QPen>
#include "vec3.h"

class enemy: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    enemy();
    float posx;
    float posy;
    vec3 velocidad;
    void reducir_salud();
    int reduccion=30;
    //int estado=1;   // 1 = is alive ;  0 = is dead;
    int salud=100;
private:


};

#endif // ENEMY_H
