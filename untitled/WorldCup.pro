TEMPLATE = app
TARGET = MiProyecto
QT += core gui
CONFIG += console

SOURCES += main.cpp \
    equipo.cpp \
    grupo.cpp \
           jugador.cpp \
    partido.cpp \
    torneo.cpp

HEADERS += jugador.h \
    equipo.h \
    grupo.h \
    partido.h \
    torneo.h