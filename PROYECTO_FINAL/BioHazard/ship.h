#ifndef SHIP_H
#define SHIP_H


#include <QGraphicsPixmapItem>
#include <QObject>

class ship:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    ship(int type, QGraphicsItem * parent=0);
    ~ship();
    QTimer *anim;
    QTimer * timer;
    int mode;
    bool SeDebeEliminar=false;
public slots:
    void move();
    void animate();
    void anim_counter();
    void PausarTodoEnemigo();
    void ContinuarEjecutando();
protected:
    int i=0;        //index for each animation frame
    int TYPE;


};

#endif // SHIP_H
