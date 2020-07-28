#ifndef SINENEMYSHIP_H
#define SINENEMYSHIP_H

#include <QGraphicsPixmapItem>
#include <QObject>

class sinenemyship:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    sinenemyship(QGraphicsItem * parent=0);
    QTimer *anim;
    int mode;
public slots:
    void move();
    void animate();
    void anim_counter();
private:
    int i=0;        //index for each animation frame
};

#endif // SINENEMYSHIP_H
