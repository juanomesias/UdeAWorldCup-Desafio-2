#ifndef TORNEO_H
#define TORNEO_H

#include "Equipo.h"

class Torneo {
private:
    Equipo* equipos;
    int cantidadEquipos;

    Equipo grupos[12][4];

public:
    Torneo();
    ~Torneo();

    void cargarDatos();
    void formarGrupos();
    void mostrarGrupos();
};

#endif