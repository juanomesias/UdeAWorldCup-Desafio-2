#ifndef PARTIDO_H
#define PARTIDO_H

#include "Equipo.h"

class Partido {
private:
    Equipo* equipo1;
    Equipo* equipo2;

    int goles1;
    int goles2;

    char fecha[20];
    char sede[50];

    char arbitros[3][20];

    float posesion1;
    float posesion2;

    int generarRandom(int min, int max);
    int calcularGolesEsperado(Equipo* A, Equipo* B);

public:
    Partido(Equipo* e1, Equipo* e2, const char* f, const char* s);

    void setArbitros(const char* a1, const char* a2, const char* a3);

    void simular();

    int getGoles1();
    int getGoles2();
    Equipo* getGanador();

    void mostrarResultado();
};

#endif