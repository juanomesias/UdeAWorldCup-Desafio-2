#ifndef PARTIDO_H
#define PARTIDO_H

#include <string>
#include "Equipo.h"

using namespace std;

class Partido {
private:
    Equipo* equipo1;
    Equipo* equipo2;

    int goles1;
    int goles2;

    string fecha;
    string sede;

    string arbitros[3];

    float posesion1;
    float posesion2;

public:
    void setArbitros(string a1, string a2, string a3);

    void simular();

    Equipo* getEquipo1();
    Equipo* getEquipo2();
    int getGoles1();
    int getGoles2();
    Equipo* getGanador();

    void mostrarResultado();
};

#endif