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
    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this, SLOT(move()));
    timer->start(10);

}

void bullet2::move()
{

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


//    QList<QGraphicsItem *> colliding_items = collidingItems();
//    for(int i = 0, n = colliding_items.size(); i < n; i++){
//        if(typeid(*(colliding_items[i])) == typeid (enemyship) ){

//            //Increase score
//            Game2->score->increase(50);

//            //remove the both
//            if(typeid(*(colliding_items[i]))!=typeid(sinenemyship)){
//            scene()->removeItem(colliding_items[i]);
//            scene()->removeItem(this);
//            //delete both
//            delete colliding_items[i];
//            delete this;
//            }
//        }

//        if(typeid(*(colliding_items[i])) == typeid (sinenemyship)){

//            //Increase score
//            Game2->score->increase(50);
//            if(typeid(*(colliding_items[i]))!=typeid(enemyship)){
//            //remove the both
//            scene()->removeItem(colliding_items[i]);
//            scene()->removeItem(this);
//            //delete both
//            delete colliding_items[i];
//            delete this;
//            }
//        }
//    }


    if(SeElimina==true){
        delete this;
    }
    else {
    //move bullet right
    setPos(x()+20,y());
    if(x()>=600){
        scene()->removeItem(this);
        delete this;
    }
   }
}
