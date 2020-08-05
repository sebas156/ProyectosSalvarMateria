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
    int NivelActual; // Guarda el nivel maximo que ha desbloqueado el usuario.
    int ModoDeJuego; // Solo puede tener dos estados. 1 o 2. Guarda el modo en el que se jugará en game.
    int PuntosActuales; // Guarda los puntos maximos que el usuario ha podido ganar en el modo supervivencia de game.
    int nivelSeleccionado;  // Guarda el nivel que se ha seleccionado.
    SeleccionarNivel *SeleccionarNivelUsuario; // Interfaz de seleccionar nivel.
    int contadorPuntos=0;    // Cuenta los puntos que el usuario gana cuando juegue el modo supervivencia de game.
    vector<map<string,int>> RankingDeUsuarios; // Vector donde se van a guardar todos los usuarios con el maximo puntaje que han ganado
};                                             // en el modo supervivencia de game.

#endif // VENTANAPRINCIPALUSUARIO_H
