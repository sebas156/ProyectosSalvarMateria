#ifndef GAME_H
#define GAME_H
#include <QPen>
#include <QBrush>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QObject>
#include "player1.h"
#include <QTimer>
#include <QWidget>
#include <QList>
#include <queue>
#include <iostream>
#include "nodo.h"
#include "enemy.h"

class game: public QGraphicsView
{
public:
    game(QWidget *parent = 0);
    QGraphicsScene * scene;
    player1 * player;
    QGraphicsView * view;
    void ActualizarPosicionZombies();
    void InicializarCuadros();
    void CrearMapaDeCalor(nodo *, queue < nodo *>);
    void EstablecerVecinos();
    void ConstruccionCampoVectorial();
    void CalcularAceleracionZombie();
    void EstablecerZombies();
    void SetNumeroZombies(int);
    void NodosIniciales();
    void EstablecerTodosLosNodosComoNoVisitados();
public slots:
    void ActualizarCamporVectorial();
    void ActualizarZombies();
    void follow_char();

private:
    QList<enemy *> Zombies;
    nodo ArregloMatrizAbstracta[24][40];
    int NumeroZombies;
    queue <nodo *> frontera;
    int NIX,NIY;
    float t=0.1;
};

#endif // GAME_H
