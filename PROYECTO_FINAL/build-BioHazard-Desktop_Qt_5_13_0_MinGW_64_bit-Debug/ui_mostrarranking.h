/********************************************************************************
** Form generated from reading UI file 'mostrarranking.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MOSTRARRANKING_H
#define UI_MOSTRARRANKING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mostrarranking
{
public:
    QVBoxLayout *verticalLayout;
    QSplitter *splitter;
    QPlainTextEdit *plainTextEdit;
    QPushButton *volver;

    void setupUi(QWidget *mostrarranking)
    {
        if (mostrarranking->objectName().isEmpty())
            mostrarranking->setObjectName(QString::fromUtf8("mostrarranking"));
        mostrarranking->resize(400, 300);
        verticalLayout = new QVBoxLayout(mostrarranking);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        splitter = new QSplitter(mostrarranking);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Vertical);
        plainTextEdit = new QPlainTextEdit(splitter);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        splitter->addWidget(plainTextEdit);
        volver = new QPushButton(splitter);
        volver->setObjectName(QString::fromUtf8("volver"));
        splitter->addWidget(volver);

        verticalLayout->addWidget(splitter);


        retranslateUi(mostrarranking);

        QMetaObject::connectSlotsByName(mostrarranking);
    } // setupUi

    void retranslateUi(QWidget *mostrarranking)
    {
        mostrarranking->setWindowTitle(QCoreApplication::translate("mostrarranking", "Form", nullptr));
        volver->setText(QCoreApplication::translate("mostrarranking", "Volver", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mostrarranking: public Ui_mostrarranking {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MOSTRARRANKING_H
