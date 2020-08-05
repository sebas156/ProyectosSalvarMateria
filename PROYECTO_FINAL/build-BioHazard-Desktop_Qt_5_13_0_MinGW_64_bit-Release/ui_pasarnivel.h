/********************************************************************************
** Form generated from reading UI file 'pasarnivel.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PASARNIVEL_H
#define UI_PASARNIVEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PasarNivel
{
public:
    QSplitter *splitter_2;
    QTextBrowser *textBrowser;
    QSplitter *splitter;
    QPushButton *siguiente;
    QPushButton *pushButton_2;

    void setupUi(QWidget *PasarNivel)
    {
        if (PasarNivel->objectName().isEmpty())
            PasarNivel->setObjectName(QString::fromUtf8("PasarNivel"));
        PasarNivel->resize(400, 300);
        splitter_2 = new QSplitter(PasarNivel);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setGeometry(QRect(80, 50, 256, 213));
        splitter_2->setOrientation(Qt::Vertical);
        textBrowser = new QTextBrowser(splitter_2);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        splitter_2->addWidget(textBrowser);
        splitter = new QSplitter(splitter_2);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        siguiente = new QPushButton(splitter);
        siguiente->setObjectName(QString::fromUtf8("siguiente"));
        splitter->addWidget(siguiente);
        pushButton_2 = new QPushButton(splitter);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        splitter->addWidget(pushButton_2);
        splitter_2->addWidget(splitter);

        retranslateUi(PasarNivel);

        QMetaObject::connectSlotsByName(PasarNivel);
    } // setupUi

    void retranslateUi(QWidget *PasarNivel)
    {
        PasarNivel->setWindowTitle(QCoreApplication::translate("PasarNivel", "Form", nullptr));
        textBrowser->setHtml(QCoreApplication::translate("PasarNivel", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">Felicidades, haz Sobrevivido. </span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">\302\277Estas listo para el siguiente nivel?</span></p></body></html>", nullptr));
        siguiente->setText(QCoreApplication::translate("PasarNivel", "Siguiente nivel", nullptr));
        pushButton_2->setText(QCoreApplication::translate("PasarNivel", "Menu principal.", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PasarNivel: public Ui_PasarNivel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PASARNIVEL_H
