#ifndef INICIOSESION_H
#define INICIOSESION_H

#include <QWidget>
#include <iostream>

using namespace std;
namespace Ui {
class InicioSesion;
}

class InicioSesion : public QWidget
{
    Q_OBJECT

public:
    explicit InicioSesion(QWidget *parent = nullptr);
    ~InicioSesion();

private slots:
    void on_login_clicked();

private:
    Ui::InicioSesion *ui;
    string UserName;
    string Paswoord;
};

#endif // INICIOSESION_H
