#include "enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>
#include <QList>
#include <stdlib.h>
#include <QGraphicsItem>

enemy::enemy()
{

    setPixmap(QPixmap(":/MOV/mutant.png").copy(0,0,46,46));
    setShapeMode(BoundingRectShape);
    timer_anim = new QTimer();
    this->setScale(0.9);

    connect(timer_anim,&QTimer::timeout,this,&enemy::animate);
    timer_anim->start(60);

    // Establece el tiempo entre cada ataque que hace un enemigo al jugador princial.
    connect(Atacar, &QTimer::timeout,this,&enemy::HabilitarAtaque);
    Atacar->start(3000);

}

enemy::~enemy()
{
    delete Atacar;
    delete timer_anim;
}

void enemy::reducir_salud()
{
    salud-=reduccion;
}

void enemy::ColisionRetroceder(float AX, float AY)
{
    /* Esta funcion recibe la aceleracion que tendrá el zombie en el momento de la colision con la bala.
     * Esta aceleracion debe estar en direccion opuesta a la velocidad resultante de la colision.
     */
    // Posicion que llevaba el enemigo antes de ser impactado por la bala.
    float tempx=x();
    float tempy=y();

    //La aceleración irá reduciendo esa velocidad resultante (cosntante.)

    while (velocidad.Magnitud()>2) { // Bucle que se repite mientras que la velocidad del enemigo al cual le han disparado sea mayor que 2
        if(posx>0 && posx<1900 && posy>100 && posy<1100){  // Verifica si el zombie se encuentra dentro de la escena.
            velocidad.x = velocidad.x + AX*dt;
            velocidad.y = velocidad.y + AY*dt;
            posx = posx + velocidad.x*dt + (AX*dt*dt)/2;
            posy = posy + velocidad.y*dt + (AY*dt*dt)/2;
            this->setPos(posx,posy);
        }else {
            // Si no se encuentra dentro de la escene se queda justo donde está... A pesar que le disparen.
            velocidad.x=0;
            velocidad.y=0;
            setPos(tempx,tempy);
        }
        QList<QGraphicsItem *> colliding_items = collidingItems(); // Estas lineas de codigo verifican si debido al retroceso del enemigo por el disparo.
        for(int i=0, n = colliding_items.size(); i<n ; i++)       // el enemigo choca contra un muro. Y detienen ese retroceso.
        {
            if(typeid (*(colliding_items[i])) == typeid(obstaculo))
            {
                velocidad.MultiplicarEscalar(0);
                setPos(tempx,tempy);
                setPos(x(),y());
                break;
            }
        }
    }
}

void enemy::animate()
{
    QPixmap image(":/MOV/mutant.png");
    anim_counter();
    QPixmap cropped = image.copy(46*(i-1),0,46,46);
    setPixmap(QPixmap(cropped));
}

void enemy::anim_counter()
{
    if(i>2)
        i=0;
    i++;
}

void enemy::HabilitarAtaque()
{
    SePuedeAtacar=true;
}
