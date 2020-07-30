#ifndef VENTANAPRINCIPALUSUARIO_H
#define VENTANAPRINCIPALUSUARIO_H

#include <QWidget>
#include <iostream>
#include <string>
#include "seleccionarnivel.h"

using namespace std;
namespace Ui {
class VentanaPrincipalUsuario;
}

class VentanaPrincipalUsuario : public QWidget
{
    Q_OBJECT

public:
    explicit VentanaPrincipalUsuario(int,int,string,QWidget *parent = nullptr);
    ~VentanaPrincipalUsuario();

private slots:
    void on_Campana_clicked();
    void on_Cooperativo_clicked();
    void on_Ranking_clicked();
    void on_CerrarSesion_clicked();
    void Aparecer();
    void on_comojugar_clicked();

signals:
    void buttonClicked();
private:
    Ui::VentanaPrincipalUsuario *ui;
    QString NickName;
    int NivelActual;
};

#endif // VENTANAPRINCIPALUSUARIO_H
