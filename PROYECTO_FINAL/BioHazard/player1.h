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
    ~player1();
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent *event);
    QTimer *movtimer;
    QTimer *acelerate;
    QTimer *timer_anim;
    float Vx = 0;
    float Vy = 0;
    float Vf = 1.4;
    float a = 0.1;
    void RestarVida(int);
    bool TecladoBloqueado=false;
    void PonerTodoEnCero();
    float get_vida();
public slots:
    void spawn();
    void move();
    void change_speed();
    void animate();
    void anim_counter();
signals:
    void buttonPressed();
    void buttonClicked();
    void buttonClicked2();
private:
    int Vida=100;
    int L=0;
    int R=0;
    int U=0;
    int D=0;
    int i=0;    //animation index
    char aim;
    int shots=0; //shots counter (cartridge)

    //float V = 0;

};


#endif // PLAYER1_H
