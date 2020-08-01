#ifndef GAME_H
#define GAME_H
#include "obstaculo.h"
#include <QPen>
#include <QBrush>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QMessageBox>
#include <QObject>
#include "player1.h"
#include <QTimer>
#include <QWidget>
#include <QList>
#include <queue>
#include <iostream>
#include "nodo.h"
#include "enemy.h"
#include "game2.h"
#include "pausar.h"
#include "perder.h"
#include "pasarnivel.h"

class game: public QGraphicsView
{
public:
    game(int*,int,string,QWidget *parent = 0);
    ~game();
    void SetNivelOrda(int,int);
    QGraphicsScene * scene;
    player1 * player;
    QGraphicsView * view;
    QMediaPlayer * music;
    void SetZombiesPorOrda();
    void EstablecerMuros();
    bool PisoConFriccion();
    bool EstablecerPisoQuitaVida();
    void ActualizarPosicionZombies();
    void InicializarCuadros();
    void CrearMapaDeCalor(nodo *, queue < nodo *>);
    void EstablecerVecinos();
    void ConstruccionCampoVectorial();
    void CalcularAceleracionZombie();
    void EstablecerZombies(float, float);
    void SetNumeroZombies(int);
    void NodosIniciales();
    void EstablecerTodosLosNodosComoNoVisitados();
    bool HayAlgunVecinoIntrasitable(list<nodo*>);
    bool CorresPondeAlgunVecinoEsquinero(int,int,int,int);
    bool CrearObstaculosMapa(int, int);
    QList<enemy *> Zombies;
    void BorrarZombie();
    void CaracteristicasZombiesPorNivelYOrda(enemy *);

    pausar * InterfazPausa;
    perder * InterfazPerder;
    PasarNivel * InterfazPasarNivel;

public slots:
    void PausarTodoJuego();
    void LiberarOrdasZombies();
    void ActualizarCamporVectorial();
    void ActualizarZombies();
    void follow_char();
    void PerdisteElJuego();
    void VerificarSiYaPasadeNivel();
    void ContinuarJugando();

private:
    QTimer * OrdasZombies;
    QTimer * timer;
    QTimer * VerificarSiPasaNivel;
    int nivel;
    int Orda;
    int TiempoEntreOrdas;
    int modo;
    int *NivelRetornar;
    QString NickNameInicioSesion;
    QList <obstaculo *> Paredes;
    nodo ArregloMatrizAbstracta[24][40];
    int NumeroZombies;
    queue <nodo *> frontera;
    int NIX,NIY;
    float t=0.1;
};

#endif // GAME_H
