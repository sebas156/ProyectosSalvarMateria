#include "iniciosesion.h"
#include "ui_iniciosesion.h"

InicioSesion::InicioSesion(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InicioSesion)
{
    ui->setupUi(this);
}

InicioSesion::~InicioSesion()
{
    delete ui;
}

void InicioSesion::on_login_clicked()
{

}
