#include "registro.h"
#include "ui_registro.h"

Registro::Registro(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Registro)
{
    ui->setupUi(this);
}

string Registro::GetNombreUsuario()
{
    return Username;
}

string Registro::GetPaswoord()
{
    return Paswoord1;
}

void Registro::SetUsuarioNameReiniciar(QString TextoUsuario)
{
    ui -> UserName->setText(TextoUsuario);
}

void Registro::SetPaswoordReiniciar(QString TextoContrasena)
{
    ui->passwoord->setText(TextoContrasena);
    ui->passwoord_2->setText(TextoContrasena);
}


Registro::~Registro()
{
    delete ui;
}

void Registro::on_registro_clicked()
{
    // Una vez se de clic en el boton registrar, se guardará los valores que tengan los QLineText
    Username = ui->UserName->text().toStdString();
    Paswoord1= ui->passwoord->text().toStdString();
    Paswoord2=ui->passwoord_2->text().toStdString();
    // Si las dos contraseñas no coinciden no avanzará. De lo contrario emitirá la señal buttonPressed().
    if(Paswoord1==Paswoord2)
        emit buttonPressed();
    else {
        QMessageBox::warning(this,"ERROR","Las contraseñas NO coinciden.");
    }
}
