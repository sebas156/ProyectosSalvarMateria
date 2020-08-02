#ifndef HEALTHBAR_H
#define HEALTHBAR_H
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QPainter>
#include <QRect>
class healthbar: public QGraphicsRectItem, public QRect
{
public:
    healthbar(int width);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
private:
    float W;  //width

};

#endif // HEALTHBAR_H
