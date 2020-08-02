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
        ammo.cpp \
        bullet.cpp \
        bullet2.cpp \
        enemy.cpp \
        enemyship.cpp \
        game.cpp \
        game2.cpp \
        ganar.cpp \
        healer.cpp \
        health.cpp \
        healthbar.cpp \
        inicarsesion2.cpp \
        main.cpp \
        mainwindow.cpp \
        nodo.cpp \
        obstaculo.cpp \
        pasarnivel.cpp \
        pausar.cpp \
        perder.cpp \
        player1.cpp \
        principal.cpp \
        registro.cpp \
        score.cpp \
        seleccionarnivel.cpp \
        ship.cpp \
        sinenemyship.cpp \
        spaceship.cpp \
        vec3.cpp \
        ventanaprincipalusuario.cpp

HEADERS += \
        ammo.h \
        bullet.h \
        bullet2.h \
        enemy.h \
        enemyship.h \
        game.h \
        game2.h \
        ganar.h \
        healer.h \
        health.h \
        healthbar.h \
        inicarsesion2.h \
        mainwindow.h \
        nodo.h \
        obstaculo.h \
        pasarnivel.h \
        pausar.h \
        perder.h \
        player1.h \
        principal.h \
        registro.h \
        score.h \
        seleccionarnivel.h \
        ship.h \
        sinenemyship.h \
        spaceship.h \
        vec3.h \
        ventanaprincipalusuario.h

FORMS += \
        ganar.ui \
        inicarsesion2.ui \
        pasarnivel.ui \
        pausar.ui \
        perder.ui \
        principal.ui \
        registro.ui \
        seleccionarnivel.ui \
        ventanaprincipalusuario.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
