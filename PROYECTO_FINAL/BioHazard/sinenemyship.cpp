#include "sinenemyship.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>
#include <QList>
#include <stdlib.h>
#include "game2.h"
#include "bullet2.h"
#include "math.h"
#include "ship.h"

extern game2 * Game2;

sinenemyship::sinenemyship(int type, QGraphicsItem *parent): ship(type,parent)
{
    TYPE=type;
    if(TYPE<1||TYPE>2)
        TYPE=1;
}

