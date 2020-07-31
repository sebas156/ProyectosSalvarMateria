#include "pausar.h"
#include "ui_pausar.h"

pausar::pausar(QString Nombre,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pausar)
{
    ui->setupUi(this);
    ui->label->setText(Nombre);
}

pausar::~pausar()
{
    delete ui;
}

void pausar::on_continue_2_clicked()
{
    emit buttonClicked();
}

void pausar::on_Mprincipal_clicked()
{
    emit buttonClicked2();
}
