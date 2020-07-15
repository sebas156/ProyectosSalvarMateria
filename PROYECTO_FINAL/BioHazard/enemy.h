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
};

#endif // ENEMY_H
