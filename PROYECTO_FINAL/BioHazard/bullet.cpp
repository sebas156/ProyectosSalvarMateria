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
    int C=0,I;
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i=0, n = colliding_items.size(); i<n ; i++)
    {
        if(typeid (*(colliding_items[i])) == typeid(enemy))
        {
            //qDebug()<<colliding_items.size();
            C=1;
            I=i;
            //scene()->removeItem(colliding_items[i]);
            //colliding_items[i]->setPos(7000,7000);
            colliding_items[i]->setScale(0.95);
            break;
        }
        else if(typeid (*(colliding_items[i])) == typeid(obstaculo))
        {
            delete this;
            break;
        }
    }

// ******************************   E R R O R    A Q U I   **********************************//
//   Propuesta de solución: Recorrer toda la lista de Zombies y verificar, cada uno, si está o no en la escena.
//   Eso puede implicar verificar si el objeto es visible, o si pertenece a los items() de la escena. En caso de que
//   el objeto no sea visible o no esté en la escena, eliminarlo de la Qlist Zombies por su índice y a través de los
//   métodos que ofrece este contenedor para borrar elementos.

//    El código, hasta el momento, elimina las balas y remueve los enemigos de la escena de la forma correcta, y cuando
//    hay enemigos superpuestos (es decir, uno encima de otro), no se eliminan todos los enemigos superpuesto de un solo disparo,
//    sino que toda disparar tantas balas como enemigos haya (que es lo ideal). EL ÚNICO PROBLEMA ES ELIMINARLOS DE LA MEMORIA.
//    ES DECIR, LA ELIMINACIÓN DE LOS ENEMIGOS ES LA ESPERADA, PERO SIGUEN OCUPANDO MEMORIA.


    if(L==1)
        setPos(x()-10,y());
    if(R==1)
        setPos(x()+10,y());
    if(U==1)
        setPos(x(),y()-10);
    if(D==1)
        setPos(x(),y()+10);

    if(pos().y()<0-rect().height() || pos().y()>1200 || pos().x()<0 || pos().x()>2000 || C==1)
    {
        scene()->removeItem(this);
        QList<enemy*>::iterator it=Game->Zombies.begin();
        for(int x=0; x<Game->Zombies.size();x++)
        {
            if(Game->Zombies[x]->scale()<1)
            {
                float vf;
                if(this->velocidad.x==0){
                    vf=(velocidad.y*this->Masa + Game->Zombies[x]->Masa*Game->Zombies[x]->velocidad.y)/(this->Masa + Game->Zombies[x]->Masa);
                    Game->Zombies[x]->velocidad.y=vf;
                    Game->Zombies[x]->velocidad.x=0;
                }
                else {
                    vf=(velocidad.x*this->Masa + Game->Zombies[x]->Masa*Game->Zombies[x]->velocidad.x)/(this->Masa + Game->Zombies[x]->Masa);
                    Game->Zombies[x]->velocidad.x=vf;
                    Game->Zombies[x]->velocidad.y=0;
                }
                it+=x;
                Game->Zombies[x]->setScale(1);
                Game->Zombies[x]->reducir_salud();
                Game->Zombies[x]->ColisionRetroceder(Game->Zombies[x]->velocidad.x*(-1.5),Game->Zombies[x]->velocidad.y*(-1.5));
                if(Game->Zombies[x]->salud<=0)
                {
                    delete Game->Zombies[x];
                    Game->Zombies.erase(it);
                    break;
                }
            }
        }
        delete this;
    }
}
