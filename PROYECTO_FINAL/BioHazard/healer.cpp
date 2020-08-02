#include "healer.h"
#include "game.h"

extern game * Game;

healer::healer(QGraphicsItem *parent)
{
    //draw the item
    setPixmap(QPixmap(":/2D/healer.png"));
}
