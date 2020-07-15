#include "vec3.h"

vec3::vec3()
{

}

void vec3::MultiplicarEscalar(float s)
{
    // Multiplica cada componente por el escalar s.
    x=x*s;
    y=y*s;
}

float vec3::Magnitud()
{
    // Magnitud del vector.
    float mag = sqrt(pow(x, 2) + pow(y, 2));
    return mag;
}

void vec3::Normalizar()
{
    // Normaliza el vector.
    double mag = sqrt(pow(x, 2) + pow(y, 2));
    x = x / mag;
    y = y / mag;
}
