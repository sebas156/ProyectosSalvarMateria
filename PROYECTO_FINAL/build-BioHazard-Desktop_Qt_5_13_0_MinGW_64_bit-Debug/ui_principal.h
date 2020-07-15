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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_principal
{
public:
    QPushButton *sesion;
    QPushButton *pushButton_2;

    void setupUi(QWidget *principal)
    {
        if (principal->objectName().isEmpty())
            principal->setObjectName(QString::fromUtf8("principal"));
        principal->resize(400, 300);
        sesion = new QPushButton(principal);
        sesion->setObjectName(QString::fromUtf8("sesion"));
        sesion->setGeometry(QRect(200, 70, 121, 51));
        pushButton_2 = new QPushButton(principal);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(200, 160, 121, 51));

        retranslateUi(principal);

        QMetaObject::connectSlotsByName(principal);
    } // setupUi

    void retranslateUi(QWidget *principal)
    {
        principal->setWindowTitle(QCoreApplication::translate("principal", "Form", nullptr));
        sesion->setText(QCoreApplication::translate("principal", "Iniciar Sesion", nullptr));
        pushButton_2->setText(QCoreApplication::translate("principal", "Registro", nullptr));
    } // retranslateUi

};

namespace Ui {
    class principal: public Ui_principal {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRINCIPAL_H
