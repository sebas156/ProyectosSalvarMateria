#ifndef BULLET2_H
#define BULLET2_H
#include "game2.h"
#include <QGraphicsPixmapItem>

class bullet2:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    bullet2(QGraphicsItem *parent = 0);

public slots:
    void move();

};

#endif // BULLET2_H
