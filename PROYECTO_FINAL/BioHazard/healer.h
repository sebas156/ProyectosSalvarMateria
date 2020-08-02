#ifndef HEALER_H
#define HEALER_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>

class healer: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    //healer();
    healer(QGraphicsItem *parent = 0);
};

#endif // HEALER_H
