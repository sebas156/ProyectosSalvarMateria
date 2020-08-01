#include "pasarnivel.h"
#include "ui_pasarnivel.h"

PasarNivel::PasarNivel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PasarNivel)
{
    ui->setupUi(this);
}

PasarNivel::~PasarNivel()
{
    delete ui;
}

void PasarNivel::on_siguiente_clicked()
{
    emit buttonClicked();
}

void PasarNivel::on_pushButton_2_clicked()
{
     emit buttonClicked2();
}
