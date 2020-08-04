#ifndef PLAYER2_H
#define PLAYER2_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPainter>
#include "player1.h"

class player2: public QObject,/* public QGraphicsRectItem,*/ public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    player2();
    ~player2();
    QTimer *movtimer;
    QTimer *acelerate;
    QTimer *timer_anim;
    float Vx = 0;
    float Vy = 0;
    float Vf = 1.4;
    float a = 0.1;
    void RestarVida(int);
    float get_vida();
    void PonerTodoEnCero();
public slots:
    void move();
    void change_speed();
    void animate();
    void anim_counter();
signals:
    void buttonPressed();
    void buttonClicked();
public:
    float Vida=100;
    int L=0;
    int R=0;
    int U=0;
    int D=0;
    int i=0;    //animation index
    char aim;
    int shots=0; //counter of bullets

    //float V = 0;
};
#endif // PLAYER2_H
