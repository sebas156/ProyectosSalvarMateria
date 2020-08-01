#include "ganar.h"
#include "ui_ganar.h"

ganar::ganar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ganar)
{
    ui->setupUi(this);
}

ganar::~ganar()
{
    delete ui;
}
