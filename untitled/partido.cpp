#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Partido.h"

using namespace std;

Partido::Partido(Equipo* e1, Equipo* e2, const char* f, const char* s) {
    equipo1 = e1;
    equipo2 = e2;

    goles1 = 0;
    goles2 = 0;

    posesion1 = 0;
    posesion2 = 0;

    int i = 0;
    while (f[i] != '\0' && i < 19) {
        fecha[i] = f[i];
        i++;
    }
    fecha[i] = '\0';

    i = 0;
    while (s[i] != '\0' && i < 49) {
        sede[i] = s[i];
        i++;
    }
    sede[i] = '\0';
}

void Partido::setArbitros(const char* a1, const char* a2, const char* a3) {
    const char* arr[3] = {a1, a2, a3};

    for (int j = 0; j < 3; j++) {
        int i = 0;
        while (arr[j][i] != '\0' && i < 19) {
            arbitros[j][i] = arr[j][i];
            i++;
        }
        arbitros[j][i] = '\0';
    }
}

int Partido::generarRandom(int min, int max) {
    return min + rand() % (max - min + 1);
}

int Partido::calcularGolesEsperados(Equipo* A, Equipo* B) {
    float GF = A->getPromedioGolesFavor();
    float GC = B->getPromedioGolesContra();

    float alpha = 0.6f;
    float beta = 0.4f;
    float mu = 1.35f;

    float lambda = alpha * GF + beta * GC + mu;

    int goles = (int)lambda;

    goles += generarRandom(-1, 1);

    if (goles < 0) goles = 0;

    return goles;
}

void Partido::simular() {
    static bool init = false;
    if (!init) {
        srand(time(0));
        init = true;
    }

    goles1 = calcularGolesEsperados(equipo1, equipo2);
    goles2 = calcularGolesEsperados(equipo2, equipo1);

    int r1 = equipo1->getRanking();
    int r2 = equipo2->getRanking();

    if (r1 + r2 != 0) {
        posesion1 = (float)r2 / (r1 + r2) * 100;
        posesion2 = 100 - posesion1;
    }

    for (int i = 0; i < goles1; i++) {
        int idx = generarRandom(0, 25);
        Jugador* j = equipo1->obtenerJugador(idx);
        j->anotarGol();
        j->jugarMinutos(90);
    }

    for (int i = 0; i < goles2; i++) {
        int idx = generarRandom(0, 25);
        Jugador* j = equipo2->obtenerJugador(idx);
        j->anotarGol();
        j->jugarMinutos(90);
    }

    equipo1->actualizarEstadisticas(goles1, goles2);
    equipo2->actualizarEstadisticas(goles2, goles1);
}

int Partido::getGoles1() {
    return goles1;
}

int Partido::getGoles2() {
    return goles2;
}

Equipo* Partido::getGanador() {
    if (goles1 > goles2) return equipo1;
    if (goles2 > goles1) return equipo2;
    return 0;
}

void Partido::mostrarResultado() {
    cout << "Resultado: " << goles1 << " - " << goles2 << endl;
}