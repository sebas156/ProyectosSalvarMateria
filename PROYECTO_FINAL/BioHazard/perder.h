#ifndef PERDER_H
#define PERDER_H

#include <QWidget>

namespace Ui {
class perder;
}

class perder : public QWidget
{
    Q_OBJECT

public:
    explicit perder(QWidget *parent = nullptr);
    ~perder();

private slots:
    void on_reiniciar_clicked();
    void on_menu_clicked();

signals:
    void buttonClicked();
    void buttonClicked2();

private:
    Ui::perder *ui;
};

#endif // PERDER_H
