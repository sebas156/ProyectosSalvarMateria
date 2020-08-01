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

private:
    Ui::ganar *ui;
};

#endif // GANAR_H
