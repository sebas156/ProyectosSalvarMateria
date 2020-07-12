#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMessageBox>
#include <QMainWindow>
#include <map>
#include <vector>
#include <fstream>
#include <string>
#include "principal.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    vector<map<string,map<string,int>>> UsuariosRegistrados;
    principal *InterfazInicial;
};

#endif // MAINWINDOW_H
