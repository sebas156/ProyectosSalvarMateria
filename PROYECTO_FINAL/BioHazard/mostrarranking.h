#ifndef MOSTRARRANKING_H
#define MOSTRARRANKING_H

#include <QWidget>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;
namespace Ui {
class mostrarranking;
}

class mostrarranking : public QWidget
{
    Q_OBJECT

public:
    explicit mostrarranking(vector<map<string,int>>,QWidget *parent = nullptr);
    ~mostrarranking();
    void PonerLainfoEnPantalla();

private slots:
    void on_volver_clicked();
signals:
    void buttonClicked();

private:
    Ui::mostrarranking *ui;
    vector<map<string,int>> MostrarRanqueados;
};

#endif // MOSTRARRANKING_H
