#include "healthbar.h"
#include "QDebug"
healthbar::healthbar(int width)
{
    W = width;
}

void healthbar::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::green);
    painter->setPen(Qt::black);
    painter->drawRect(QRectF(0,0,this->width(),10));
    qDebug()<<this->width();
}
