#include "seleccionarnivel.h"
#include "ui_seleccionarnivel.h"
#include "game.h"
#include "game2.h"

game2 extern *Game2;
game extern *Game;
SeleccionarNivel::SeleccionarNivel(int NivelIput, string UsuarioInput,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SeleccionarNivel)
{
    nivel=NivelIput;
    NickName = QString::fromStdString(UsuarioInput);
    ui->setupUi(this);
    ui->NombreUsuario->setText(NickName);
}

SeleccionarNivel::~SeleccionarNivel()
{
    delete ui;
}

void SeleccionarNivel::on_pushButton_clicked()
{
    if(nivel>=1){
        this->~SeleccionarNivel();
        Game= new game(1);
    }
    else {
        QMessageBox::warning(this,"Nivel Sin Desbloquear","Lo sentimos pero no has desbloqueado este nivel. ");
    }
}

void SeleccionarNivel::on_pushButton_2_clicked()
{
    if(nivel>=2){
        this->~SeleccionarNivel();
        Game2=new game2;
    }
    else {
        QMessageBox::warning(this,"Nivel Sin Desbloquear","Lo sentimos pero no has desbloqueado este nivel. ");
    }
}

void SeleccionarNivel::on_pushButton_3_clicked()
{
    if(nivel>=3){
        this->~SeleccionarNivel();
        Game= new game(3);
    }
    else {
        QMessageBox::warning(this,"Nivel Sin Desbloquear","Lo sentimos pero no has desbloqueado este nivel. ");
    }
}

void SeleccionarNivel::on_pushButton_4_clicked()
{
    emit buttonClicked();
    this->~SeleccionarNivel();
}
