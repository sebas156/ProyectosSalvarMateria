#ifndef BULLET_H
#define BULLET_H
#include <QGraphicsRectItem>
#include <QObject>
#include "vec3.h"

class bullet: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    bullet(char dir);
    int Masa=20;
    vec3 velocidad;
public slots:
    void move();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
private:
    int L=0;
    int R=0;
    int U=0;
    int D=0;
};

#endif // BULLET_H
