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

game::game(QWidget *parent)
{
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
    view->setBackgroundBrush(QBrush(QImage(":/BGI/bg1.png")));
    //view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    view->setFixedSize(800,600);

    player->setPos(0,0);

    view->show();
    SetNumeroZombies(10);
    EstablecerZombies();
    InicializarCuadros();
    EstablecerVecinos();
    NodosIniciales();
    CrearMapaDeCalor(&ArregloMatrizAbstracta[NIX][NIY],frontera);
    ConstruccionCampoVectorial();
    ArregloMatrizAbstracta[NIX][NIY].Direccion.x=0;
    ArregloMatrizAbstracta[NIX][NIY].Direccion.y=0;
    connect(player,&player1::buttonPressed,this,&game::ActualizarCamporVectorial);
    QTimer * timer = new QTimer;
    connect(timer, &QTimer::timeout,this,&game::ActualizarZombies);
    timer->start(20);
    //spawn enemies
//    srand(time(NULL));
//    QObject::connect(timer,SIGNAL(timeout()),player,SLOT(spawn()));
//    timer->start(2000);
}

void game::SetNumeroZombies(int Dificultad)
{
    NumeroZombies=Dificultad;
}

void game::follow_char()
{
    //view->centerOn(QPoint(player->x(),player->y()));
}

void game::InicializarCuadros()
{
    // Si se cambia de mapa tener cuidado si se cambia la cantidad de cuadros que hay.
    int posy = 25;
    for(int fila =0;fila <24;fila++){
        int posx=25;
        for(int columna=0;columna<40;columna++){
            ArregloMatrizAbstracta[fila][columna].visitado=false;
            ArregloMatrizAbstracta[fila][columna].transitable=true;
            ArregloMatrizAbstracta[fila][columna].PosRX=posx;
            ArregloMatrizAbstracta[fila][columna].PosRY=posy;
            //qDebug()<<fila<<" "<<columna<<" "<<ArregloMatrizAbstracta[fila][columna].PosRX<<" "<<ArregloMatrizAbstracta[fila][columna].PosRY;
            posx+=50;
        }
        posy+=50;
    }
}

void game::EstablecerZombies()
{
    QPen BlackPen(Qt::black);
    QBrush RedBrush(Qt::yellow);
    for(int iterador=0;iterador<NumeroZombies;iterador++){
        enemy * aux = new enemy ();
        aux->setBrush(RedBrush);
        aux->setPen(BlackPen);
        scene->addItem(aux);
        Zombies.push_back(aux);
    }
}

void game::NodosIniciales()
{
    // Si se cambia de mapa tener cuidado si se cambia la cantidad de cuadros que hay.
    for(int fila =0;fila <24;fila++){
        for(int columna=0;columna<40;columna++){
            if(ArregloMatrizAbstracta[fila][columna].PuntoEstaAqui(player->x()+player->pixmap().width()/2,player->y()+player->pixmap().height()/4)){
                //qDebug()<<rect->x()<<" "<<rect->y();
                ArregloMatrizAbstracta[fila][columna].distancia=0;
                ArregloMatrizAbstracta[fila][columna].visitado=true;
                NIX=fila;
                NIY=columna;
                return;
            }
        }
    }
}

void game::EstablecerTodosLosNodosComoNoVisitados()
{
    for(int fila =0;fila <24;fila++){
        for(int columna=0;columna<40;columna++){
            ArregloMatrizAbstracta[fila][columna].visitado=false;
        }
    }
}


void game::ActualizarCamporVectorial()
{
    EstablecerTodosLosNodosComoNoVisitados();
    NodosIniciales();
    CrearMapaDeCalor(&ArregloMatrizAbstracta[NIX][NIY],frontera);
    ConstruccionCampoVectorial();
    ArregloMatrizAbstracta[NIX][NIY].Direccion.x=0;
    ArregloMatrizAbstracta[NIX][NIY].Direccion.y=0;
//        qDebug()<<"XXXXXXXXXXXXXXXXXXXXXX";
//        for(int fila =0; fila<24;fila++){
//            for(int columna=0;columna<40;columna++){
//                //qDebug()<<ArregloMatrizAbstracta[fila][columna].distancia;
//                qDebug()<<ArregloMatrizAbstracta[fila][columna].Direccion.x<<" "<<ArregloMatrizAbstracta[fila][columna].Direccion.y<<" ";
//            }
//            qDebug()<<"\n";
//        }
}

void game::EstablecerVecinos()
{
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

    // Falta agregar intransitable.
    // Preguntar si es transitable, si es true hacer lo que ya está de lo contrario distancia = 999999
    // Si es intransitable debería agregarlo a la fontera?
    list <nodo *> VecinosActuales= Inicial->vecinos;
    for(auto i: VecinosActuales){
        if(i->visitado==false){
            i->distancia=Inicial->distancia+1;
            i->visitado=true;
            frontera.push(i);
        }
    }
    if(frontera.empty())
        return;
    nodo * Nodo = frontera.front();
    frontera.pop();
    CrearMapaDeCalor(Nodo,frontera);

}

void game::CalcularAceleracionZombie()
{
    // Si se cambia de mapa tener cuidado si se cambia la cantidad de cuadros que hay.
    for (int iterador=0;iterador<Zombies.size();iterador++) {
        for (int fila =0 ;fila<24;fila++) {
            for (int columna =0;columna<40;columna++) {
                if(ArregloMatrizAbstracta[fila][columna].PuntoEstaAqui(Zombies.at(iterador)->posx,Zombies.at(iterador)->posy)==true)
                {

                       Zombies.at(iterador)->velocidad.x=ArregloMatrizAbstracta[fila][columna].Direccion.x;
                       Zombies.at(iterador)->velocidad.y=ArregloMatrizAbstracta[fila][columna].Direccion.y;
                       Zombies.at(iterador)->velocidad.MultiplicarEscalar(30);
                }
            }
        }
    }
}

void game::ConstruccionCampoVectorial()
{
    // Si se cambia de mapa tener cuidado si se cambia la cantidad de cuadros que hay.
    int contador;
    for(int fila =0;fila<24;fila++){
        for(int columna =0; columna <40;columna++){
            int MinDistancia=99999999;
            nodo * Auxiliar;
            contador=0;
            for(auto menor: ArregloMatrizAbstracta[fila][columna].vecinos){
                if(menor->transitable==false)
                    continue;
                if(menor->distancia<MinDistancia){
                    MinDistancia=menor->distancia;
                    Auxiliar=menor;
                    contador++;
                }
            }
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
//        if(i==0)
//            qDebug()<<Zombies.at(i)->posx<<" "<<Zombies.at(i)->posy;
    }
}


void game::ActualizarZombies()
{
    CalcularAceleracionZombie();
    ActualizarPosicionZombies();
}
