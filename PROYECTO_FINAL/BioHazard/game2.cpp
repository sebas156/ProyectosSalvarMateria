#include "game2.h"
#include <QGraphicsScene>
#include "spaceship.h"
#include <QGraphicsView>
#include <QTimer>
#include <QObject>
#include <QGraphicsTextItem>
#include <QMediaPlayer>
#include <QMovie>
#include "healthbar.h"


game2::game2(int *ApuntadorNivelSeleccionado,string NombreUsuario,QWidget *parent)
{
    srand(time(NULL));
    NivelRetornar=ApuntadorNivelSeleccionado;

    // Estableciendo Nombre de ususario que inicio sesión.
    NickNameUsuario=QString::fromStdString(NombreUsuario);

    // Estableciendo interfaces.
    InterfazPausar=new pausar(NickNameUsuario);
    InterfazPerder= new perder();
    InterfazPasarNivel= new PasarNivel();


    //Estableciendo las conexiones de las interfaces.
    connect(InterfazPausar,&pausar::buttonClicked,this,&game2::QuierenContinuar);

    //Create a Scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,600);
    setScene(scene);
    //scene->setBackgroundBrush(Qt::black);

    //set movie
    //QGraphicsScene scene2;
    gif_anim = new QLabel();
    movie = new QMovie(":/2D/city.gif");
    gif_anim->setMovie(movie);
    movie->start();


    //QGraphicsProxyWidget *proxy = scene->addWidget(gif_anim);
    scene->addWidget(gif_anim);
    gif_anim->setFixedSize(800,600);
    gif_anim->setScaledContents(true);


    //Create an Item to put into the scene
    ship = new spaceship();
    connect(ship,&spaceship::buttonClicked,this,&game2::QuierenPausar);

    //add the item to the scene
    scene->addItem(ship);

    //make rect focusable
    ship->setFlag(QGraphicsItem::ItemIsFocusable);
    ship->setFocus();


    ship->setPos(20,0);

    //add view
    view = new QGraphicsView(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedSize(800,600);
    //view->setBackgroundBrush(Qt::black);


    //create the score/Health and add them to scene
    score = new Score();
    scene->addItem(score);
    bar = new healthbar(100);
    scene->addItem(bar);
    bar->setZValue(5);
    bar->setPos(0,0);
    scene->update();
    score->setPos(0,10);


    //Spawn enemies
    timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()),ship,SLOT(spawn()));
    timer->start(1000);

    //Pasar de nivel.
    // Apenas se acabe este timer se considera que el jugador pasó de nivel.
    // Muy importante recordar en que milisegundo iba cunado se ponga pausa.
    TiempoParaAguantar=new QTimer();
    connect(TiempoParaAguantar,&QTimer::timeout,this,&game2::PasarDeNivel);
    TiempoParaAguantar->start(90000);

    //Timer que verifica si perdió
    TimerPerdiste=new QTimer();
    connect(TimerPerdiste,&QTimer::timeout,this,&game2::VerificarSiPerdio);
    TimerPerdiste->start(5);

    //play background music
    music = new QMediaPlayer;
    music->setMedia(QUrl("qrc:/2D/track1.mp3"));
    music->setVolume(10);
    music->play();

    //add foreground
    view->setForegroundBrush(QBrush(QImage(":/BGI/fscreen.png")));

    view->show();
}

game2::~game2()
{
    delete TimerPerdiste;
    delete TiempoParaAguantar;
    delete gif_anim;
    delete view;
    delete ship;
    delete score;
    delete bar;
    delete movie;
    delete timer;
    delete InterfazPausar;
    delete InterfazPerder;
    delete InterfazPasarNivel;
    delete music;
    delete scene;
}

void game2::QuierenPausar()
{
    // Pausa todos los timers.
    ship->PausarTodosLosTimers();
    TiempoRestantePasarNivel=TiempoParaAguantar->remainingTime(); // Retorna el tiempo que le falta al timer para terminar.
    TiempoParaAguantar->stop();
    TimerPerdiste->stop();
    movie->stop();
    music->stop();
    timer->stop();
    ship->PausarTodosLosTimers();
    InterfazPausar->show();
}

void game2::QuierenContinuar()
{
    // Reinicia todos los timers.
    TiempoParaAguantar->start(TiempoRestantePasarNivel); // Retorna el timer desde donde había quedado.
    movie->start();
    music->play();
    timer->start(1000);
    TimerPerdiste->start(5);
    ship->ReactivarTodosLosTimers();
    InterfazPausar->close();
}

void game2::VerificarSiPerdio()
{
    if(ship->get_health()<=2){
        TiempoParaAguantar->stop();
        movie->stop();
        timer->stop();
        ship->PausarTodosLosTimers();
        InterfazPerder->show();
    }
}

void game2::PasarDeNivel()
{
    *NivelRetornar+=1;
    TiempoParaAguantar->stop();
    movie->stop();
    timer->stop();
    ship->PausarTodosLosTimers();
    InterfazPasarNivel->show();
}
