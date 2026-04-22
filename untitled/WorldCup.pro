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

QMAKE_POST_LINK += $$quote(cmd /c copy $$shell_path($$PWD/equipos.csv) $$shell_path($$OUT_PWD/equipos.csv))