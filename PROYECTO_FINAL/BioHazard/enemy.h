#ifndef ENEMY_H
#define ENEMY_H
#include <QGraphicsRectItem>
#include <QObject>
#include <QBrush>
#include <QPen>
#include <QTimer>
#include "vec3.h"
#include "obstaculo.h"

class enemy: public QObject/*, public QGraphicsRectItem*/, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    enemy();
    ~enemy();
    int VelocidadMaxima;
    float posx;
    float posy;
    float dt=0.01;
    vec3 velocidad;
    void reducir_salud();
    void ColisionRetroceder(float, float);
    int reduccion;    // La cantidad de puntos de vida que le reduce un impacto de bala.
    int salud=100;
    int Masa;
    int Dano;
    bool SePuedeAtacar=true;
    QTimer *Atacar = new QTimer;
    QTimer *timer_anim = new QTimer;
public slots:
    void animate();
    void anim_counter();
private slots:
    void HabilitarAtaque();
private:
    int i=0;  //index for animation

};

#endif // ENEMY_H
