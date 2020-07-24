#ifndef PLAYER1_H
#define PLAYER1_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPainter>

class player1: public QObject, /*public QGraphicsRectItem,*/ public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    player1();
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent *event);
    QTimer *movtimer;
    QTimer *acelerate;
    QTimer *timer_anim;
    void RestarVida(int);
public slots:
    void spawn();
    void move();
    void change_speed();
    void animate();
    void anim_counter();
signals:
    void buttonPressed();
    void buttonClicked();
private:
    int Vida=200;
    int L=0;
    int R=0;
    int U=0;
    int D=0;
    int i=0;    //animation index
    char aim;

    //float V = 0;
    float Vx = 0;
    float Vy = 0;
    float Vf = 1.4;
    float a = 0.1;

};


#endif // PLAYER1_H
