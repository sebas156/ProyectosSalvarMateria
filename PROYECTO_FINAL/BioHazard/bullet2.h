#ifndef BULLET2_H
#define BULLET2_H
#include "game2.h"
#include <QGraphicsPixmapItem>

class bullet2:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    bullet2(QGraphicsItem *parent = 0);
    ~bullet2();

public slots:
    void move();

private:
    bool SeElimina=false;
    QTimer * timer;

};

#endif // BULLET2_H
