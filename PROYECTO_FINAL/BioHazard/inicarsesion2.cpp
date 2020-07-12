#include "inicarsesion2.h"
#include "ui_inicarsesion2.h"

InicarSesion2::InicarSesion2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InicarSesion2)
{
    ui->setupUi(this);
}

string InicarSesion2::GetUserName()
{
    return UserName;
}

string InicarSesion2::GerPaswoord()
{
    return Paswoord;
}

void InicarSesion2::SetUserNameReiniciar(QString TextoUsuario)
{
    ui->UserName->setText(TextoUsuario);
}

void InicarSesion2::SetPaswoordReiniciar(QString TextoContrasena)
{
    ui->passwoord->setText(TextoContrasena);
}

InicarSesion2::~InicarSesion2()
{
    delete ui;
}

void InicarSesion2::on_login_clicked()
{
    // Una vez se de clic en el boton iniciar sesion se guardará los valores que tengan los QLineText
    // Y se emitirá la señal buttonPressed()
   UserName=ui->UserName->text().toStdString();
   Paswoord=ui->passwoord->text().toStdString();
   emit buttonPressed();
}
