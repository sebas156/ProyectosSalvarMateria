/********************************************************************************
** Form generated from reading UI file 'registro.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTRO_H
#define UI_REGISTRO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Registro
{
public:
    QGroupBox *groupBox;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *UserName;
    QLineEdit *passwoord;
    QPushButton *registro;
    QLineEdit *passwoord_2;
    QLabel *label_3;

    void setupUi(QWidget *Registro)
    {
        if (Registro->objectName().isEmpty())
            Registro->setObjectName(QString::fromUtf8("Registro"));
        Registro->resize(400, 300);
        groupBox = new QGroupBox(Registro);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(60, 10, 301, 261));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(10);
        groupBox->setFont(font);
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 40, 71, 21));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 100, 121, 21));
        UserName = new QLineEdit(groupBox);
        UserName->setObjectName(QString::fromUtf8("UserName"));
        UserName->setGeometry(QRect(170, 40, 121, 21));
        passwoord = new QLineEdit(groupBox);
        passwoord->setObjectName(QString::fromUtf8("passwoord"));
        passwoord->setGeometry(QRect(170, 100, 121, 21));
        registro = new QPushButton(groupBox);
        registro->setObjectName(QString::fromUtf8("registro"));
        registro->setGeometry(QRect(90, 200, 131, 21));
        passwoord_2 = new QLineEdit(groupBox);
        passwoord_2->setObjectName(QString::fromUtf8("passwoord_2"));
        passwoord_2->setGeometry(QRect(170, 150, 121, 21));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 150, 121, 21));

        retranslateUi(Registro);

        QMetaObject::connectSlotsByName(Registro);
    } // setupUi

    void retranslateUi(QWidget *Registro)
    {
        Registro->setWindowTitle(QCoreApplication::translate("Registro", "Form", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Registro", "Registro", nullptr));
        label->setText(QCoreApplication::translate("Registro", "Usuario:", nullptr));
        label_2->setText(QCoreApplication::translate("Registro", "Contrase\303\261a:", nullptr));
        registro->setText(QCoreApplication::translate("Registro", "REGISTRARSE", nullptr));
        label_3->setText(QCoreApplication::translate("Registro", "Verificar contrase\303\261a:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Registro: public Ui_Registro {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTRO_H
