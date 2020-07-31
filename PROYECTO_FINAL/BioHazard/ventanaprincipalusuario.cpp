#include "ventanaprincipalusuario.h"
#include "ui_ventanaprincipalusuario.h"
#include "game.h"
#include "game2.h"
game2 extern *Game2;
game extern *Game;

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
    ModoDeJuego=1;
    this->close();
    SeleccionarNivelUsuario = new SeleccionarNivel(NivelActual,NickName.toStdString());
    connect(SeleccionarNivelUsuario,&SeleccionarNivel::buttonClicked,this,&VentanaPrincipalUsuario::Aparecer);
    connect(SeleccionarNivelUsuario,&SeleccionarNivel::buttonClicked2,this,&VentanaPrincipalUsuario::IniciarNivelSeleccionado);
    SeleccionarNivelUsuario->show();
}

void VentanaPrincipalUsuario::on_Cooperativo_clicked()
{
    ModoDeJuego=2;
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

void VentanaPrincipalUsuario::IniciarNivelSeleccionado()
{
   nivelSeleccionado=SeleccionarNivelUsuario->GetNivelSeleccionado();
    SeleccionarNivelUsuario->~SeleccionarNivel();
    if(nivelSeleccionado==1){
        Game=new game(&nivelSeleccionado,ModoDeJuego,NickName.toStdString());
        connect(Game->InterfazPausa,&pausar::buttonClicked2,this,&VentanaPrincipalUsuario::InterrumpidoPausa);
    }
    else if (nivelSeleccionado==2) {
        Game2=new game2();
    }
    else {
        Game=new game(&nivelSeleccionado,ModoDeJuego,NickName.toStdString());
    }
}

void VentanaPrincipalUsuario::InterrumpidoPausa()
{
    Game->InterfazPausa->close();
    Game->view->close();
    Game->music->stop();
    Game->close();
    this->show();
}

