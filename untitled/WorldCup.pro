TEMPLATE = app
TARGET = MiProyecto

QT -= gui
QT += core

CONFIG += console
CONFIG -= app_bundle

SOURCES += \
    main.cpp \
    Jugador.cpp \
    Equipo.cpp \
    Partido.cpp \
    Grupo.cpp \
    Torneo.cpp

HEADERS += \
    Jugador.h \
    Equipo.h \
    Partido.h \
    Grupo.h \
    Torneo.h

#QMAKE_POST_LINK += $$quote(cmd /c copy $$shell_path($$PWD/selecciones_clasificadas_mundial.csv) $$shell_path($$OUT_PWD/selecciones_clasificadas_mundial.csv))