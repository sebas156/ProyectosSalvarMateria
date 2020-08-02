#include "enemyship.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>
#include <QList>
#include <stdlib.h>
#include "game2.h"
#include "bullet2.h"
#include "ship.h"

extern game2 * Game2;

enemyship::enemyship(QGraphicsItem *parent): ship(0,parent)
{
    TYPE=0;
}
