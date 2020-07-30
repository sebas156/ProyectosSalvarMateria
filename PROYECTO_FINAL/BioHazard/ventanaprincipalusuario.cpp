#include "ventanaprincipalusuario.h"
#include "ui_ventanaprincipalusuario.h"

VentanaPrincipalUsuario::VentanaPrincipalUsuario(int nivel, int puntos, string NombreUsuario,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VentanaPrincipalUsuario)
{
    NivelActual=nivel;
    ui->setupUi(this);
    NickName = QString::fromStdString(NombreUsuario);
    ui->NombreUsuario->setText(NickName);
}

VentanaPrincipalUsuario::~VentanaPrincipalUsuario()
{
    delete ui;
}

void VentanaPrincipalUsuario::on_Campana_clicked()
{
    this->close();
    SeleccionarNivel *SelccionarNivelUsuario = new SeleccionarNivel(NivelActual,NickName.toStdString());
    connect(SelccionarNivelUsuario,&SeleccionarNivel::buttonClicked,this,&VentanaPrincipalUsuario::Aparecer);
    SelccionarNivelUsuario->show();
}

void VentanaPrincipalUsuario::on_Cooperativo_clicked()
{

}

void VentanaPrincipalUsuario::on_Ranking_clicked()
{

}

void VentanaPrincipalUsuario::on_CerrarSesion_clicked()
{
    emit buttonClicked();
    this->close();
}

void VentanaPrincipalUsuario::Aparecer()
{
    this->show();
}

void VentanaPrincipalUsuario::on_comojugar_clicked()
{

}
