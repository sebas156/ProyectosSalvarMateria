#ifndef SELECCIONARNIVEL_H
#define SELECCIONARNIVEL_H

#include <QWidget>
#include <iostream>
#include <string>
#include <QMessageBox>

using namespace std;

namespace Ui {
class SeleccionarNivel;
}

class SeleccionarNivel : public QWidget
{
    Q_OBJECT

public:
    explicit SeleccionarNivel(int, string,QWidget *parent = nullptr);
    ~SeleccionarNivel();
    int GetNivelSeleccionado();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();
signals:
    void buttonClicked();
    void buttonClicked2();
private:
    Ui::SeleccionarNivel *ui;
    int nivel;
    QString NickName;
};

#endif // SELECCIONARNIVEL_H
