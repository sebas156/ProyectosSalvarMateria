#ifndef NODO_H
#define NODO_H
#include <iostream>
#include <list>
#include "vec3.h"
using namespace std;
class nodo
{
public:
    list <nodo *> vecinos;
    int resolucion=50; // Determina la dimension del nodo. cuadrado. Varia dependiendo del mapa.
    int PosRX;         // Posicion real del nodo en el mapa.
    int PosRY;
    bool transitable; // Verifica si en la posicion en la que está el cuadro hay un obstaculo.
    bool visitado;    // Es una bandera para el algoritmo de busqueda.
    int distancia;    // Indica que tan lejos está un nodo del personaje principal.
    vec3 Direccion;   // Contiene un vecto que indica la direccion en la que se debe ir para llegar de la manera
                      // mas eficiente posible al personaje.
    bool PuntoEstaAqui(float,float); // Verifica si para un punto dado se encuentra dentro de de un determinado cuadro.
    bool PisoHaceDano=false;
};

#endif // NODO_H
