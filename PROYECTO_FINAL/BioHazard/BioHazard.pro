#-------------------------------------------------
#
# Project created by QtCreator 2020-07-09T22:11:48
#
#-------------------------------------------------

QT       += core gui
QT      += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BioHazard
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        bullet.cpp \
        bullet2.cpp \
        enemy.cpp \
        enemyship.cpp \
        game.cpp \
        game2.cpp \
        health.cpp \
        inicarsesion2.cpp \
        main.cpp \
        mainwindow.cpp \
        nodo.cpp \
        obstaculo.cpp \
        player1.cpp \
        principal.cpp \
        registro.cpp \
        score.cpp \
        sinenemyship.cpp \
        spaceship.cpp \
        vec3.cpp

HEADERS += \
        bullet.h \
        bullet2.h \
        enemy.h \
        enemyship.h \
        game.h \
        game2.h \
        health.h \
        inicarsesion2.h \
        mainwindow.h \
        nodo.h \
        obstaculo.h \
        player1.h \
        principal.h \
        registro.h \
        score.h \
        sinenemyship.h \
        spaceship.h \
        vec3.h

FORMS += \
        inicarsesion2.ui \
        principal.ui \
        registro.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
