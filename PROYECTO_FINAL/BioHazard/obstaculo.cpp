#include "obstaculo.h"

obstaculo::obstaculo(int X, int Y, int Ancho, int Largo)
{
    setRect(X-20,Y-20,Largo,Ancho);
}
