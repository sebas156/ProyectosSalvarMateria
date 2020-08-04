#ifndef VENTANAPRINCIPALUSUARIO_H
#define VENTANAPRINCIPALUSUARIO_H

#include <QWidget>
#include <iostream>
#include <string>
#include "seleccionarnivel.h"
#include <QTimer>
#include <fstream>
#include <map>
#include <vector>
#include <iostream>
#include "mostrarranking.h"
#include "controles.h"

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
    void LeerRankingDeJugadores();
    void PonerEnElvector(string);
    int StringANumero(string);

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
    void  Ordenamiento_por_Insercion(int);
    void RegistarCambiosEnElRanking();
    void eliminarInterfazMostarRankingUsuarios();
    void Destruircontroles();

signals:
    void buttonClicked();
private:
    controles * InterfazControles;
    mostrarranking * InterfazMostarRanking;
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
    int contadorPuntos=0;
    vector<map<string,int>> RankingDeUsuarios;
};

#endif // VENTANAPRINCIPALUSUARIO_H
