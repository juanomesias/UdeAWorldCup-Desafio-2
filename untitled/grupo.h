#ifndef GRUPO_H
#define GRUPO_H

#include "Equipo.h"
#include "Partido.h"

class Grupo {
private:
    void ordenarTabla();

    char letra;

    Equipo* equipos[4];
    Partido* partidos[6];

    int puntos[4];

public:
    Grupo(char l);
    Grupo();
    Equipo* getEquipo(int index);
    Equipo* getEquipoEnPosicion(int pos);

    void agregarEquipo(int index, Equipo* eq);

    void generarPartidos();

    void simularGrupo();

    void calcularTabla();

    void mostrarTabla();

    void mostrarGrupo();

    ~Grupo();
};

#endif