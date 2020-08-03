#ifndef MOSTRARRANKING_H
#define MOSTRARRANKING_H

#include <QWidget>

namespace Ui {
class mostrarranking;
}

class mostrarranking : public QWidget
{
    Q_OBJECT

public:
    explicit mostrarranking(QWidget *parent = nullptr);
    ~mostrarranking();

private:
    Ui::mostrarranking *ui;
};

#endif // MOSTRARRANKING_H
