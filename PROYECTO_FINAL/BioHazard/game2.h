#ifndef GAME2_H
#define GAME2_H
#include <QGraphicsScene>
#include "spaceship.h"
#include <QGraphicsView>
#include <QTimer>
#include <QObject>
#include <QWidget>
#include "score.h"
#include "health.h"

class game2: public QGraphicsView
{
public:
    game2(QWidget *parents = 0);
    QTimer *seedtimer;
    QGraphicsView * view;
    QGraphicsScene * scene;
    spaceship * ship;
    Score * score;
    Health * health;
public slots:
    void spawn();
    void increase_seed();
private:
    int seed=0;
};
#endif // GAME2_H
