#ifndef ENEMY_H
#define ENEMY_H
#include <QGraphicsRectItem>
#include <QObject>
#include <QBrush>
#include <QPen>
#include <QTimer>
#include "vec3.h"
#include "obstaculo.h"

class enemy: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    enemy();
    float posx;
    float posy;
    float dt=0.01;
    vec3 velocidad;
    void reducir_salud();
    void ColisionRetroceder(float, float);
    int reduccion=30;
    int salud=100;
    int Masa=70;
    bool SePuedeAtacar=true;
    int Dano=2;
    QTimer *Atacar = new QTimer;
private slots:
    void HabilitarAtaque();

};

#endif // ENEMY_H
