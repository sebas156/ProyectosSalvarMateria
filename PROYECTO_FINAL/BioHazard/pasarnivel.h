#ifndef PASARNIVEL_H
#define PASARNIVEL_H

#include <QWidget>

namespace Ui {
class PasarNivel;
}

class PasarNivel : public QWidget
{
    Q_OBJECT

public:
    explicit PasarNivel(QWidget *parent = nullptr);
    ~PasarNivel();

private slots:
    void on_siguiente_clicked();
    void on_pushButton_2_clicked();
signals:
    void buttonClicked();
    void buttonClicked2();

private:
    Ui::PasarNivel *ui;
};

#endif // PASARNIVEL_H
