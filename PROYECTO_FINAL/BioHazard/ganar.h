#ifndef GANAR_H
#define GANAR_H

#include <QWidget>

namespace Ui {
class ganar;
}

class ganar : public QWidget
{
    Q_OBJECT

public:
    explicit ganar(QWidget *parent = nullptr);
    ~ganar();

private slots:
    void on_aceptar_clicked();
signals:
    void buttonClicked();

private:
    Ui::ganar *ui;
};

#endif // GANAR_H
