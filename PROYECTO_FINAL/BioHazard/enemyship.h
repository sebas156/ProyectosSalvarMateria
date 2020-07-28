#ifndef ENEMYSHIP_H
#define ENEMYSHIP_H
#include <QGraphicsPixmapItem>
#include <QObject>

class enemyship:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    enemyship(QGraphicsItem * parent=0);
    QTimer *anim;
public slots:
    void move();
    void animate();
    void anim_counter();

private:
    int i=0;        //index for each animation frame
};
#endif // ENEMYSHIP_H
