#ifndef AMMO_H
#define AMMO_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>

class ammo: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    ammo(QGraphicsItem *parent = 0);
};


#endif // AMMO_H
