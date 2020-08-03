/********************************************************************************
** Form generated from reading UI file 'seleccionarnivel.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECCIONARNIVEL_H
#define UI_SELECCIONARNIVEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SeleccionarNivel
{
public:
    QSplitter *splitter;
    QLabel *label;
    QLabel *NombreUsuario;
    QSplitter *splitter_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;

    void setupUi(QWidget *SeleccionarNivel)
    {
        if (SeleccionarNivel->objectName().isEmpty())
            SeleccionarNivel->setObjectName(QString::fromUtf8("SeleccionarNivel"));
        SeleccionarNivel->resize(400, 300);
        splitter = new QSplitter(SeleccionarNivel);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setGeometry(QRect(70, 30, 271, 61));
        splitter->setOrientation(Qt::Horizontal);
        label = new QLabel(splitter);
        label->setObjectName(QString::fromUtf8("label"));
        splitter->addWidget(label);
        NombreUsuario = new QLabel(splitter);
        NombreUsuario->setObjectName(QString::fromUtf8("NombreUsuario"));
        splitter->addWidget(NombreUsuario);
        splitter_2 = new QSplitter(SeleccionarNivel);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setGeometry(QRect(120, 120, 181, 151));
        splitter_2->setOrientation(Qt::Vertical);
        pushButton = new QPushButton(splitter_2);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        splitter_2->addWidget(pushButton);
        pushButton_2 = new QPushButton(splitter_2);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        splitter_2->addWidget(pushButton_2);
        pushButton_3 = new QPushButton(splitter_2);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        splitter_2->addWidget(pushButton_3);
        pushButton_4 = new QPushButton(splitter_2);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        splitter_2->addWidget(pushButton_4);

        retranslateUi(SeleccionarNivel);

        QMetaObject::connectSlotsByName(SeleccionarNivel);
    } // setupUi

    void retranslateUi(QWidget *SeleccionarNivel)
    {
        SeleccionarNivel->setWindowTitle(QApplication::translate("SeleccionarNivel", "Form", nullptr));
        label->setText(QApplication::translate("SeleccionarNivel", "Usuario:", nullptr));
        NombreUsuario->setText(QApplication::translate("SeleccionarNivel", "TextLabel", nullptr));
        pushButton->setText(QApplication::translate("SeleccionarNivel", "Nivel 1", nullptr));
        pushButton_2->setText(QApplication::translate("SeleccionarNivel", "Nivel 2", nullptr));
        pushButton_3->setText(QApplication::translate("SeleccionarNivel", "Nivel 3", nullptr));
        pushButton_4->setText(QApplication::translate("SeleccionarNivel", "Atras", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SeleccionarNivel: public Ui_SeleccionarNivel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECCIONARNIVEL_H
