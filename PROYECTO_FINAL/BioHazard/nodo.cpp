#include "nodo.h"

bool nodo::PuntoEstaAqui(float x1, float y1)
{
    if((x1>=(PosRX - 25)) and (y1>=(PosRY - 25)) and (x1<=(PosRX+25))and (y1<=(PosRY+25)))
        return true;
    else
        return false;
}

