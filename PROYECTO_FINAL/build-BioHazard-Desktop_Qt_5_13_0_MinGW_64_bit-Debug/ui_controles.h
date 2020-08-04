/********************************************************************************
** Form generated from reading UI file 'controles.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTROLES_H
#define UI_CONTROLES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_controles
{
public:
    QVBoxLayout *verticalLayout;
    QSplitter *splitter;
    QGraphicsView *graphicsView;
    QPushButton *volver;

    void setupUi(QWidget *controles)
    {
        if (controles->objectName().isEmpty())
            controles->setObjectName(QString::fromUtf8("controles"));
        controles->resize(400, 300);
        verticalLayout = new QVBoxLayout(controles);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        splitter = new QSplitter(controles);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Vertical);
        graphicsView = new QGraphicsView(splitter);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        splitter->addWidget(graphicsView);
        volver = new QPushButton(splitter);
        volver->setObjectName(QString::fromUtf8("volver"));
        volver->setMaximumSize(QSize(16777215, 30));
        splitter->addWidget(volver);

        verticalLayout->addWidget(splitter);


        retranslateUi(controles);

        QMetaObject::connectSlotsByName(controles);
    } // setupUi

    void retranslateUi(QWidget *controles)
    {
        controles->setWindowTitle(QCoreApplication::translate("controles", "Form", nullptr));
        volver->setText(QCoreApplication::translate("controles", "volver", nullptr));
    } // retranslateUi

};

namespace Ui {
    class controles: public Ui_controles {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTROLES_H
