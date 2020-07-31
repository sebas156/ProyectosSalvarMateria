#ifndef PAUSAR_H
#define PAUSAR_H

#include <QWidget>

namespace Ui {
class pausar;
}

class pausar : public QWidget
{
    Q_OBJECT

public:
    explicit pausar(QString,QWidget *parent = nullptr);
    ~pausar();

private slots:
    void on_continue_2_clicked();

    void on_Mprincipal_clicked();

signals:
    void buttonClicked();
    void buttonClicked2();

private:
    Ui::pausar *ui;
};

#endif // PAUSAR_H
