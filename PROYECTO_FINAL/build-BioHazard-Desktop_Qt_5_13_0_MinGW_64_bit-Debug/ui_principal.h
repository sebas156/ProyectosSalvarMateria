/********************************************************************************
** Form generated from reading UI file 'principal.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRINCIPAL_H
#define UI_PRINCIPAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_principal
{
public:
    QLabel *label;
    QSplitter *splitter;
    QPushButton *sesion;
    QPushButton *pushButton_2;
    QPushButton *Cerrar;

    void setupUi(QWidget *principal)
    {
        if (principal->objectName().isEmpty())
            principal->setObjectName(QString::fromUtf8("principal"));
        principal->resize(400, 300);
        label = new QLabel(principal);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(120, 30, 151, 51));
        splitter = new QSplitter(principal);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setGeometry(QRect(110, 90, 181, 171));
        splitter->setOrientation(Qt::Vertical);
        sesion = new QPushButton(splitter);
        sesion->setObjectName(QString::fromUtf8("sesion"));
        splitter->addWidget(sesion);
        pushButton_2 = new QPushButton(splitter);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        splitter->addWidget(pushButton_2);
        Cerrar = new QPushButton(splitter);
        Cerrar->setObjectName(QString::fromUtf8("Cerrar"));
        splitter->addWidget(Cerrar);

        retranslateUi(principal);

        QMetaObject::connectSlotsByName(principal);
    } // setupUi

    void retranslateUi(QWidget *principal)
    {
        principal->setWindowTitle(QCoreApplication::translate("principal", "Form", nullptr));
        label->setText(QCoreApplication::translate("principal", "BIOHAZARD", nullptr));
        sesion->setText(QCoreApplication::translate("principal", "Iniciar Sesion", nullptr));
        pushButton_2->setText(QCoreApplication::translate("principal", "Registro", nullptr));
        Cerrar->setText(QCoreApplication::translate("principal", "Cerrar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class principal: public Ui_principal {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRINCIPAL_H
