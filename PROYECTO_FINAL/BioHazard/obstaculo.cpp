#include "obstaculo.h"
#include <QGraphicsEllipseItem>

obstaculo::obstaculo(int X, int Y, int Ancho, int Largo)
{
    setRect(X-25,Y-25,Largo,Ancho);
}
