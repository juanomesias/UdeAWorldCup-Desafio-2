#ifndef TORNEO_H
#define TORNEO_H

#include "Grupo.h"

class Torneo {
private:
    Grupo* grupos;
    int cantidadGrupos;

public:
    Torneo(int n);

    ~Torneo();

    Grupo* getGrupos();

    void simularFaseGrupos();
    void mostrarResultadosGrupos();
};

#endif