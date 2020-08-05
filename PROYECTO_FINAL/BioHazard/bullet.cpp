#include "bullet.h"
#include "game.h"
#include "enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QPainter>
#include <QDebug>

extern game *Game;

bullet::bullet(char dir)
{
    // Segun la direccion que lleva la bala.
    // Establece la magnitud del vector velocidad de la bala.
    // Para las colisiones.
    if(dir=='l'){
        L=1;
        this->velocidad.x=-1000;
        this->velocidad.y=0;
    }
    if(dir=='r'){
        this->velocidad.x=1000;
        this->velocidad.y=0;
        R=1;
    }
    if(dir=='u'){
       U=1;
       this->velocidad.x=0;
       this->velocidad.y=-1000;

    }
    if(dir=='d'){
        D=1;
        this->velocidad.x=0;
        this->velocidad.y=1000;
    }

    //draw the bullet
    setRect(0,0,5,5);

    //connect
    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(5);
}

bullet::~bullet()
{
    delete timer;
}

void bullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::white);
    painter->drawEllipse(boundingRect());
}

void bullet::move()
{
    int C=0,I;
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i=0, n = colliding_items.size(); i<n ; i++)
    {
        // Si hubo una colision con un enemigo a ese enemigo se le reducirá la escala.
        // Para marcarlo como que le han disparado.
        // Además hay una bandera que indica que hubo una colisión.S
        if(typeid (*(colliding_items[i])) == typeid(enemy))
        {
            C=1; // Bnadera que indica que hubo una colision.
            I=i;
            colliding_items[i]->setScale(0.95);
            break;
        }
        // Si la bala choca con un obstaculo, la bala se eliminará.S
        else if(typeid (*(colliding_items[i])) == typeid(obstaculo))
        {
            delete this;
            break;
        }

        if(typeid (*(colliding_items[i])) == typeid(player1))
                {
                    //Si la bala choca con el player 1, es porque el player 2 le disparó.
                    // Lo cual significa que al player 1 se le debe curar.
                    delete this;
                    Game->player->RestarVida(-25);
                    if(Game->player->get_vida()>100)
                        Game->player->set_vida(100);
                    break;
                }
    }

    // Movimiento.
    if(L==1)
        setPos(x()-10,y());
    if(R==1)
        setPos(x()+10,y());
    if(U==1)
        setPos(x(),y()-10);
    if(D==1)
        setPos(x(),y()+10);

    //Aqui se verifica si la bala salió de la escena o si por el contrario colisionó con algo.
    if(pos().y()<0-rect().height() || pos().y()>1200 || pos().x()<0 || pos().x()>2000 || C==1)
    {
        scene()->removeItem(this);
        QList<enemy*>::iterator it=Game->Zombies.begin();
        for(int x=0; x<Game->Zombies.size();x++)
        {
            // Se verifica cada uno de los zombies si su escala se ha reducido. Si es así, quiere decir que a ese zombie le dispararon.
            if(Game->Zombies[x]->scale()<1)
            {
                // Considerando que la bala nunca se mueve en diagonal. Solo hay dosposibilidades. que la componente en x
                // de la velocidad de la bala sea 0 o que lo sea la de y.
                float vf;
                if(this->velocidad.x==0){
                    // Ecuacion de la colision entre dos objetos para el eje y.
                    vf=(velocidad.y*this->Masa + Game->Zombies[x]->Masa*Game->Zombies[x]->velocidad.y)/(this->Masa + Game->Zombies[x]->Masa);
                    Game->Zombies[x]->velocidad.y=vf;
                    Game->Zombies[x]->velocidad.x=0;
                }
                else {
                    // Ecuacion de la colision entre dos objetos para el eje x.
                    vf=(velocidad.x*this->Masa + Game->Zombies[x]->Masa*Game->Zombies[x]->velocidad.x)/(this->Masa + Game->Zombies[x]->Masa);
                    Game->Zombies[x]->velocidad.x=vf;
                    Game->Zombies[x]->velocidad.y=0;
                }
                it+=x;
                Game->Zombies[x]->setScale(1); // Restablezco la escala del zombie.
                Game->Zombies[x]->reducir_salud(); // Reduzco la salud del zombie.
                // Se explica dentro de la funcion.
                Game->Zombies[x]->ColisionRetroceder(Game->Zombies[x]->velocidad.x*(-1.5),Game->Zombies[x]->velocidad.y*(-1.5));
                if(Game->Zombies[x]->salud<=0)
                {
                    // Se verifica si la salud del zombie es menor que 0. En ese caso se elimina el zombie.
                    // Y si estamos en modo 2. Se aumenta el puntaje.
                    if(Game->getmodo()==2){
                        *(Game->puntosTotales)+=10;
                        Game->score->increase(10);
                    }
                    delete Game->Zombies[x];
                    Game->Zombies.erase(it);
                    break;
                }
            }
        }
        delete this;
    }
}
