#ifndef VEC3_H
#define VEC3_H
#include <iostream>
#include <math.h>

using namespace std;

class vec3
{
public:
    vec3();
    // Mulriplica el vector por un escalar.
    void MultiplicarEscalar(float s);

    // Calcula la magnitud del vector
    float Magnitud();

    // Normaliza el vector
    void Normalizar();

    // Componentes del vector.
    float x;
    float y;
};

#endif // VEC3_H
