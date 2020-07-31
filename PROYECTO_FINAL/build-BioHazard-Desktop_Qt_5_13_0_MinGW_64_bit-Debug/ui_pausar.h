/********************************************************************************
** Form generated from reading UI file 'pausar.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAUSAR_H
#define UI_PAUSAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_pausar
{
public:
    QPushButton *continue_2;
    QPushButton *Mprincipal;
    QLabel *label;
    QTextBrowser *textBrowser;

    void setupUi(QWidget *pausar)
    {
        if (pausar->objectName().isEmpty())
            pausar->setObjectName(QString::fromUtf8("pausar"));
        pausar->resize(400, 300);
        continue_2 = new QPushButton(pausar);
        continue_2->setObjectName(QString::fromUtf8("continue_2"));
        continue_2->setGeometry(QRect(100, 220, 80, 21));
        Mprincipal = new QPushButton(pausar);
        Mprincipal->setObjectName(QString::fromUtf8("Mprincipal"));
        Mprincipal->setGeometry(QRect(230, 220, 80, 21));
        label = new QLabel(pausar);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(90, 60, 91, 21));
        textBrowser = new QTextBrowser(pausar);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(80, 80, 221, 111));

        retranslateUi(pausar);

        QMetaObject::connectSlotsByName(pausar);
    } // setupUi

    void retranslateUi(QWidget *pausar)
    {
        pausar->setWindowTitle(QCoreApplication::translate("pausar", "Form", nullptr));
        continue_2->setText(QCoreApplication::translate("pausar", "Continuar", nullptr));
        Mprincipal->setText(QCoreApplication::translate("pausar", "Menu", nullptr));
        label->setText(QCoreApplication::translate("pausar", "TextLabel", nullptr));
        textBrowser->setHtml(QCoreApplication::translate("pausar", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"justify\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-style:italic;\">Tras ver The Walking Dead uno aprende a valorar a los Zombies. Ellos no te quieren por el f\303\255sico, s\303\263lo por el cerebro... y eso es muy bonito.</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class pausar: public Ui_pausar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAUSAR_H
