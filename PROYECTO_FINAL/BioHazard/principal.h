#ifndef PRINCIPAL_H
#define PRINCIPAL_H
#include <QMessageBox>
#include <QWidget>
#include "registro.h"
#include "inicarsesion2.h"
#include <map>
#include <vector>
#include <fstream>
#include <string>

namespace Ui {
class principal;
}

class principal : public QWidget
{
    Q_OBJECT

public:
    explicit principal(QWidget *parent = nullptr);
    void LeerRegistroDeUsuarios();
    void LlenarConUsuariosRegistrados(string);
    int StringNumeroCodigo(string);
    int BusquedaBinaria(string, int, int);
    void  Ordenamiento_por_Insercion(int);
    void Registrar();
    ~principal();

private slots:
    void on_sesion_clicked();
    void on_pushButton_2_clicked();
    void VerificarNoEstaRegistar();
    void VerificarSiEstaInicioSesion();

private:
    Ui::principal *ui;
    vector<map<string,map<string,int>>> UsuariosRegistrados;
    Registro * InterfazRegistrar;
    InicarSesion2 *InterfazIniciarSesion;
    string AuxUsuario, AuxPaswoord1;
};

#endif // PRINCIPAL_H
