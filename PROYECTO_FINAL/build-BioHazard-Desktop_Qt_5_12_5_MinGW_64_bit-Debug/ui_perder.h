/********************************************************************************
** Form generated from reading UI file 'perder.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PERDER_H
#define UI_PERDER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_perder
{
public:
    QTextBrowser *textBrowser;
    QSplitter *splitter;
    QPushButton *reiniciar;
    QPushButton *menu;

    void setupUi(QWidget *perder)
    {
        if (perder->objectName().isEmpty())
            perder->setObjectName(QString::fromUtf8("perder"));
        perder->resize(400, 300);
        textBrowser = new QTextBrowser(perder);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(45, 30, 301, 61));
        splitter = new QSplitter(perder);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setGeometry(QRect(90, 130, 201, 121));
        splitter->setOrientation(Qt::Vertical);
        reiniciar = new QPushButton(splitter);
        reiniciar->setObjectName(QString::fromUtf8("reiniciar"));
        splitter->addWidget(reiniciar);
        menu = new QPushButton(splitter);
        menu->setObjectName(QString::fromUtf8("menu"));
        splitter->addWidget(menu);

        retranslateUi(perder);

        QMetaObject::connectSlotsByName(perder);
    } // setupUi

    void retranslateUi(QWidget *perder)
    {
        perder->setWindowTitle(QApplication::translate("perder", "Form", nullptr));
        textBrowser->setHtml(QApplication::translate("perder", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:11pt;\">Perdiste. Eras la ultima esperanza de la humanidad y perdiste. </span></p></body></html>", nullptr));
        reiniciar->setText(QApplication::translate("perder", "Volver a intentarlo", nullptr));
        menu->setText(QApplication::translate("perder", "Menu", nullptr));
    } // retranslateUi

};

namespace Ui {
    class perder: public Ui_perder {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PERDER_H
