#ifndef VENTANAPRINCIPALUSUARIO_H
#define VENTANAPRINCIPALUSUARIO_H

#include <QWidget>
#include <iostream>
#include <string>
#include "seleccionarnivel.h"
#include <QTimer>
#include <fstream>

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
    void IniciarNivelSeleccionado();
    void InterrumpidoRegresarMenuPrincipal();
    void LlamarIniciarJuego();
    void CompararPasarNivelInmediatamente();
    void SubirNivelSinEjecutar();

signals:
    void buttonClicked();
private:
    void RegistrarEnElArchivo();
    void IniciarNivel();
    Ui::VentanaPrincipalUsuario *ui;
    QString NickName;
    int NivelActual;
    int ModoDeJuego;
    int PuntosActuales;
    int nivelSeleccionado;
    bool reinicio=false;
    SeleccionarNivel *SeleccionarNivelUsuario;
};

#endif // VENTANAPRINCIPALUSUARIO_H
