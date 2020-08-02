/********************************************************************************
** Form generated from reading UI file 'ganar.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GANAR_H
#define UI_GANAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ganar
{
public:
    QSplitter *splitter;
    QTextBrowser *textBrowser;
    QPushButton *aceptar;

    void setupUi(QWidget *ganar)
    {
        if (ganar->objectName().isEmpty())
            ganar->setObjectName(QString::fromUtf8("ganar"));
        ganar->resize(400, 300);
        splitter = new QSplitter(ganar);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setGeometry(QRect(70, 50, 256, 191));
        splitter->setOrientation(Qt::Vertical);
        textBrowser = new QTextBrowser(splitter);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        splitter->addWidget(textBrowser);
        aceptar = new QPushButton(splitter);
        aceptar->setObjectName(QString::fromUtf8("aceptar"));
        splitter->addWidget(aceptar);

        retranslateUi(ganar);

        QMetaObject::connectSlotsByName(ganar);
    } // setupUi

    void retranslateUi(QWidget *ganar)
    {
        ganar->setWindowTitle(QApplication::translate("ganar", "Form", nullptr));
        textBrowser->setHtml(QApplication::translate("ganar", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt;\">Felicidades haz salvado a la tierra de una invasion extraterrestre. Tu planeta se enorgullece. Descanse soldado.</span></p></body></html>", nullptr));
        aceptar->setText(QApplication::translate("ganar", "Aceptar.", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ganar: public Ui_ganar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GANAR_H
