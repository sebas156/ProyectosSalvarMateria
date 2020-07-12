/********************************************************************************
** Form generated from reading UI file 'iniciosesion.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INICIOSESION_H
#define UI_INICIOSESION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InicioSesion
{
public:
    QSplitter *splitter_3;
    QSplitter *splitter;
    QLabel *label;
    QLabel *label_2;
    QSplitter *splitter_2;
    QLabel *label_3;
    QLabel *label_4;

    void setupUi(QWidget *InicioSesion)
    {
        if (InicioSesion->objectName().isEmpty())
            InicioSesion->setObjectName(QString::fromUtf8("InicioSesion"));
        InicioSesion->resize(400, 300);
        splitter_3 = new QSplitter(InicioSesion);
        splitter_3->setObjectName(QString::fromUtf8("splitter_3"));
        splitter_3->setGeometry(QRect(30, 100, 331, 111));
        splitter_3->setOrientation(Qt::Vertical);
        splitter = new QSplitter(splitter_3);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        label = new QLabel(splitter);
        label->setObjectName(QString::fromUtf8("label"));
        splitter->addWidget(label);
        label_2 = new QLabel(splitter);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        splitter->addWidget(label_2);
        splitter_3->addWidget(splitter);
        splitter_2 = new QSplitter(splitter_3);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setOrientation(Qt::Horizontal);
        label_3 = new QLabel(splitter_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        splitter_2->addWidget(label_3);
        label_4 = new QLabel(splitter_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        splitter_2->addWidget(label_4);
        splitter_3->addWidget(splitter_2);

        retranslateUi(InicioSesion);

        QMetaObject::connectSlotsByName(InicioSesion);
    } // setupUi

    void retranslateUi(QWidget *InicioSesion)
    {
        InicioSesion->setWindowTitle(QCoreApplication::translate("InicioSesion", "Form", nullptr));
        label->setText(QCoreApplication::translate("InicioSesion", "Usuario:          ", nullptr));
        label_2->setText(QString());
        label_3->setText(QCoreApplication::translate("InicioSesion", "Contrasena:", nullptr));
        label_4->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class InicioSesion: public Ui_InicioSesion {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INICIOSESION_H
