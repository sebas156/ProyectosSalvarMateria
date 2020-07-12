#ifndef INICARSESION2_H
#define INICARSESION2_H

#include <QWidget>
#include <iostream>

using namespace std;
namespace Ui {
class InicarSesion2;
}

class InicarSesion2 : public QWidget
{
    Q_OBJECT

public:
    explicit InicarSesion2(QWidget *parent = nullptr);
    string GetUserName();
    string GerPaswoord();
    void SetUserNameReiniciar(QString);
    void SetPaswoordReiniciar(QString);
    ~InicarSesion2();

private slots:
    void on_login_clicked();

signals:
    void buttonPressed();

private:
    Ui::InicarSesion2 *ui;
    string UserName;
    string Paswoord;
};

#endif // INICARSESION2_H
