#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QObject>
#include "player1.h"
#include <QTimer>
#include "game.h"
#include <QGraphicsEllipseItem>
#include <QDebug>
#include "bullet.h"
#include <stdlib.h>
#include <time.h>

game::game(int * NivelInput,int ModoInput,string InicioSesion,QWidget *parent)
{
    // Modo de juego.
    modo = ModoInput;
    // Nombre del usuario que ha iniciado sesion.
    NickNameInicioSesion=QString::fromStdString(InicioSesion);

    //Apuntadores. De esta manera puedo afectar la Variable NivelInput desde la variable NivelRetorna.
    NivelRetornar=NivelInput;
    SetNivelOrda(*NivelInput,1);

    // Crea la variable de la interfaz que se genera si el jugador pausa el juego.
    InterfazPausa=new pausar(NickNameInicioSesion);
    connect(InterfazPausa,&pausar::buttonClicked,this,&game::ContinuarJugando);

    // Crea la variable de la interfaz que se genera si al juador lo matan.
    InterfazPerder= new perder();
    InterfazPasarNivel= new PasarNivel();

    //Crea la variable con la interfaz que se genera si el jugador gana el juego (Pasa el ultimo nivel.)
    InterfazGanar= new ganar();

    //create a scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,2000,1200);
    setScene(scene);

    //create an item to put into the scene
    player = new player1();

    //add previous item to the scene
    scene->addItem(player);

    //make rect focusable
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    //add view
    view = new QGraphicsView(scene);
    if(nivel==1)
        view->setBackgroundBrush(QBrush(QImage(":/BGI/escenario.png")));
    else
        view->setBackgroundBrush(QBrush(QImage(":/BGI/escenario2.png")));
    //view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    view->setFixedSize(800,600);

    player->setPos(700,700);

    view->show();
    // Esta funcion esta blece los zombies que salen segun la ordan en la que se encuentre.
    SetZombiesPorOrda();


    //Las funciones a continuacion inicializan y constituyen el campo vectorial.
    //______________________________________________
    InicializarCuadros();
    EstablecerVecinos();
    EstablecerPisoQuitaVida();
    PisoConFriccion();
    EstablecerMuros();
    NodosIniciales();
    CrearMapaDeCalor(&ArregloMatrizAbstracta[NIX][NIY],frontera);
    ConstruccionCampoVectorial();
    ArregloMatrizAbstracta[NIX][NIY].Direccion.x=0;
    ArregloMatrizAbstracta[NIX][NIY].Direccion.y=0;
    //________________________________________________


    // Este timer libera un numero de zombies cada TiempoEntreOrdas segundos.
    OrdasZombies = new QTimer;
    connect(OrdasZombies, &QTimer::timeout,this,&game::LiberarOrdasZombies);
    OrdasZombies->start(TiempoEntreOrdas);



    connect(player,&player1::buttonClicked,this,&game::PerdisteElJuego);
    connect(player,&player1::buttonPressed,this,&game::ActualizarCamporVectorial);
    connect(player,&player1::buttonClicked2,this,&game::PausarTodoJuego);


    // Actualiza la posicion de los zombies.
    timer = new QTimer;
    connect(timer, &QTimer::timeout,this,&game::ActualizarZombies);
    timer->start(20);


    // Está verificando si se pasa de nivel.
    VerificarSiPasaNivel = new QTimer;
    connect(VerificarSiPasaNivel, &QTimer::timeout,this,&game::VerificarSiYaPasadeNivel);
    VerificarSiPasaNivel->start(10);

    // crear barra de salud
    hbar = new healthbar(player->get_vida());
    scene->addItem(hbar);
    hbar->setPos(player->x(),player->y()-20);


    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //play background music
    music = new QMediaPlayer;
    music->setMedia(QUrl("qrc:/AUD/00.mp3"));
    music->setVolume(25);
    music->play();
}

game::~game()
{
    for(int i=0;i<Zombies.size();i++){
        QList<enemy *>::iterator h=Zombies.begin();
        delete Zombies.at(i);
        h+=i;
        Zombies.erase(h);
        h.~iterator();
    }

    for (int i = 0; i<Paredes.size();i++){
        QList<obstaculo *>::iterator V=Paredes.begin();
        delete Paredes.at(i);
        V+=i;
        Paredes.erase(V);
        V.~iterator();
    }
    delete player;
    delete scene;
    delete view;
    delete music;
    delete InterfazGanar;
    delete InterfazPausa;
    delete InterfazPerder;
    delete InterfazPasarNivel;
    delete OrdasZombies;
    delete timer;
    delete VerificarSiPasaNivel;
}

void game::SetNivelOrda(int NivelAux, int OrdaAux)
{
    // Establece la orda y el nivel actual.
    nivel=NivelAux;
    Orda=OrdaAux;
}

void game::SetZombiesPorOrda()
{
    //Esta funcion establece el numero de zombies cada vez que el timer OrdasZombies se inicie. Según la orda en la que se encuentre.
    if(Orda==1){
        TiempoEntreOrdas=6000;
        SetNumeroZombies(6);
    }
    else if(Orda==2){
        TiempoEntreOrdas=15000;
        SetNumeroZombies(9);
    }
    else if(Orda==3){
        TiempoEntreOrdas=18000;
        SetNumeroZombies(12);
    }
}

void game::EstablecerMuros()
{
    // Busqueda exhaustiva y coloca un objeto obstaculo.
    for(int fila=0;fila<24;fila++){
        for(int columna =0; columna<40; columna++){
            if(nivel==1){
                if(fila==6 and columna==15 ){
                    obstaculo * Auxiliar = new obstaculo(ArregloMatrizAbstracta[fila][columna].PosRX,ArregloMatrizAbstracta[fila][columna].PosRY,95,145);
                     Auxiliar->setPen(Qt::NoPen);
                    scene->addItem(Auxiliar);
                    Paredes.push_back(Auxiliar);
                }
                else if(fila==7 and columna==22 ){
                    obstaculo * Auxiliar = new obstaculo(ArregloMatrizAbstracta[fila][columna].PosRX,ArregloMatrizAbstracta[fila][columna].PosRY,45,95);
                    Auxiliar->setPen(Qt::NoPen);
                    scene->addItem(Auxiliar);
                    Paredes.push_back(Auxiliar);
                }
                else if(fila==5 and columna==2 ){
                    obstaculo * Auxiliar = new obstaculo(ArregloMatrizAbstracta[fila][columna].PosRX,ArregloMatrizAbstracta[fila][columna].PosRY,45,95);
                    scene->addItem(Auxiliar);
                    Paredes.push_back(Auxiliar);
                }
                else if(fila==6 and columna==28 ){
                    obstaculo * Auxiliar = new obstaculo(ArregloMatrizAbstracta[fila][columna].PosRX,ArregloMatrizAbstracta[fila][columna].PosRY,45,145);
                    scene->addItem(Auxiliar);
                    Paredes.push_back(Auxiliar);
                }
                else if(fila==4 and columna==0){
                    obstaculo * Auxiliar = new obstaculo(ArregloMatrizAbstracta[fila][columna].PosRX,ArregloMatrizAbstracta[fila][columna].PosRY,95,95);
                    scene->addItem(Auxiliar);
                    Paredes.push_back(Auxiliar);
                }
                else if(fila==7 and columna==32){
                    obstaculo * Auxiliar = new obstaculo(ArregloMatrizAbstracta[fila][columna].PosRX,ArregloMatrizAbstracta[fila][columna].PosRY,95,95);
                    scene->addItem(Auxiliar);
                    Paredes.push_back(Auxiliar);
                }
                else if(fila==8 and columna==25){
                    obstaculo * Auxiliar = new obstaculo(ArregloMatrizAbstracta[fila][columna].PosRX,ArregloMatrizAbstracta[fila][columna].PosRY,45,95);
                    scene->addItem(Auxiliar);
                    Paredes.push_back(Auxiliar);
                }
                else if(fila==10 and columna==5){
                    obstaculo * Auxiliar = new obstaculo(ArregloMatrizAbstracta[fila][columna].PosRX,ArregloMatrizAbstracta[fila][columna].PosRY,95,145);
                    scene->addItem(Auxiliar);
                    Paredes.push_back(Auxiliar);
                }
                else if(fila==8 and columna==0){
                    obstaculo * Auxiliar = new obstaculo(ArregloMatrizAbstracta[fila][columna].PosRX,ArregloMatrizAbstracta[fila][columna].PosRY,195,245);
                    scene->addItem(Auxiliar);
                    Paredes.push_back(Auxiliar);
                }
                else if(fila==13 and columna==11){
                    obstaculo * Auxiliar = new obstaculo(ArregloMatrizAbstracta[fila][columna].PosRX,ArregloMatrizAbstracta[fila][columna].PosRY,95,95);
                    scene->addItem(Auxiliar);
                    Paredes.push_back(Auxiliar);
                }
                else if(fila==11 and columna==15){
                    obstaculo * Auxiliar = new obstaculo(ArregloMatrizAbstracta[fila][columna].PosRX,ArregloMatrizAbstracta[fila][columna].PosRY,95,95);
                    scene->addItem(Auxiliar);
                    Paredes.push_back(Auxiliar);
                }
                else if(fila==14 and columna==17){
                    obstaculo * Auxiliar = new obstaculo(ArregloMatrizAbstracta[fila][columna].PosRX,ArregloMatrizAbstracta[fila][columna].PosRY,45,95);
                    scene->addItem(Auxiliar);
                    Paredes.push_back(Auxiliar);
                }
                else if(fila==13 and columna==22){
                    obstaculo * Auxiliar = new obstaculo(ArregloMatrizAbstracta[fila][columna].PosRX,ArregloMatrizAbstracta[fila][columna].PosRY,95,95);
                    scene->addItem(Auxiliar);
                    Paredes.push_back(Auxiliar);
                }
                else if(fila==13 and columna==30){
                    obstaculo * Auxiliar = new obstaculo(ArregloMatrizAbstracta[fila][columna].PosRX,ArregloMatrizAbstracta[fila][columna].PosRY,45,95);
                    scene->addItem(Auxiliar);
                    Paredes.push_back(Auxiliar);
                }
                else if(fila==9 and columna==31){
                    obstaculo * Auxiliar = new obstaculo(ArregloMatrizAbstracta[fila][columna].PosRX,ArregloMatrizAbstracta[fila][columna].PosRY,145,195);
                    scene->addItem(Auxiliar);
                    Paredes.push_back(Auxiliar);
                }
                else if(fila==15 and columna==38){
                    obstaculo * Auxiliar = new obstaculo(ArregloMatrizAbstracta[fila][columna].PosRX,ArregloMatrizAbstracta[fila][columna].PosRY,45,95);
                    Auxiliar->setPen(Qt::NoPen);
                    scene->addItem(Auxiliar);
                    Paredes.push_back(Auxiliar);
                }
                else if(fila==16 and columna==37){
                    obstaculo * Auxiliar = new obstaculo(ArregloMatrizAbstracta[fila][columna].PosRX,ArregloMatrizAbstracta[fila][columna].PosRY,45,95);
                    Auxiliar->setPen(Qt::NoPen);
                    scene->addItem(Auxiliar);
                    Paredes.push_back(Auxiliar);
                }
                else if(fila==17 and columna==1){
                    obstaculo * Auxiliar = new obstaculo(ArregloMatrizAbstracta[fila][columna].PosRX,ArregloMatrizAbstracta[fila][columna].PosRY,45,145);
                    scene->addItem(Auxiliar);
                    Paredes.push_back(Auxiliar);
                }
                else if(fila==19 and columna==9){
                    obstaculo * Auxiliar = new obstaculo(ArregloMatrizAbstracta[fila][columna].PosRX,ArregloMatrizAbstracta[fila][columna].PosRY,45,145);
                    scene->addItem(Auxiliar);
                    Paredes.push_back(Auxiliar);
                }
                else if(fila==19 and columna==18){
                    obstaculo * Auxiliar = new obstaculo(ArregloMatrizAbstracta[fila][columna].PosRX,ArregloMatrizAbstracta[fila][columna].PosRY,95,145);
                    scene->addItem(Auxiliar);
                    Paredes.push_back(Auxiliar);
                }
                else if(fila==23 and columna==22){
                    obstaculo * Auxiliar = new obstaculo(ArregloMatrizAbstracta[fila][columna].PosRX,ArregloMatrizAbstracta[fila][columna].PosRY,45,145);
                    scene->addItem(Auxiliar);
                    Paredes.push_back(Auxiliar);
                }
                else if(fila==18 and columna==26){
                    obstaculo * Auxiliar = new obstaculo(ArregloMatrizAbstracta[fila][columna].PosRX,ArregloMatrizAbstracta[fila][columna].PosRY,95,95);
                    scene->addItem(Auxiliar);
                    Paredes.push_back(Auxiliar);
                }
                else if(fila==16 and columna==32){
                    obstaculo * Auxiliar = new obstaculo(ArregloMatrizAbstracta[fila][columna].PosRX,ArregloMatrizAbstracta[fila][columna].PosRY,95,95);
                    scene->addItem(Auxiliar);
                    Paredes.push_back(Auxiliar);
                }
            }
            else {
                if(fila==1 and columna==0 ){
                    obstaculo * Auxiliar = new obstaculo(ArregloMatrizAbstracta[fila][columna].PosRX,ArregloMatrizAbstracta[fila][columna].PosRY,95,95);
                    scene->addItem(Auxiliar);
                    Paredes.push_back(Auxiliar);
                }
                else if(fila==5 and columna==2 ){
                    obstaculo * Auxiliar = new obstaculo(ArregloMatrizAbstracta[fila][columna].PosRX,ArregloMatrizAbstracta[fila][columna].PosRY,45,95);
                    scene->addItem(Auxiliar);
                    Paredes.push_back(Auxiliar);
                }
                else if(fila==4 and columna==24 ){
                    obstaculo * Auxiliar = new obstaculo(ArregloMatrizAbstracta[fila][columna].PosRX,ArregloMatrizAbstracta[fila][columna].PosRY,95,95);
                    scene->addItem(Auxiliar);
                    Paredes.push_back(Auxiliar);
                }
                else if(fila==6 and columna==13 ){
                    obstaculo * Auxiliar = new obstaculo(ArregloMatrizAbstracta[fila][columna].PosRX,ArregloMatrizAbstracta[fila][columna].PosRY,95,95);
                    scene->addItem(Auxiliar);
                    Paredes.push_back(Auxiliar);
                }
                else if(fila==6 and columna==17){
                    obstaculo * Auxiliar = new obstaculo(ArregloMatrizAbstracta[fila][columna].PosRX,ArregloMatrizAbstracta[fila][columna].PosRY,45,145);
                    scene->addItem(Auxiliar);
                    Paredes.push_back(Auxiliar);
                }
                else if(fila==4 and columna==24){
                    obstaculo * Auxiliar = new obstaculo(ArregloMatrizAbstracta[fila][columna].PosRX,ArregloMatrizAbstracta[fila][columna].PosRY,95,95);
                    scene->addItem(Auxiliar);
                    Paredes.push_back(Auxiliar);
                }
                else if(fila==6 and columna==24){
                    obstaculo * Auxiliar = new obstaculo(ArregloMatrizAbstracta[fila][columna].PosRX,ArregloMatrizAbstracta[fila][columna].PosRY,45,95);
                    scene->addItem(Auxiliar);
                    Paredes.push_back(Auxiliar);
                }
                else if(fila==9 and columna==17){
                    obstaculo * Auxiliar = new obstaculo(ArregloMatrizAbstracta[fila][columna].PosRX,ArregloMatrizAbstracta[fila][columna].PosRY,45,45);
                    scene->addItem(Auxiliar);
                    Paredes.push_back(Auxiliar);
                }
                else if(fila==9 and columna==21){
                    obstaculo * Auxiliar = new obstaculo(ArregloMatrizAbstracta[fila][columna].PosRX,ArregloMatrizAbstracta[fila][columna].PosRY,45,245);
                    scene->addItem(Auxiliar);
                    Paredes.push_back(Auxiliar);
                }
                else if(fila==9 and columna==26){
                    obstaculo * Auxiliar = new obstaculo(ArregloMatrizAbstracta[fila][columna].PosRX,ArregloMatrizAbstracta[fila][columna].PosRY,95,95);
                    scene->addItem(Auxiliar);
                    Paredes.push_back(Auxiliar);
                }
                else if(fila==10 and columna==9){
                    obstaculo * Auxiliar = new obstaculo(ArregloMatrizAbstracta[fila][columna].PosRX,ArregloMatrizAbstracta[fila][columna].PosRY,45,45);
                    scene->addItem(Auxiliar);
                    Paredes.push_back(Auxiliar);
                }
                else if(fila==8 and columna==33){
                    obstaculo * Auxiliar = new obstaculo(ArregloMatrizAbstracta[fila][columna].PosRX,ArregloMatrizAbstracta[fila][columna].PosRY,45,195);
                    scene->addItem(Auxiliar);
                    Paredes.push_back(Auxiliar);
                }
                else if(fila==8 and columna==38){
                    obstaculo * Auxiliar = new obstaculo(ArregloMatrizAbstracta[fila][columna].PosRX,ArregloMatrizAbstracta[fila][columna].PosRY,95,95);
                    scene->addItem(Auxiliar);
                    Paredes.push_back(Auxiliar);
                }
                else if(fila==12 and columna==17){
                    obstaculo * Auxiliar = new obstaculo(ArregloMatrizAbstracta[fila][columna].PosRX,ArregloMatrizAbstracta[fila][columna].PosRY,45,195);
                    scene->addItem(Auxiliar);
                    Paredes.push_back(Auxiliar);
                }
                else if(fila==12 and columna==25){
                    obstaculo * Auxiliar = new obstaculo(ArregloMatrizAbstracta[fila][columna].PosRX,ArregloMatrizAbstracta[fila][columna].PosRY,95,45);
                    scene->addItem(Auxiliar);
                    Paredes.push_back(Auxiliar);
                }
                else if(fila==14 and columna==1){
                    obstaculo * Auxiliar = new obstaculo(ArregloMatrizAbstracta[fila][columna].PosRX,ArregloMatrizAbstracta[fila][columna].PosRY,45,45);
                    scene->addItem(Auxiliar);
                    Paredes.push_back(Auxiliar);
                }
                else if(fila==14 and columna==7){
                    obstaculo * Auxiliar = new obstaculo(ArregloMatrizAbstracta[fila][columna].PosRX,ArregloMatrizAbstracta[fila][columna].PosRY,45,45);
                    scene->addItem(Auxiliar);
                    Paredes.push_back(Auxiliar);
                }
                else if(fila==13 and columna==17){
                    obstaculo * Auxiliar = new obstaculo(ArregloMatrizAbstracta[fila][columna].PosRX,ArregloMatrizAbstracta[fila][columna].PosRY,95,45);
                    scene->addItem(Auxiliar);
                    Paredes.push_back(Auxiliar);
                }
                else if(fila==14 and columna==31){
                    obstaculo * Auxiliar = new obstaculo(ArregloMatrizAbstracta[fila][columna].PosRX,ArregloMatrizAbstracta[fila][columna].PosRY,95,45);
                    scene->addItem(Auxiliar);
                    Paredes.push_back(Auxiliar);
                }
                else if(fila==16 and columna==23){
                    obstaculo * Auxiliar = new obstaculo(ArregloMatrizAbstracta[fila][columna].PosRX,ArregloMatrizAbstracta[fila][columna].PosRY,45,45);
                    scene->addItem(Auxiliar);
                    Paredes.push_back(Auxiliar);
                }
                else if(fila==20 and columna==2){
                    obstaculo * Auxiliar = new obstaculo(ArregloMatrizAbstracta[fila][columna].PosRX,ArregloMatrizAbstracta[fila][columna].PosRY,95,145);
                    scene->addItem(Auxiliar);
                    Paredes.push_back(Auxiliar);
                }
                else if(fila==20 and columna==17){
                    obstaculo * Auxiliar = new obstaculo(ArregloMatrizAbstracta[fila][columna].PosRX,ArregloMatrizAbstracta[fila][columna].PosRY,45,45);
                    scene->addItem(Auxiliar);
                    Paredes.push_back(Auxiliar);
                }
                else if(fila==21 and columna==25){
                    obstaculo * Auxiliar = new obstaculo(ArregloMatrizAbstracta[fila][columna].PosRX,ArregloMatrizAbstracta[fila][columna].PosRY,45,45);
                    scene->addItem(Auxiliar);
                    Paredes.push_back(Auxiliar);
                }
                else if(fila==21 and columna==37){
                    obstaculo * Auxiliar = new obstaculo(ArregloMatrizAbstracta[fila][columna].PosRX,ArregloMatrizAbstracta[fila][columna].PosRY,145,145);
                    scene->addItem(Auxiliar);
                    Paredes.push_back(Auxiliar);
                }
                else if(fila==18 and columna==29){
                    obstaculo * Auxiliar = new obstaculo(ArregloMatrizAbstracta[fila][columna].PosRX,ArregloMatrizAbstracta[fila][columna].PosRY,95,95);
                    scene->addItem(Auxiliar);
                    Paredes.push_back(Auxiliar);
                }
            }
        }
    }
}

bool game::PisoConFriccion()
{
    // Busqueda exhaustiva y establece en cual de los puntos del mapa hay fricción.
    for(int fila=0;fila<24;fila++){
        for(int columna =0; columna<40; columna++){
            if(nivel==1){
                if(fila==4 and ((columna>=7 and columna<=11) or (columna>=15 and columna<=19) or (columna>=34 and columna <=39)))
                    ArregloMatrizAbstracta[fila][columna].PisoConFriccion=true;
                else if (fila==5 and ((columna>=8 and columna<=10) or (columna>=15 and columna<=17) or (columna>=36 and columna<=39)))
                    ArregloMatrizAbstracta[fila][columna].PisoConFriccion=true;
                else if(fila==6 and ((columna>=27 and columna<=31) or (columna>=35 and columna<=39)))
                    ArregloMatrizAbstracta[fila][columna].PisoConFriccion=true;
                else if(fila==7 and ((columna>=27 and columna<=31) or (columna>=33 and columna<=39)))
                    ArregloMatrizAbstracta[fila][columna].PisoConFriccion=true;
                else if(fila==8 and ((columna>=27 and columna<=31) or (columna>=33 and columna<=39)))
                    ArregloMatrizAbstracta[fila][columna].PisoConFriccion=true;
                else if(fila==9 and ((columna>=5 and columna<=7) or (columna==35)))
                    ArregloMatrizAbstracta[fila][columna].PisoConFriccion=true;
                else if(fila==10 and ((columna>=8 and columna<=9) or (columna==35)))
                    ArregloMatrizAbstracta[fila][columna].PisoConFriccion=true;
                else if(fila==11 and ((columna>=8 and columna<=9) or (columna==14) or (columna>=29 and columna<=30)))
                    ArregloMatrizAbstracta[fila][columna].PisoConFriccion=true;
                else if(fila==12 and ((columna>=3 and columna<=10) or (columna==14) or (columna==17) or (columna==18) or (columna>=28 and columna<=35) or (columna==39)))
                    ArregloMatrizAbstracta[fila][columna].PisoConFriccion=true;
                else if(fila==13 and ((columna>=6 and columna<=8) or (columna==13) or (columna==14) or (columna==17) or (columna==18) or (columna>=28 and columna<=35) or (columna==39)))
                    ArregloMatrizAbstracta[fila][columna].PisoConFriccion=true;
                else if(fila==14 and ((columna>=1 and columna<=2) or (columna==10) or (columna>=13 and columna==16) or (columna>=28 and columna <=39)))
                    ArregloMatrizAbstracta[fila][columna].PisoConFriccion=true;
                else if(fila==15 and ((columna>=1 and columna<=2) or (columna>=10 and columna==13) or (columna>=16 and columna <=19) or (columna>=36 and columna <=37)))
                    ArregloMatrizAbstracta[fila][columna].PisoConFriccion=true;
                else if(fila==16 and ((columna>=1 and columna<=3)))
                    ArregloMatrizAbstracta[fila][columna].PisoConFriccion=true;
                else if(fila==17 and ((columna>=37 and columna<=38)))
                    ArregloMatrizAbstracta[fila][columna].PisoConFriccion=true;
                else if(fila==18 and ((columna>=2 and columna<=6) or (columna>=14 and columna==15) or (columna==38)))
                    ArregloMatrizAbstracta[fila][columna].PisoConFriccion=true;
                else if(fila==19 and ((columna>=2 and columna<=5) or (columna>=13 and columna==15) or (columna==38)))
                    ArregloMatrizAbstracta[fila][columna].PisoConFriccion=true;
                else if(fila==20 and ((columna>=3 and columna<=5) or (columna>=11 and columna==16)))
                    ArregloMatrizAbstracta[fila][columna].PisoConFriccion=true;
                else if(fila==21 and ((columna>=12 and columna==16)))
                    ArregloMatrizAbstracta[fila][columna].PisoConFriccion=true;
                else if(fila==22 and ((columna>=13 and columna==17)))
                    ArregloMatrizAbstracta[fila][columna].PisoConFriccion=true;
                else if(fila==23 and ((columna>=14 and columna==19)))
                    ArregloMatrizAbstracta[fila][columna].PisoConFriccion=true;
            }
            else {
                if(fila==5 and columna==26)
                    ArregloMatrizAbstracta[fila][columna].PisoConFriccion=true;
                else if((fila>=7 and fila<=8) and columna==17)
                    ArregloMatrizAbstracta[fila][columna].PisoConFriccion=true;
                else if(fila==7 and columna == 24)
                    ArregloMatrizAbstracta[fila][columna].PisoConFriccion=true;
                else if(fila==10 and columna == 21)
                    ArregloMatrizAbstracta[fila][columna].PisoConFriccion=true;
                else if(fila==11 and columna == 27)
                    ArregloMatrizAbstracta[fila][columna].PisoConFriccion=true;
                else if(fila==13 and columna == 19)
                    ArregloMatrizAbstracta[fila][columna].PisoConFriccion=true;
                else if(fila==15 and ((columna>=4 and columna<=5) or columna==34))
                    ArregloMatrizAbstracta[fila][columna].PisoConFriccion=true;
                else if(fila==16 and columna == 11)
                    ArregloMatrizAbstracta[fila][columna].PisoConFriccion=true;
                else if(fila==16 and columna == 33)
                    ArregloMatrizAbstracta[fila][columna].PisoConFriccion=true;
                else if(fila==16 and columna == 35)
                    ArregloMatrizAbstracta[fila][columna].PisoConFriccion=true;
                else if(fila==18 and (columna>=24 and columna<=25))
                    ArregloMatrizAbstracta[fila][columna].PisoConFriccion=true;
                else if(fila==21 and (columna>=19 and columna<=20))
                    ArregloMatrizAbstracta[fila][columna].PisoConFriccion=true;
                else if(fila==22 and columna==6)
                    ArregloMatrizAbstracta[fila][columna].PisoConFriccion=true;
                else if(fila==22 and (columna>=23 and columna<=24))
                    ArregloMatrizAbstracta[fila][columna].PisoConFriccion=true;
                else if(fila==22 and columna==35)
                    ArregloMatrizAbstracta[fila][columna].PisoConFriccion=true;

            }

        }
    }
}

bool game::EstablecerPisoQuitaVida()
{
    // Busqueda exhaustiva y establece las zonas del mapa en las que el jugador recibe daño por el suelo.
    for(int fila=0;fila<24;fila++){
        for(int columna =0; columna<40; columna++){
            if(nivel==1){
                if(fila==23 and ((columna>=0 and columna<=13) or (columna>=24 and columna<=39)))
                    ArregloMatrizAbstracta[fila][columna].PisoHaceDano=true;
                else if (fila==22 and ((columna>=0 and columna<=12) or (columna>=24 and columna<=29) or (columna>=37 and columna<=39)))
                    ArregloMatrizAbstracta[fila][columna].PisoHaceDano=true;
                else if(fila==21 and ((columna>=0 and columna<=11) or (columna>=24 and columna<=27) or columna==38))
                    ArregloMatrizAbstracta[fila][columna].PisoHaceDano=true;
                else if(fila==20 and ((columna>=0 and columna<=2) or (columna>=6 and columna<=10) or (columna>=26 and columna<=27)))
                    ArregloMatrizAbstracta[fila][columna].PisoHaceDano=true;
                else if(fila==19 and ((columna>=0 and columna<=1) or (columna>=6 and columna<=9)))
                    ArregloMatrizAbstracta[fila][columna].PisoHaceDano=true;
                else if(fila==18 and ((columna>=0 and columna<=1) or (columna>=7 and columna<=9)))
                    ArregloMatrizAbstracta[fila][columna].PisoHaceDano=true;
                else if(fila==17 and ((columna>=0 and columna<=1) or (columna>=7 and columna<=8)))
                    ArregloMatrizAbstracta[fila][columna].PisoHaceDano=true;
                else if((fila==15 and columna== 25) or (fila==16 and columna==26))
                    ArregloMatrizAbstracta[fila][columna].PisoHaceDano=true;
            }
            else {
                if(fila==5 and ((columna>=0 and columna<=1) or (columna>=35 and columna<=37)))
                    ArregloMatrizAbstracta[fila][columna].PisoHaceDano=true;
                else if (fila==6 and ((columna>=0 and columna<=6) or (columna>=32 and columna<=39)))
                    ArregloMatrizAbstracta[fila][columna].PisoHaceDano=true;
                else if(fila==7 and ((columna>=0 and columna<=7) or (columna>=33 and columna<=39)))
                    ArregloMatrizAbstracta[fila][columna].PisoHaceDano=true;
                else if(fila==10 and (columna==0 or columna==39))
                    ArregloMatrizAbstracta[fila][columna].PisoHaceDano=true;
                else if(fila==11 and ((columna>=0 and columna<=2) or (columna>=37 and columna<=39)))
                    ArregloMatrizAbstracta[fila][columna].PisoHaceDano=true;
                else if(fila==12 and ((columna>=0 and columna<=5) or (columna>=32 and columna<=39)))
                    ArregloMatrizAbstracta[fila][columna].PisoHaceDano=true;
                else if(fila==13 and ((columna>=0 and columna<=7) or (columna>=32 and columna<=39)))
                    ArregloMatrizAbstracta[fila][columna].PisoHaceDano=true;
                else if(fila==14 and ((columna>=38 and columna<=39)))
                    ArregloMatrizAbstracta[fila][columna].PisoHaceDano=true;
                else if(fila==15 and columna==39)
                    ArregloMatrizAbstracta[fila][columna].PisoHaceDano=true;
                else if(fila==16 and columna==39)
                    ArregloMatrizAbstracta[fila][columna].PisoHaceDano=true;
                else if(fila==17 and (columna==0 or columna==1 or (columna>=5 and columna<=9) or (columna>=37 and columna<=39) ))
                    ArregloMatrizAbstracta[fila][columna].PisoHaceDano=true;
                else if(fila==18 and ( (columna>=0 and columna<=7) or (columna>=32 and columna<=39) ))
                    ArregloMatrizAbstracta[fila][columna].PisoHaceDano=true;
                else if(fila==19 and ( (columna>=0 and columna<=6) or (columna>=32 and columna<=39) ))
                    ArregloMatrizAbstracta[fila][columna].PisoHaceDano=true;
                else if(fila==20 and ( (columna>=0 and columna<=3) or (columna>=37 and columna<=39) ))
                    ArregloMatrizAbstracta[fila][columna].PisoHaceDano=true;
                else if(fila==21 and ( (columna>=0 and columna<=1)))
                    ArregloMatrizAbstracta[fila][columna].PisoHaceDano=true;
            }
        }
    }
}

void game::SetNumeroZombies(int Dificultad)
{
    // Establece el numero de zombies que salen por cada orda.
    NumeroZombies=Dificultad;
}

void game::follow_char()
{
    //view->centerOn(QPoint(player->x(),player->y()));
}

void game::PerdisteElJuego()
{
    // Se detienen todos los timers y muestra la interfaz de perder.
    InterfazPerder->show();
    OrdasZombies->stop();
    timer->stop();
    VerificarSiPasaNivel->stop();
    player->TecladoBloqueado=true;
    player->PonerTodoEnCero();
    music->stop();
}

void game::VerificarSiYaPasadeNivel()
{
    // Verifica si ya pasó de nivel o en su defecto ganó el juego.
    qDebug()<<Zombies.size()<<" "<<nivel<<" "<<Orda;
    if(Zombies.size()==0 and nivel==3 and Orda==2){
        InterfazGanar->show();
        player->TecladoBloqueado=true;
        player->PonerTodoEnCero();
        OrdasZombies->stop();
        timer->stop();
        VerificarSiPasaNivel->stop();
        player->TecladoBloqueado=true;
        player->PonerTodoEnCero();
        music->stop();
    }
    else if((Zombies.size()==0 and Orda==2)){
        *NivelRetornar+=1;
        InterfazPasarNivel->show();
         player->TecladoBloqueado=true;
         player->PonerTodoEnCero();
         OrdasZombies->stop();
         timer->stop();
         VerificarSiPasaNivel->stop();
         player->TecladoBloqueado=true;
         player->PonerTodoEnCero();
         music->stop();
    }
    //////////// aprovecha la siguiente función, llamada por un timer cada X milisegundos para actualizar la posición de la Healthbar
    hbar->setPos(player->x(),player->y()-20);
    hbar->setWidth(player->get_vida());
    scene->update();
    //hbar2->setPos(player_2->x(),player_2->y()-20);
    //hbar2->setWidth(player_2->get_vida());
    view->centerOn(player->x(),player->y());
}

void game::ContinuarJugando()
{
    // Inicializa nuevamente todos los timers.
    OrdasZombies->start(TiempoEntreOrdas);
    timer->start(20);
    VerificarSiPasaNivel->start(20);
    InterfazPausa->close();
    player->TecladoBloqueado=false;
    player->PonerTodoEnCero();
    music->play();
}

void game::InicializarCuadros()
{
    // Si se cambia de mapa tener cuidado si se cambia la cantidad de cuadros que hay.
    // Estable las posiciones en la escena de todos los nodos y determina si son intrasitables o no.
    int posy = 25;
    for(int fila =0;fila <24;fila++){
        int posx=25;
        for(int columna=0;columna<40;columna++){
            ArregloMatrizAbstracta[fila][columna].visitado=false;
            ArregloMatrizAbstracta[fila][columna].PosRX=posx;
            ArregloMatrizAbstracta[fila][columna].PosRY=posy;
            ArregloMatrizAbstracta[fila][columna].distancia=99999999;
            if(CrearObstaculosMapa(fila,columna)==true){
                ArregloMatrizAbstracta[fila][columna].transitable=false;
            }
            else {
                ArregloMatrizAbstracta[fila][columna].transitable=true;
            }
            posx+=50;
        }
        posy+=50;
    }
}

void game::EstablecerZombies(float PosicionInicialX, float PosicionInicialY)
{
    // Esta funcion crea un zombie, lo pone en la posicion (PosicionInicialX, PosicionInicialY) y lo agrega a la lista de enemigos.
    enemy * aux = new enemy ();
    aux->posx=PosicionInicialX;
    aux->posy=PosicionInicialY;
    CaracteristicasZombiesPorNivelYOrda(aux);
    scene->addItem(aux);
    Zombies.push_back(aux);
}

void game::NodosIniciales()
{
    // Si se cambia de mapa tener cuidado si se cambia la cantidad de cuadros que hay.
    // Esta funcion determina en cual de todos los nodos del mapa se encuentra el personaje y establece ese nodo como el inicial.
    for(int fila =0;fila <24;fila++){
        for(int columna=0;columna<40;columna++){
            if(ArregloMatrizAbstracta[fila][columna].PuntoEstaAqui(player->x()+player->pixmap().width()/2,player->y()+player->pixmap().height()/4)){
                ArregloMatrizAbstracta[fila][columna].distancia=0;
                ArregloMatrizAbstracta[fila][columna].visitado=true;
                NIX=fila;
                NIY=columna;
                if(ArregloMatrizAbstracta[fila][columna].PisoHaceDano==true)
                {
                    player->RestarVida(3);
                }
                if(ArregloMatrizAbstracta[fila][columna].PisoConFriccion==true)
                {
                    player->Vx=player->Vx/1.3;
                    player->Vy=player->Vy/1.3;
                }
                return;
            }
        }
    }
}

void game::EstablecerTodosLosNodosComoNoVisitados()
{
    // Establece todos los nodos de la matiz como no visitados.
    // Lo cual es muy importante para el algoritmo de generacion del campo vectorial.
    for(int fila =0;fila <24;fila++){
        for(int columna=0;columna<40;columna++){
            ArregloMatrizAbstracta[fila][columna].visitado=false;
        }
    }
}

bool game::HayAlgunVecinoIntrasitable(list<nodo *> Vecinitos)
{
    // Cada nodo tiene la informacion de sus vecinos (Las ocho direcciones - N ,S ,E ,O, NO, NE, SO, SE ), si uno de estos vecinos es intransitable
    // La funcion devuelve verdadero.
    for(auto i:Vecinitos){
        if(i->transitable==false)
            return true;
    }
    return false;
}

bool game::CorresPondeAlgunVecinoEsquinero(int VecinoX, int VecinoY, int OriginalX, int OriginalY)
{
    // Esta funcion verifica se las posisicones ingresadas del vecino corresponden a la de un vecino esquinero...
    // Es decir, un vecino que esté al NO, NE, SO, SE del nodo actual (Original).
    if(VecinoX==OriginalX+50 and VecinoY==OriginalY+50)
        return true;
    else if(VecinoX==OriginalX-50 and VecinoY==OriginalY-50)
        return true;
    else if (VecinoX==OriginalX+50 and VecinoY==OriginalY-50)
        return true;
    else if(VecinoX==OriginalX-50 and VecinoY==OriginalY+50)
        return true;
    else
        return false;
}

void game::LiberarOrdasZombies()
{
    // Esta funcion Despliega los zombies dada la posicion de un determinado nodo.
    // Esta funcion en realidad va a ser un slot. Cada determinado segundo va a liberar una nueva orda de zombies.
    ContadorNumeroMaximoZombies+=NumeroZombies;
    if(Orda==1){
        if(ContadorNumeroMaximoZombies>=60){
            if(Zombies.size()==0){
                Orda++;
                SetZombiesPorOrda();
                ContadorNumeroMaximoZombies=0;
            }
            return;
        }
    }
    else if(Orda==2){
        if(ContadorNumeroMaximoZombies>=90){
            if(Zombies.size()==0){
                Orda++;
                SetZombiesPorOrda();
                ContadorNumeroMaximoZombies=0;
            }
            return;
        }
    }
    else if(Orda==3){
        if(ContadorNumeroMaximoZombies>=120){
            return;
        }
    }

    srand(time(NULL));
    if(nivel==1){
        vector <int> ColumnasDespliegue1={5,12,13,14,20,19,18,24,25,26,33};
        vector <int> FilasDespliegue1={15,14,13,12};
        vector <int> FilasDespliegue2={14,13,12,11,10,9,8};
        for(int contadorZombies=0;contadorZombies<(NumeroZombies*2)/3;contadorZombies++){
            int ColumnaAleatoria= rand()% 9 ;
            EstablecerZombies(ArregloMatrizAbstracta[3][ColumnasDespliegue1[ColumnaAleatoria]].PosRX-23,ArregloMatrizAbstracta[3][ColumnasDespliegue1[ColumnaAleatoria]].PosRY-23);
        }
        for(int contadorZombies=0; contadorZombies<(NumeroZombies)/6;contadorZombies++){
            int FilaAleatoria = rand()% 3;
            EstablecerZombies(ArregloMatrizAbstracta[FilasDespliegue1[FilaAleatoria]][0].PosRX-23,ArregloMatrizAbstracta[FilasDespliegue1[FilaAleatoria]][0].PosRY-23);
        }
        for(int contadorZombies=0; contadorZombies<(NumeroZombies)/6;contadorZombies++){
            int FilaAleatoria=rand()% 7;
            EstablecerZombies(ArregloMatrizAbstracta[FilasDespliegue2[FilaAleatoria]][39].PosRX-23,ArregloMatrizAbstracta[FilasDespliegue2[FilaAleatoria]][39].PosRY-23);
        }
    }
    else {
        vector <int> ColumnasDespliegue1={12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29};
        for(int contadorZombies=0;contadorZombies<(NumeroZombies);contadorZombies++){
            int ColumnaAleatoria= rand()% 17 ;
            EstablecerZombies(ArregloMatrizAbstracta[22][ColumnasDespliegue1[ColumnaAleatoria]].PosRX-23,ArregloMatrizAbstracta[22][ColumnasDespliegue1[ColumnaAleatoria]].PosRY-23);
        }
        for(int contadorZombies=0;contadorZombies<(NumeroZombies/2);contadorZombies++){
            int ColumnaAleatoria= rand()% 17 ;
            EstablecerZombies(ArregloMatrizAbstracta[1][ColumnasDespliegue1[ColumnaAleatoria]].PosRX-23,ArregloMatrizAbstracta[1][ColumnasDespliegue1[ColumnaAleatoria]].PosRY-23);
        }
    }

}

bool game::CrearObstaculosMapa(int fila, int columna)
{
    // Esta funcion es para crear de una manera rapida todos los obstaculos que hayan en el mapa
    // De acuerdo a una determinadas condiciones.
    if(nivel==1){
        if((fila>=3 and fila <= 5) and (columna ==0 or columna == 1))
            return true;
        else if( fila == 5 and (columna==2 or columna==3))
            return true;
        else if(fila == 6 and ((columna>=15 and columna <= 17) or (columna>=28 and columna<=30) or (columna>=35 and columna<=37)))
            return true;
        else if(fila == 7 and ((columna>=15 and columna <= 17) or (columna>=22 and columna<=23) or (columna>=32 and columna<=33)))
            return true;
        else if(fila == 8 and ((columna>=25 and columna <= 26) or (columna>=32 and columna<=33)))
            return true;
        else if(fila == 9 and (columna>=31 and columna<=34))
            return true;
        else if(fila == 10  and ((columna>=5 and columna<=7) or (columna>=31 and columna<=34)))
            return true;
        else if(fila == 11  and ((columna>=5 and columna<=7) or (columna>=15 and columna<=16) or (columna>=31 and columna<=34)))
            return true;
        else if(fila == 12  and ((columna>=11 and columna<=12) or (columna>=15 and columna<=16)))
            return true;
        else if(fila == 13  and ((columna>=11 and columna<=12) or (columna>=22 and columna<=23) or (columna>=30 and columna<=31)))
            return true;
        else if(fila == 14  and ((columna>=11 and columna<=12) or (columna>=17 and columna<=18) or (columna>=22 and columna<=23)))
            return true;
        else if(fila == 15  and ( columna==38 or columna == 39))
            return true;
        else if(fila == 16  and ((columna>=32 and columna<=33) or (columna>=37 and columna<=38)))
            return true;
        else if(fila == 17  and (columna == 2 or columna==3 or columna == 32 or columna == 33))
            return true;
        else if(fila == 18  and (columna == 26 or columna==27))
            return true;
        else if(fila == 19  and (columna == 10 or columna==11 or columna == 20 or columna==19 or columna== 18 or columna==26 or columna == 27))
            return true;
        else if(fila == 20  and ( columna == 20 or columna==19 or columna== 18))
            return true;
        else
            return false;
    }
    else {
        if((fila>=1 and fila <= 2) and (columna ==0 or columna == 1))
            return true;
        else if( (fila>=4 and fila <= 5) and (columna==24 or columna==25))
            return true;
        else if((fila>=6 and fila <= 7) and ((columna>=13 and columna <= 14)))
            return true;
        else if(fila == 6 and ((columna>=17 and columna <= 19) or (columna>=24 and columna <= 25)))
            return true;
        else if(fila == 8 and ((columna>=33 and columna <= 36)))
            return true;
        else if(fila == 9 and (columna==17 or (columna>=21 and columna<=27) or columna==38 or columna==39))
            return true;
        else if(fila == 10  and ((columna>=26 and columna<= 27)))
            return true;
        else if(fila == 12  and ((columna>=17 and columna<=20) or columna==25))
            return true;
        else if((fila>=13 and fila <= 14)  and columna== 7)
            return true;
        else if((fila>=14 and fila <= 15)  and columna== 31)
            return true;
        else if((fila>=18 and fila <= 19)  and (columna>=29 and columna<=30))
            return true;
        else if((fila>=20 and fila <= 21) and ( columna>=2 and columna<=4))
            return true;
        else if((fila>=20 and fila <= 23) and ( columna>=36 and columna<=39))
            return true;
        else
            return false;
    }
}

void game::CaracteristicasZombiesPorNivelYOrda(enemy * actual)
{
    // Dependiendo del nivel y orda en el que se encuentre el personaje los zombies van a tener ciertas caracteristicas.
    if(nivel==1){
        if(Orda==1){
            actual->Dano=1;
            actual->Masa=80;
            actual->VelocidadMaxima=30;
            actual->reduccion=30;
        }
        else if (Orda==2) {
            actual->Dano=2;
            actual->Masa=70;
            actual->VelocidadMaxima=40;
            actual->reduccion=25;
        }
        else if (Orda==3) {
            actual->Dano=3;
            actual->Masa=60;
            actual->VelocidadMaxima=50;
            actual->reduccion=20;
        }
    }
    else {
        if(Orda==1){
            actual->Dano=3;
            actual->Masa=100;
            actual->VelocidadMaxima=50;
            actual->reduccion=25;
        }
        else if (Orda==2) {
            actual->Dano=4;
            actual->Masa=90;
            actual->VelocidadMaxima=55;
            actual->reduccion=20;
        }
        else if (Orda==3) {
            actual->Dano=5;
            actual->Masa=80;
            actual->VelocidadMaxima=60;
            actual->reduccion=15;
        }
    }
}

void game::PausarTodoJuego()
{
    // Detiene todos los timers
    OrdasZombies->stop();
    timer->stop();
    VerificarSiPasaNivel->stop();
    music->stop();
    InterfazPausa->show();

}

void game::ActualizarCamporVectorial()
{
    // Cada vez que el jugador se desplaza es necesario recalcular todo el campo vectorial.
    // Cada vez que se presiona una tecla para mover el personaje se emite una señal que activa ese slot.
    // Y actualiza el campo vectorial.
    EstablecerTodosLosNodosComoNoVisitados();
    NodosIniciales();
    CrearMapaDeCalor(&ArregloMatrizAbstracta[NIX][NIY],frontera);
    ConstruccionCampoVectorial();
    ArregloMatrizAbstracta[NIX][NIY].Direccion.x=0;
    ArregloMatrizAbstracta[NIX][NIY].Direccion.y=0;
}

void game::EstablecerVecinos()
{
    //Esta funcion itera sobre todos los nodos, determina cuales son los nodos vecinos de cada uno y los guarda.
    // Si se cambia de mapa tener cuidado si se cambia la cantidad de cuadros que hay.
    for (int fila=0;fila<24;fila++) {
        for (int columna =0;columna<40;columna++) {
            if(fila-1>=0 and columna -1 >=0)
                ArregloMatrizAbstracta[fila][columna].vecinos.push_front( &ArregloMatrizAbstracta[fila-1][columna-1]);
            if(fila+1 < 24 and columna + 1 < 40)
                ArregloMatrizAbstracta[fila][columna].vecinos.push_front( &ArregloMatrizAbstracta[fila+1][columna+1]);
            if(fila+1 < 24 and columna -1 >= 0)
                ArregloMatrizAbstracta[fila][columna].vecinos.push_front( &ArregloMatrizAbstracta[fila+1][columna-1]);
            if(fila-1 >=0 and columna +1 < 40)
                ArregloMatrizAbstracta[fila][columna].vecinos.push_front( &ArregloMatrizAbstracta[fila-1][columna+1]);
            if(fila-1>=0){
                ArregloMatrizAbstracta[fila][columna].vecinos.push_front( &ArregloMatrizAbstracta[fila-1][columna]);
            }
            if (fila +1 < 24) {
                ArregloMatrizAbstracta[fila][columna].vecinos.push_front( &ArregloMatrizAbstracta[fila+1][columna]);
            }
            if (columna-1>=0) {
                ArregloMatrizAbstracta[fila][columna].vecinos.push_front( &ArregloMatrizAbstracta[fila][columna-1]);
            }
            if (columna+1<40) {
                ArregloMatrizAbstracta[fila][columna].vecinos.push_front( &ArregloMatrizAbstracta[fila][columna+1]);
            }
        }
    }
}

void game::CrearMapaDeCalor(nodo * Inicial, queue <nodo *> frontera)
{
    // Esta funcion crea el mapa de calor.
    //Mapa de calor: Es el mapa que se genera al establecerle a cada nodo su distancia de él al nodo inicial (Nodo en el que se encuentra el personaje.)
    // Funcion recursiva.
    if(Inicial->transitable==true){ // Se verifica si el nodo inicial es transitable. Si no lo es, se debe ignorar.
        list <nodo *> VecinosActuales= Inicial->vecinos;
        for(auto i: VecinosActuales){ // Se itera sobre los vecinos que tenga el nodo inical.
            if(i->visitado==false ){ // El nodo vecino i no debe estar visitadao por el algoritmo y debe ser transitable para ser agregado a la frontera.
                i->distancia=Inicial->distancia+1; // La distancia es la distancia que tendrá el nodo vecino i va a ser la distancia de el nodo anterior (original) mas 1.
                i->visitado=true; // El nodo vecino i se marca como visitado.
                frontera.push(i); // Se agrega a la cola.
            }
        }
    }
    if(frontera.empty())
        return;
    nodo * Nodo = frontera.front(); // Se extrae el nodo que esté en la primera posicion de la cola.
    frontera.pop();   // Luego se elimina de la cola.
    CrearMapaDeCalor(Nodo,frontera);

}

void game::CalcularAceleracionZombie()
{
    // Esta funcion itera sobre todos los zombies que estén en el mapa, determina en cual de los nodos se encuentra cada uno
    // y iguala el direccion que tiene un nodo a la veclocidad del zombie y depues multiplica por un escalar a dicha velocidad.
    // Esto ultimo devido a que la magnitud del vector director de cada nodo es 1.
    // Si se cambia de mapa tener cuidado si se cambia la cantidad de cuadros que hay.
    for (int iterador=0;iterador<Zombies.size();iterador++) {
        for (int fila =0 ;fila<24;fila++) {
            for (int columna =0;columna<40;columna++) {
                if(ArregloMatrizAbstracta[fila][columna].PuntoEstaAqui(Zombies.at(iterador)->posx+23,Zombies.at(iterador)->posy+23)==true)
                {
                    float Distancia=pow(pow(Zombies.at(iterador)->posx-player->x(),2)+pow(Zombies.at(iterador)->posy-player->y(),2),0.5);
                       Zombies.at(iterador)->velocidad.x=ArregloMatrizAbstracta[fila][columna].Direccion.x;
                       Zombies.at(iterador)->velocidad.y=ArregloMatrizAbstracta[fila][columna].Direccion.y;
                       if(Zombies.at(iterador)->velocidad.x==0 and Zombies.at(iterador)->velocidad.y==0 and Distancia<100 and Zombies.at(iterador)->SePuedeAtacar==true)
                       {
                           player->RestarVida(Zombies.at(iterador)->Dano);
                            Zombies.at(iterador)->SePuedeAtacar=false;
                       }

                       Zombies.at(iterador)->velocidad.MultiplicarEscalar(Zombies.at(iterador)->VelocidadMaxima);
                }
        }
    }
  }
}

void game::ConstruccionCampoVectorial()
{
    // Esta funcion verifica los vecinos de cada nodo y determina cuales de esos vecinos tiene una menor distacio al nodo inicial.
    // Posterior a esto, se crea el vector apuntando hacia ese nodo que tiene una menor distancia al nodo inicial.
    // Si se cambia de mapa tener cuidado si se cambia la cantidad de cuadros que hay.
    for(int fila =0;fila<24;fila++){
        for(int columna =0; columna <40;columna++){
            int MinDistancia=99999999;
            nodo * Auxiliar;
            if(HayAlgunVecinoIntrasitable(ArregloMatrizAbstracta[fila][columna].vecinos)==true){ // Se verifica si el nodo actual ArregloMatrizAbstracta[fila][columna] tiene algun vecino intransitable.
                for(auto menor: ArregloMatrizAbstracta[fila][columna].vecinos){  // Se itera sobre los vecinos del nodo actual.
                    if(CorresPondeAlgunVecinoEsquinero(menor->PosRX,menor->PosRY,ArregloMatrizAbstracta[fila][columna].PosRX,ArregloMatrizAbstracta[fila][columna].PosRY)==false){
                        if(menor->transitable==false)     // Se verifica si el vecino actual es esquinero. Si no lo es, entra y se verifica su distancia respecto al nodo actual.
                            continue;
                        if(menor->distancia<MinDistancia){ // Si la distancia es menor que MinDistancia Auxiliar toma el valor de ese vecino y MinDistancia toma el valor de la distancia de ese nodo.
                            MinDistancia=menor->distancia;
                            Auxiliar=menor;
                        }                                  // De este modo garantizamos que la comparacion solo se haga entre los nodos no esquineros.
                    }
                }
            }
            else {  // Si no hay ningun nodo intransitable. No tiene sentido preguntar si un vecino es intransitable.
                // Se itera sobre todos los 8 vecinos. Para verificar cual es el de menor distancia.
                // Ese vecino de menor distancia va a ser igualado a auxliar.
                for(auto menor: ArregloMatrizAbstracta[fila][columna].vecinos){
                    if(menor->distancia<MinDistancia){
                        MinDistancia=menor->distancia;
                        Auxiliar=menor;
                    }
            }
        }
            // Una vez se encuentre el nodo de menor distancia se va a igualar a auxiliar y posteriormente se calcula el vector que tendrá el nodo ArregloMatrizAbstracta[fila][columna].
            // Luego ese nodo ser normaliza.
            ArregloMatrizAbstracta[fila][columna].Direccion.x=Auxiliar->PosRX-ArregloMatrizAbstracta[fila][columna].PosRX;
            ArregloMatrizAbstracta[fila][columna].Direccion.y=Auxiliar->PosRY-ArregloMatrizAbstracta[fila][columna].PosRY;
            ArregloMatrizAbstracta[fila][columna].Direccion.Normalizar();
    }
  }
}

void game::ActualizarPosicionZombies()
{
    // Se actualiza la posicion de los zombies con velocidad.
    // Si bien no utilizamos explicitamente la aceleracion cabe recalcar que es un sistema fisico acelerado debido
    // A que hay un cambio de velocidad.

    for(int i= 0; i<Zombies.size();i++){
        Zombies.at(i)->posx=Zombies.at(i)->posx + Zombies.at(i)->velocidad.x*t;
        Zombies.at(i)->posy=Zombies.at(i)->posy + Zombies.at(i)->velocidad.y*t;
        Zombies.at(i)->setPos(Zombies.at(i)->posx,Zombies.at(i)->posy);
    }
}


void game::ActualizarZombies()
{
    // Esta funcion primero actualiza la velocidad del zombie y después modifica ala posición del zombie de acuerdo a esta velocidad.
    CalcularAceleracionZombie();
    ActualizarPosicionZombies();
}
