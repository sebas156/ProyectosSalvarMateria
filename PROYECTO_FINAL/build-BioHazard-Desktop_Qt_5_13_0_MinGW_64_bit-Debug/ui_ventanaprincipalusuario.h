/********************************************************************************
** Form generated from reading UI file 'ventanaprincipalusuario.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VENTANAPRINCIPALUSUARIO_H
#define UI_VENTANAPRINCIPALUSUARIO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VentanaPrincipalUsuario
{
public:
    QSplitter *splitter;
    QLabel *label;
    QLabel *NombreUsuario;
    QSplitter *splitter_2;
    QPushButton *Campana;
    QPushButton *Cooperativo;
    QPushButton *Ranking;
    QPushButton *comojugar;
    QPushButton *CerrarSesion;

    void setupUi(QWidget *VentanaPrincipalUsuario)
    {
        if (VentanaPrincipalUsuario->objectName().isEmpty())
            VentanaPrincipalUsuario->setObjectName(QString::fromUtf8("VentanaPrincipalUsuario"));
        VentanaPrincipalUsuario->resize(400, 300);
        splitter = new QSplitter(VentanaPrincipalUsuario);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setGeometry(QRect(80, 50, 251, 16));
        splitter->setOrientation(Qt::Horizontal);
        label = new QLabel(splitter);
        label->setObjectName(QString::fromUtf8("label"));
        splitter->addWidget(label);
        NombreUsuario = new QLabel(splitter);
        NombreUsuario->setObjectName(QString::fromUtf8("NombreUsuario"));
        splitter->addWidget(NombreUsuario);
        splitter_2 = new QSplitter(VentanaPrincipalUsuario);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setGeometry(QRect(100, 100, 211, 181));
        splitter_2->setOrientation(Qt::Vertical);
        Campana = new QPushButton(splitter_2);
        Campana->setObjectName(QString::fromUtf8("Campana"));
        splitter_2->addWidget(Campana);
        Cooperativo = new QPushButton(splitter_2);
        Cooperativo->setObjectName(QString::fromUtf8("Cooperativo"));
        splitter_2->addWidget(Cooperativo);
        Ranking = new QPushButton(splitter_2);
        Ranking->setObjectName(QString::fromUtf8("Ranking"));
        splitter_2->addWidget(Ranking);
        comojugar = new QPushButton(splitter_2);
        comojugar->setObjectName(QString::fromUtf8("comojugar"));
        splitter_2->addWidget(comojugar);
        CerrarSesion = new QPushButton(splitter_2);
        CerrarSesion->setObjectName(QString::fromUtf8("CerrarSesion"));
        splitter_2->addWidget(CerrarSesion);

        retranslateUi(VentanaPrincipalUsuario);

        QMetaObject::connectSlotsByName(VentanaPrincipalUsuario);
    } // setupUi

    void retranslateUi(QWidget *VentanaPrincipalUsuario)
    {
        VentanaPrincipalUsuario->setWindowTitle(QCoreApplication::translate("VentanaPrincipalUsuario", "Form", nullptr));
        label->setText(QCoreApplication::translate("VentanaPrincipalUsuario", "Bienvenido: ", nullptr));
        NombreUsuario->setText(QCoreApplication::translate("VentanaPrincipalUsuario", "TextLabel", nullptr));
        Campana->setText(QCoreApplication::translate("VentanaPrincipalUsuario", "Campana", nullptr));
        Cooperativo->setText(QCoreApplication::translate("VentanaPrincipalUsuario", "Cooperativo", nullptr));
        Ranking->setText(QCoreApplication::translate("VentanaPrincipalUsuario", "Ranking", nullptr));
        comojugar->setText(QCoreApplication::translate("VentanaPrincipalUsuario", "\302\277Como jugar?", nullptr));
        CerrarSesion->setText(QCoreApplication::translate("VentanaPrincipalUsuario", "Cerrar Sesion", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VentanaPrincipalUsuario: public Ui_VentanaPrincipalUsuario {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VENTANAPRINCIPALUSUARIO_H
