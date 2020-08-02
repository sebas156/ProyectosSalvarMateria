/********************************************************************************
** Form generated from reading UI file 'inicarsesion2.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INICARSESION2_H
#define UI_INICARSESION2_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InicarSesion2
{
public:
    QGroupBox *groupBox;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *UserName;
    QLineEdit *passwoord;
    QPushButton *login;

    void setupUi(QWidget *InicarSesion2)
    {
        if (InicarSesion2->objectName().isEmpty())
            InicarSesion2->setObjectName(QString::fromUtf8("InicarSesion2"));
        InicarSesion2->resize(400, 300);
        groupBox = new QGroupBox(InicarSesion2);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(140, 40, 231, 221));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(10);
        groupBox->setFont(font);
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 40, 71, 21));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 100, 71, 21));
        UserName = new QLineEdit(groupBox);
        UserName->setObjectName(QString::fromUtf8("UserName"));
        UserName->setGeometry(QRect(100, 40, 121, 21));
        passwoord = new QLineEdit(groupBox);
        passwoord->setObjectName(QString::fromUtf8("passwoord"));
        passwoord->setGeometry(QRect(100, 100, 121, 21));
        login = new QPushButton(groupBox);
        login->setObjectName(QString::fromUtf8("login"));
        login->setGeometry(QRect(50, 160, 131, 21));

        retranslateUi(InicarSesion2);

        QMetaObject::connectSlotsByName(InicarSesion2);
    } // setupUi

    void retranslateUi(QWidget *InicarSesion2)
    {
        InicarSesion2->setWindowTitle(QApplication::translate("InicarSesion2", "Form", nullptr));
        groupBox->setTitle(QApplication::translate("InicarSesion2", "SignIn", nullptr));
        label->setText(QApplication::translate("InicarSesion2", "Usuario:", nullptr));
        label_2->setText(QApplication::translate("InicarSesion2", "Contrase\303\261a:", nullptr));
        login->setText(QApplication::translate("InicarSesion2", "INICIAR SESION", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InicarSesion2: public Ui_InicarSesion2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INICARSESION2_H
