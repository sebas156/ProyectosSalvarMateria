#include "controles.h"
#include "ui_controles.h"

controles::controles(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::controles)
{
    ui->setupUi(this);
    scene= new QGraphicsScene(this);
    scene->setSceneRect(0,0,1280,700);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setBackgroundBrush(QBrush(QImage(":/BGI/controles.jpeg")));
    this->resize(1280,700);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
}

controles::~controles()
{
    delete ui;
}

void controles::on_volver_clicked()
{
    emit buttonClicked();
}
