#ifndef ENEMYSHIP_H
#define ENEMYSHIP_H

#include "ship.h"

class enemyship:public ship // Herencia de la clase ship.
{
public:
    enemyship(QGraphicsItem * parent=0);
};
#endif // ENEMYSHIP_H
