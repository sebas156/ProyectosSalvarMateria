#include "spaceship.h"
#include <QKeyEvent>
#include "bullet2.h"
#include <QGraphicsScene>
#include <QDebug>
#include "game2.h"
#include <math.h>

extern game2 * Game2;

spaceship::spaceship(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    bulletsound = new QMediaPlayer;
    bulletsound->setMedia(QUrl("qrc:/2D/laser.mp3"));
    bulletsound->setVolume(5);
    setPixmap(QPixmap(":/2D/player.png"));

    setPixmap(QPixmap(":/2D/off.png").copy(0,0,106,56));
    setShapeMode(BoundingRectShape);

    movtimer = new QTimer();
    connect(movtimer,SIGNAL(timeout()),this,SLOT(move()));
    movtimer->start(5);

    acelerate = new QTimer();
    connect(acelerate,SIGNAL(timeout()),this,SLOT(change_speed()));
    acelerate->start(10);

    anim = new QTimer();
    connect(anim,SIGNAL(timeout()),this,SLOT(animate()));
    anim->start(20);

    seedtimer = new QTimer();
    connect(seedtimer,SIGNAL(timeout()),this,SLOT(increase_seed()));
    seedtimer->start(10000);

}

spaceship::~spaceship()
{
    for(int i=0; i<EnemyClase1.size();i++){
        delete EnemyClase1.at(i);
    }
    for(int i=0; i<EnemyClase2.size();i++){
        delete EnemyClase2.at(i);
    }
    delete movtimer;
    delete acelerate;
    delete anim;
    delete seedtimer;
    delete bulletsound;
}

void spaceship::keyPressEvent(QKeyEvent *event)
{
    if(TecladoBloqueado==true)
        return;
    //turn on thrusters
    if(event->key() == Qt::Key_W)
        if(!event->isAutoRepeat())
            I=1;

    if (event->key() == Qt::Key_Space){
        if(!event->isAutoRepeat())
            {
                bullet2 * Bullet2 = new bullet2();
                Bullet2->setPos(x()+100,y()+50);
                scene()->addItem(Bullet2);
            }

        //play sound
        if (bulletsound->state() == QMediaPlayer::PlayingState){
            bulletsound->setPosition(0);
        }
        else if(bulletsound->state() == QMediaPlayer::StoppedState){
            bulletsound->play();
        }
    }
    if(event->key() == Qt::Key_P){
        emit buttonClicked();
    }
}

void spaceship::keyReleaseEvent(QKeyEvent *event)
{
    //turn off thrusters
    if(event->key() == Qt::Key_W)
        if(!event->isAutoRepeat())
            I=0;
}

void spaceship::reduce_health()
{
    if(health>0){
        health-=5;
        Game2->bar->setWidth(health);
    }
}

int spaceship::get_health()
{
    return health;
}

void spaceship::PausarTodosLosTimers()
{
      for(int i=0;i<EnemyClase1.size();i++){
        EnemyClase1.at(i)->PausarTodoEnemigo();
      }
      for(int i=0;i<EnemyClase2.size();i++){
        EnemyClase2.at(i)->PausarTodoEnemigo();
      }
    movtimer->stop();
    acelerate->stop();
    anim->stop();
    seedtimer->stop();
    TecladoBloqueado=true;
}

void spaceship::ReactivarTodosLosTimers()
{
    for(int i=0;i<EnemyClase1.size();i++){
      EnemyClase1.at(i)->ContinuarEjecutando();
    }
    for(int i=0;i<EnemyClase2.size();i++){
      EnemyClase2.at(i)->ContinuarEjecutando();
    }
    movtimer->start(5);
    acelerate->start(10);
    anim->start(20);
    seedtimer->start(10000);
    TecladoBloqueado=false;
}

void spaceship::spawn()
{
    //create enemies
    if(seed==0)
    {
        enemyship * Enemyship = new enemyship;
        scene()->addItem(Enemyship);
        EnemyClase1.push_back(Enemyship);
    }

    if(seed==1)
    {
        sinenemyship * Sinenemyship = new sinenemyship(2);
        scene()->addItem(Sinenemyship);
        EnemyClase2.push_back(Sinenemyship);

        enemyship * Enemyship = new enemyship;
        scene()->addItem(Enemyship);
        Enemyship->setX(Sinenemyship->x()+120);
        EnemyClase1.push_back(Enemyship);
    }

    if(seed==2)
    {
        sinenemyship * Sinenemyship = new sinenemyship(1);
        scene()->addItem(Sinenemyship);
        EnemyClase2.push_back(Sinenemyship);
    }
}

void spaceship::move()
{
    setPos(x(),y()+v);
    for (int i = 0;i<EnemyClase1.size();i++) {
        float DistanciaHeroEnemigo=pow(pow(EnemyClase1.at(i)->x()-(this->x()+30),2)+pow(EnemyClase1.at(i)->y()-(this->y()+30),2),0.5);
        if(DistanciaHeroEnemigo<=40){
            EnemyClase1.at(i)->SeDebeEliminar=true;
        }
    }
    for (int i = 0;i<EnemyClase2.size();i++) {
        float DistanciaHeroEnemigo=pow(pow(EnemyClase2.at(i)->x()-this->x(),2)+pow(EnemyClase2.at(i)->y()-this->y(),2),0.5);
        if(DistanciaHeroEnemigo<=40){
            EnemyClase2.at(i)->SeDebeEliminar=true;
        }
    }


    for (int i = 0;i<EnemyClase1.size();i++) {
        auto iterador= EnemyClase1.begin();
        if(EnemyClase1.at(i)->SeDebeEliminar==true){
            delete EnemyClase1.at(i);
            iterador+=i;
            EnemyClase1.erase(iterador);
            i=0;
        }
    }
    for (int i = 0;i<EnemyClase2.size();i++) {
        auto iterador= EnemyClase2.begin();
        if(EnemyClase2.at(i)->SeDebeEliminar==true){
            delete EnemyClase2.at(i);
            iterador+=i;
            EnemyClase2.erase(iterador);
            i=0;
        }
    }

    if(y()>800)
       health=0;
}

void spaceship::change_speed()
{
    if(I==1)
    {
        if(v>=-vtf)
        {
            v+=g;
            v-=a;
        }
    }
    if(I==0)
    {
        if(v<=vf)
        {
            v+=g;
        }
    }
}

void spaceship::animate()
{
    if(I==0)
    {
        QPixmap image(":/2D/off.png");
        anim_counter();
        QPixmap cropped = image.copy(106*(i),0,106,56);
        setPixmap(QPixmap(cropped));
    }

    else
    {
        QPixmap image(":/2D/on.png");
        anim_counter();
        QPixmap cropped = image.copy(106*(i),0,106,56);
        setPixmap(QPixmap(cropped));
    }
}

void spaceship::anim_counter()
{
    if(i==4)
        i=0;
    else
        i++;
}

void spaceship::increase_seed()
{
    if(seed==2)
        seed=0;
    else
        seed++;
    collidingItems().clear();
}
