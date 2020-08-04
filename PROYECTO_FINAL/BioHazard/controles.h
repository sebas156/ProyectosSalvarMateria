#ifndef CONTROLES_H
#define CONTROLES_H
#include <QGraphicsScene>
#include <QWidget>

namespace Ui {
class controles;
}

class controles : public QWidget
{
    Q_OBJECT

public:
    explicit controles(QWidget *parent = nullptr);
    ~controles();

private slots:
    void on_volver_clicked();
signals:
    void buttonClicked();

private:
    Ui::controles *ui;
    QGraphicsScene * scene;
};

#endif // CONTROLES_H
