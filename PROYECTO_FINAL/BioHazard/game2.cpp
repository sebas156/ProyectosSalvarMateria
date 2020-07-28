#include "game2.h"
#include <QGraphicsScene>
#include "spaceship.h"
#include <QGraphicsView>
#include <QTimer>
#include <QObject>
#include <QGraphicsTextItem>
#include <QMediaPlayer>
#include <QMovie>
#include <QLabel>


game2::game2(QWidget *parent)
{
    srand(time(NULL));

    //Create a Scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,600);
    setScene(scene);
    //scene->setBackgroundBrush(Qt::black);

    //set movie
    //QGraphicsScene scene2;
    QLabel *gif_anim = new QLabel();
    QMovie *movie = new QMovie(":/2D/city.gif");
    gif_anim->setMovie(movie);
    movie->start();
    //QGraphicsProxyWidget *proxy = scene->addWidget(gif_anim);
    scene->addWidget(gif_anim);
    gif_anim->setFixedSize(800,600);
    gif_anim->setScaledContents(true);

    //Create an Item to put into the scene
    ship = new spaceship();

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


    //create the score/Health
    score = new Score();
    scene->addItem(score);
    health = new Health();
    health->setPos(health->x(),health->y()+25);
    scene->addItem(health);


    //Spawn enemies
    QTimer * timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()),ship,SLOT(spawn()));
    timer->start(1000);

    //play background music
    QMediaPlayer * music = new QMediaPlayer;
    music->setMedia(QUrl("qrc:/2D/track1.mp3"));
    music->setVolume(10);
    music->play();

    view->show();
}
