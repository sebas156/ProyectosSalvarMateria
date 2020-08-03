#include "mostrarranking.h"
#include "ui_mostrarranking.h"

mostrarranking::mostrarranking(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mostrarranking)
{
    ui->setupUi(this);
}

mostrarranking::~mostrarranking()
{
    delete ui;
}
