#ifndef SPACESHIP_H
#define SPACESHIP_H
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QMediaPlayer>
#include <QTimer>

class spaceship:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    spaceship(QGraphicsItem * parent = 0);
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent *event);
    QTimer *movtimer;
    QTimer *acelerate;
    QTimer *anim;
    QTimer *seedtimer;
    void reduce_health();
    int get_health();
public slots:
    void spawn();
    void move();
    void change_speed();
    void animate();
    void anim_counter();
    void increase_seed();
private:
    QMediaPlayer * bulletsound;
    float v=0;      //speed
    float g=0.1;   //equivalent of gravity
    float a=0.16;   //thruster acceleration
    float vf=4.00;   //top-speed in free-fall
    float vtf=4.00;    //thruster top-speed
    int I=0;        //thruster state // 1 = ON, 0 = OFF
    int i=0;        //index for each animation frame
    int seed=0;
    int health=100;
};

#endif // SPACESHIP_H
