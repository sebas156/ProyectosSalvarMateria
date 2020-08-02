#include "spaceship.h"
#include <QKeyEvent>
#include "bullet2.h"
#include <QGraphicsScene>
#include <QDebug>
#include "enemyship.h"
#include "sinenemyship.h"
#include "game2.h"

extern game2 * Game2;

spaceship::spaceship(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    bulletsound = new QMediaPlayer;
    bulletsound->setMedia(QUrl("qrc:/2D/laser.mp3"));
    bulletsound->setVolume(5);
    setPixmap(QPixmap(":/2D/player.png"));

    setPixmap(QPixmap(":/2D/off.png").copy(0,0,106,56));
    setShapeMode(BoundingRectShape);

    QTimer *movtimer = new QTimer();
    connect(movtimer,SIGNAL(timeout()),this,SLOT(move()));
    movtimer->start(5);

    QTimer *acelerate = new QTimer();
    connect(acelerate,SIGNAL(timeout()),this,SLOT(change_speed()));
    acelerate->start(10);

    QTimer *anim = new QTimer();
    connect(anim,SIGNAL(timeout()),this,SLOT(animate()));
    anim->start(20);

    QTimer *seedtimer = new QTimer();
    connect(seedtimer,SIGNAL(timeout()),this,SLOT(increase_seed()));
    seedtimer->start(10000);

}

void spaceship::keyPressEvent(QKeyEvent *event)
{
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

void spaceship::spawn()
{
    //create enemies
    if(seed==0)
    {
        enemyship * Enemyship = new enemyship;
        scene()->addItem(Enemyship);
    }

    if(seed==1)
    {
        sinenemyship * Sinenemyship = new sinenemyship(2);
        scene()->addItem(Sinenemyship);

        enemyship * Enemyship = new enemyship;
        scene()->addItem(Enemyship);
        Enemyship->setX(Sinenemyship->x()+120);
    }

    if(seed==2)
    {
        sinenemyship * Sinenemyship = new sinenemyship(1);
        scene()->addItem(Sinenemyship);
    }
}

void spaceship::move()
{
    setPos(x(),y()+v);
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
