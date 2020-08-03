#include "mostrarranking.h"
#include "ui_mostrarranking.h"

mostrarranking::mostrarranking(vector<map<string,int>> VectorEntrante,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mostrarranking)
{
    MostrarRanqueados=VectorEntrante;
    ui->setupUi(this);
    PonerLainfoEnPantalla();
}

mostrarranking::~mostrarranking()
{
    delete ui;
}

void mostrarranking::PonerLainfoEnPantalla()
{
    string auxiliar2="  Usuarios           Puntaje    ";
    ui->plainTextEdit->appendPlainText(QString::fromStdString(auxiliar2));
    for(int fila=MostrarRanqueados.size()-1; fila>=0;fila--){
        auxiliar2=MostrarRanqueados[fila].begin()->first;
        int limiteEspacios=23 - auxiliar2.size();
        for(int columna=0;columna<limiteEspacios;columna++){
            auxiliar2+=" ";
        }
        auxiliar2+=to_string(MostrarRanqueados[fila].begin()->second);
        ui->plainTextEdit->appendPlainText(QString::fromStdString(auxiliar2));
    }
    ui->plainTextEdit->update();

}

void mostrarranking::on_volver_clicked()
{
    emit buttonClicked();
}
