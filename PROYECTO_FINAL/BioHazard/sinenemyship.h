#ifndef SINENEMYSHIP_H
#define SINENEMYSHIP_H

#include "ship.h"

class sinenemyship:public ship // Herencia de la clase ship.
{
public:
    sinenemyship(int type, QGraphicsItem * parent=0);
};

#endif // SINENEMYSHIP_H
