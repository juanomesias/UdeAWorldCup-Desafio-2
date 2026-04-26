#ifndef TORNEO_H
#define TORNEO_H

#include "Grupo.h"
#include "Equipo.h"
#include "Partido.h"

class Torneo {
private:
    Equipo* equipos;
    Equipo* r16Clasificados[32];
    Equipo* r8Clasificados[8];
    Equipo* r4Clasificados[4];

    Equipo* campeon;
    Equipo* subcampeon;
    Equipo* tercerLugar;
    Equipo* cuartoLugar;
    int cantidadEquipos;

    Grupo grupos[12];

    void simularLlave(Equipo* entrada[], int n, Equipo* ganadores[], const char* nombreFase);
    void ordenarPorRanking();
    bool esValidoGrupo(int grupoIndex, Equipo* equipo);
    int generarRandom(int min, int max);
    bool mismoGrupo(Equipo* a, Equipo* b);
    void ordenarEquipos(Equipo* arr[], int n);

public:
    Torneo();
    ~Torneo();

    void cargarDatos();
    void formarGrupos();

    void simularTorneo();
    void simularEliminatorias();
    void mostrarGrupos();
    void mostrarTablas();

    void clasificarR16(Equipo* clasificados[]);
    void generarR16(Equipo* clasificados[], Partido* partidosR16[]);

    void guardarResultados();
    void mostrarEstadisticasFinales();
};

#endif