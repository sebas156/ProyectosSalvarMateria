#include "seleccionarnivel.h"
#include "ui_seleccionarnivel.h"

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

int SeleccionarNivel::GetNivelSeleccionado()
{
    return nivel;
}

void SeleccionarNivel::on_pushButton_clicked()
{
    if(nivel>=1){
        nivel=1;
        emit buttonClicked2();
    }
    else {
        QMessageBox::warning(this,"Nivel Sin Desbloquear","Lo sentimos pero no has desbloqueado este nivel. ");
    }
}

void SeleccionarNivel::on_pushButton_2_clicked()
{
    if(nivel>=2){
        nivel=2;
        emit buttonClicked2();
    }
    else {
        QMessageBox::warning(this,"Nivel Sin Desbloquear","Lo sentimos pero no has desbloqueado este nivel. ");
    }
}

void SeleccionarNivel::on_pushButton_3_clicked()
{
    if(nivel>=3){
        nivel=3;
        emit buttonClicked2();
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
