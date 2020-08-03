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
    int VelocidadMaxima;      // La velocidad maxima a la que un enemigo puede correr.
    float posx;               // Posicion en x del enemigo.
    float posy;               // Posicion en Y del enemigo.
    float dt=0.01;
    vec3 velocidad;           // Vector que establece la dirreccion en la que se mueve el enemigo.
    void reducir_salud();     // Reduce la salud del enemigo.
    void ColisionRetroceder(float, float);   // Ejecuta la colision.
    int reduccion;    // La cantidad de puntos de vida que le reduce un impacto de bala.
    int salud=100;
    int Masa;
    int Dano;         // Daño que le hace el enemigo al heroe.
    bool SePuedeAtacar=true; // Establece si el zombie puede atacar.
    QTimer *Atacar = new QTimer;  // Este timer establece cada cuanto el enemigo ahce daño.
    QTimer *timer_anim = new QTimer;   // Para la animacion.
public slots:
    void animate();
    void anim_counter();
private slots:
    void HabilitarAtaque();
private:
    int i=0;  //index for animation

};

#endif // ENEMY_H
