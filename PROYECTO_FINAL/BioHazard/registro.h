#ifndef REGISTRO_H
#define REGISTRO_H
#include <QWidget>
#include <string>
#include <QMessageBox>

using namespace std;

namespace Ui {
class Registro;
}

class Registro : public QWidget
{
    Q_OBJECT

public:
    explicit Registro(QWidget *parent = nullptr);
    string GetNombreUsuario();
    string GetPaswoord();
    void SetUsuarioNameReiniciar(QString);
    void SetPaswoordReiniciar(QString);
    ~Registro();
private slots:
    void on_registro_clicked();

signals:
    void buttonPressed();

private:
    string Username;
    string Paswoord1;
    string Paswoord2;
    Ui::Registro *ui;
};

#endif // REGISTRO_H
