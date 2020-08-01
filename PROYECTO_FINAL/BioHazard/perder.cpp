#include "perder.h"
#include "ui_perder.h"

perder::perder(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::perder)
{
    ui->setupUi(this);
}

perder::~perder()
{
    delete ui;
}

void perder::on_reiniciar_clicked()
{
    emit buttonClicked();
}

void perder::on_menu_clicked()
{
    emit buttonClicked2();
}
