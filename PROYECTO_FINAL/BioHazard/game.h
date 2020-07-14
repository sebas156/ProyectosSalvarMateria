#ifndef GAME_H
#define GAME_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QObject>
#include "player1.h"
#include <QTimer>
#include <QWidget>

class game: public QGraphicsView
{
public:
    game(QWidget *parent = 0);
    QGraphicsScene * scene;
    player1 * player;
    QGraphicsView * view;
public slots:
    void follow_char();
};

#endif // GAME_H
