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
#include "ganar.h"
#include "healthbar.h"
#include "healer.h"
#include "ammo.h"
#include "player2.h"
#include "score.h"

class game: public QGraphicsView
{
public:
    game(int *,int*,int,string,QWidget *parent = 0);
    ~game();
    void SetNivelOrda(int,int);
    QGraphicsScene * scene; // Variable para la escena.
    player1 * player;       // Jugador.
    player2 * player_2;      //jugador 2.
    QGraphicsView * view; // el view.
    QMediaPlayer * music;
    healthbar *hbar;
    healer * Healer;
    ammo * Ammo;
    Score * score;
    void SetZombiesPorOrda();   // Establece los zombies que se despliegan cada TiempoEntreOrdas segundos.
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
    int getmodo();
    int * puntosTotales;
    // Las siguientes variables van a estar conectadas con slots de VentanaPrincipalUsuario
    pausar * InterfazPausa;
    perder * InterfazPerder;
    PasarNivel * InterfazPasarNivel;
    ganar * InterfazGanar;
public slots:
    void PausarTodoJuego();      // Slot que al ejecutarse detiene todos los timers.
    void LiberarOrdasZombies();  // Libera una cierta cantidad de zombies cada TiempoEntreOrdas segundos.
    void ActualizarCamporVectorial();  //
    void ActualizarZombies();         // Actualiza la posicion de los zombies.
    void PerdisteElJuego();          // Slot que detiene todos los timers y muestra la interfaz de perder.
    void VerificarSiYaPasadeNivel(); // Verifica si pasa de nivel o en su defecto gana el juego
    void ContinuarJugando();        // Inicia todos los timers.
    void respawnAmmo();
    void ActualizarPosicionScore();

private:
    QTimer * OrdasZombies;
    QTimer * timer;
    QTimer * VerificarSiPasaNivel;
    QTimer *PosicionHealth;
    QTimer *re_fill;
    int nivel;                      //Nivel actual del juador.
    int Orda;                       // Orda actual del jugador.
    int TiempoEntreOrdas=6000;           // Tiempo que hay entre en despliegue de zombies y otro.
    int modo;
    int *NivelRetornar;             // NivelRetornar recibe la direccion de memoria de la variable en la que se guardó el nivel que se selecciono.
    QString NickNameInicioSesion;   // Almacena el nombre del usuario que ha iniciado sesion.
    QList <obstaculo *> Paredes;
    nodo ArregloMatrizAbstracta[24][40];  // Matriz de todos los nodos que cubren el mapa.
    int NumeroZombies;                    // Es el numero de zombies que en total van a aparecer en cada una de las 3 oleadas.
    queue <nodo *> frontera;              // Al amacena los nodos en los que el algoritmo de creacion del mapa de calor se va parando.
    int NIX,NIY;                          // Guarda la posision en la matriz de los nodos iniciales.
    float t=0.1;                          // Variable de tiempo para las ecuaciones de movimientos de los zombies.
    int ContadorNumeroMaximoZombies=0;    // Cuanta el numero de zombies que se han deplegado en una orda de aliens.
    int zombiesPorSpawn=6;               // Establece el numero de zombies que despliegan cada vez que el timer se reinicia.
    int maximoNumeroZombiesPorOrda=30;   // Esto es para el modo cooperativo. Establece el numero maximo de zombies que se despliega or orda.
                                         // Crece indefinidamente.
};

#endif // GAME_H
