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
    PuntosActuales=puntos;
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
    delete SeleccionarNivelUsuario;
    IniciarNivel();
}

void VentanaPrincipalUsuario::InterrumpidoRegresarMenuPrincipal()
{
    Game->InterfazGanar->close();
    Game->InterfazPerder->close();
    Game->InterfazPausa->close();
    Game->InterfazPasarNivel->close();
    delete Game;
    this->show();
}

void VentanaPrincipalUsuario::LlamarIniciarJuego()
{
    if(nivelSeleccionado==1 or nivelSeleccionado==3){
        Game->InterfazPausa->close();
        Game->InterfazPerder->close();
       delete Game;
    }
    IniciarNivel();
}

void VentanaPrincipalUsuario::CompararPasarNivelInmediatamente()
{
    if(nivelSeleccionado>NivelActual){
        NivelActual=nivelSeleccionado;
        RegistrarEnElArchivo();
    }
    Game->InterfazPasarNivel->close();
    delete Game;
    IniciarNivel();
}

void VentanaPrincipalUsuario::SubirNivelSinEjecutar()
{
    if(nivelSeleccionado>NivelActual){
        NivelActual=nivelSeleccionado;
        RegistrarEnElArchivo();
    }
    Game->InterfazPasarNivel->close();
    delete Game;
    this->show();
}

void VentanaPrincipalUsuario::RegistrarEnElArchivo()
{
    ofstream archivo(NickName.toStdString()+".txt");
    if(archivo.fail())
        QMessageBox::warning(this, "ERROR","No se pudo abrir el archivo. ");
    else {
        archivo<<NivelActual<<","<<PuntosActuales<<endl;
    }
    archivo.close();
}

void VentanaPrincipalUsuario::IniciarNivel()
{
    if(nivelSeleccionado==1){
        Game=new game(&nivelSeleccionado,ModoDeJuego,NickName.toStdString());
        connect(Game->InterfazPausa,&pausar::buttonClicked2,this,&VentanaPrincipalUsuario::InterrumpidoRegresarMenuPrincipal);
        connect(Game->InterfazPerder,&perder::buttonClicked2,this,&VentanaPrincipalUsuario::InterrumpidoRegresarMenuPrincipal);
        connect(Game->InterfazPerder,&perder::buttonClicked,this,&VentanaPrincipalUsuario::LlamarIniciarJuego);
        connect(Game->InterfazPasarNivel,&PasarNivel::buttonClicked,this,&VentanaPrincipalUsuario::CompararPasarNivelInmediatamente);
        connect(Game->InterfazPasarNivel,&PasarNivel::buttonClicked2,this,&VentanaPrincipalUsuario::SubirNivelSinEjecutar);
        connect(Game->InterfazGanar,&ganar::buttonClicked,this,&VentanaPrincipalUsuario::InterrumpidoRegresarMenuPrincipal);
    }
    else if (nivelSeleccionado==2) {
        Game2=new game2();
    }
    else {
        Game=new game(&nivelSeleccionado,ModoDeJuego,NickName.toStdString());
        connect(Game->InterfazPausa,&pausar::buttonClicked2,this,&VentanaPrincipalUsuario::InterrumpidoRegresarMenuPrincipal);
        connect(Game->InterfazPerder,&perder::buttonClicked2,this,&VentanaPrincipalUsuario::InterrumpidoRegresarMenuPrincipal);
        connect(Game->InterfazPerder,&perder::buttonClicked,this,&VentanaPrincipalUsuario::LlamarIniciarJuego);
        connect(Game->InterfazPasarNivel,&PasarNivel::buttonClicked,this,&VentanaPrincipalUsuario::CompararPasarNivelInmediatamente);
        connect(Game->InterfazPasarNivel,&PasarNivel::buttonClicked2,this,&VentanaPrincipalUsuario::SubirNivelSinEjecutar);
        connect(Game->InterfazGanar,&ganar::buttonClicked,this,&VentanaPrincipalUsuario::InterrumpidoRegresarMenuPrincipal);
    }

}

