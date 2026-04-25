#ifndef GRUPO_H
#define GRUPO_H

#include "Equipo.h"
#include "Partido.h"

class Grupo {
private:
    char letra;

    equipo* equipos[4];
    Partido* partidos[6];

    int puntos[4];

public:
    Grupo(char l);

    void agregarEquipo(int index, equipo* eq);

    void generarPartidos();

    void simularGrupo();

    void calcularTabla();

    void mostrarTabla();
};

#endif