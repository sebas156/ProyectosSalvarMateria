#ifndef GAME2_H
#define GAME2_H
#include <QGraphicsScene>
#include "spaceship.h"
#include <QGraphicsView>
#include <QTimer>
#include <QObject>
#include <QWidget>
#include "score.h"
#include "healthbar.h"
#include "pausar.h"
#include "perder.h"
#include "pasarnivel.h"
#include <iostream>
#include <QLabel>
using namespace std;

class game2: public QGraphicsView
{
public:
    game2(int *,string,QWidget *parents = 0);
    ~game2();
    QLabel *gif_anim;
    QTimer *TimerPerdiste;
    QTimer * TiempoParaAguantar;
    QGraphicsView * view;
    QGraphicsScene * scene;
    spaceship * ship;
    Score * score;
    healthbar * bar;
    QMovie *movie;
    QTimer * timer;
    pausar * InterfazPausar;
    perder * InterfazPerder;
    PasarNivel * InterfazPasarNivel;
    QMediaPlayer * music;
public slots:
    void spawn();
    void increase_seed();
    void QuierenPausar();
    void QuierenContinuar();
    void VerificarSiPerdio();
    void PasarDeNivel();
private:
    int seed=0;
    int TiempoRestantePasarNivel;
    int * NivelRetornar;
    QString NickNameUsuario;
};
#endif // GAME2_H
