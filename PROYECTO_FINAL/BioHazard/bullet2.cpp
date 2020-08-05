#include "bullet2.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include "enemyship.h"
#include "game2.h"
#include "sinenemyship.h"
#include <math.h>

extern game2 * Game2;

bullet2::bullet2(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem()
{
    //draw the bullet
    setPixmap(QPixmap(":/2D/laser.png"));
    this->setScale(0.3);

    //connect
    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this, SLOT(move()));
    timer->start(10);

}

bullet2::~bullet2()
{
    delete timer;
}

void bullet2::move()
{
    //Se calcula la ditancia de la bala a cada uno de los enemigos que esten creados.
    // Si dicha distancia es menor que 50 pixeles se asume que hubo una colision.
    // Y se marca el enemigo y el objeto bullet.

    for (int i = 0;i<Game2->ship->EnemyClase1.size();i++) {
        float DistanciaBalaEnemigo=pow(pow(Game2->ship->EnemyClase1.at(i)->x()-this->x(),2)+pow(Game2->ship->EnemyClase1.at(i)->y()-this->y(),2),0.5);
        if(DistanciaBalaEnemigo<=50){
            Game2->ship->EnemyClase1.at(i)->SeDebeEliminar=true;
        }
    }
    for (int i = 0;i<Game2->ship->EnemyClase2.size();i++) {
        float DistanciaBalaEnemigo=pow(pow(Game2->ship->EnemyClase2.at(i)->x()-this->x(),2)+pow(Game2->ship->EnemyClase2.at(i)->y()-this->y(),2),0.5);
        if(DistanciaBalaEnemigo<=50){
            Game2->ship->EnemyClase2.at(i)->SeDebeEliminar=true;
        }
    }

    // Todos aquellos enemigos de la clase 1 que se hayan marcado se van a eliminar.
    for (int i = 0;i<Game2->ship->EnemyClase1.size();i++) {
        auto iterador=Game2->ship->EnemyClase1.begin();
        if(Game2->ship->EnemyClase1.at(i)->SeDebeEliminar==true){
            Game2->score->increase(50);
            iterador+=i;
            delete Game2->ship->EnemyClase1.at(i);
            Game2->ship->EnemyClase1.erase(iterador);
            SeElimina=true;
            i=0;
        }
    }
    // Todos aquellos enemigos de la clase 2 que se hayan marcado se van a eliminar.
    for (int i = 0;i<Game2->ship->EnemyClase2.size();i++) {
        auto iterador=Game2->ship->EnemyClase2.begin();
        if(Game2->ship->EnemyClase2.at(i)->SeDebeEliminar==true){
            Game2->score->increase(50);
            iterador+=i;
            delete Game2->ship->EnemyClase2.at(i);
            Game2->ship->EnemyClase2.erase(iterador);
            SeElimina=true;
            i=0;
        }
    }

    // Si la bala fue marcada se va a eliminar.
    if(SeElimina==true){
        delete this;
    }
    else {
    //move bullet right
    setPos(x()+20,y());
    // Si la bala sale del view se va a eliminar.
    if(x()>=600){
        scene()->removeItem(this);
        delete this;
    }
   }
}
