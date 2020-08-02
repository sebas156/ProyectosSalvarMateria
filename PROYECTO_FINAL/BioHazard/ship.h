#ifndef SHIP_H
#define SHIP_H


#include <QGraphicsPixmapItem>
#include <QObject>

class ship:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    ship(int type, QGraphicsItem * parent=0);
    QTimer *anim;
    int mode;
public slots:
    void move();
    void animate();
    void anim_counter();
protected:
    int i=0;        //index for each animation frame
    int TYPE;
};

#endif // SHIP_H
