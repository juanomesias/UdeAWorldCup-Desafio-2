#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Partido.h"
#include "Jugador.h"

using namespace std;

Partido::Partido(Equipo* e1, Equipo* e2, const char* f, const char* s) {
    equipo1 = e1;
    equipo2 = e2;

    goles1 = 0;
    goles2 = 0;

    posesion1 = 0;
    posesion2 = 0;

    cantGoleadores1 = 0;
    cantGoleadores2 = 0;
    huboProrroga = false;

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

int Partido::generarRandom(int min, int max) {
    return min + rand() % (max - min + 1);
}

float Partido::randomPorcentaje() {
    return (float)(rand() % 10000) / 100.0f;
}

void Partido::seleccionarConvocados(int seleccionados[], int total) {
    bool usados[50] = {false};

    for (int i = 0; i < 11; i++) {
        int idx;
        do {
            idx = generarRandom(0, total - 1);
        } while (usados[idx]);

        usados[idx] = true;
        seleccionados[i] = idx;
    }
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

int Partido::calcularGolesEsperados(Equipo* A, Equipo* B) {
    float GF = A->getGolesAFavor() / 10.0f;
    float GC = B->getGolesEnContra() / 10.0f;

    float alpha = 0.6f;
    float beta = 0.4f;
    float mu = 1.35f;

    float lambda = alpha * GF + beta * GC + mu;

    int goles = (int)lambda;

    goles += generarRandom(-1, 1);

    if (goles < 0) goles = 0;

    return goles;
}

void Partido::simular(bool eliminatoria) {
    static bool init = false;
    if (!init) {
        srand(time(0));
        init = true;
    }

    cantGoleadores1 = 0;
    cantGoleadores2 = 0;
    huboProrroga = false;

    seleccionarConvocados(convocados1, equipo1->getCantidadJugadores());
    seleccionarConvocados(convocados2, equipo2->getCantidadJugadores());

    goles1 = calcularGolesEsperados(equipo1, equipo2);
    goles2 = calcularGolesEsperados(equipo2, equipo1);

    if (eliminatoria && goles1 == goles2) {
        huboProrroga = true;

        int r1 = equipo1->getRanking();
        int r2 = equipo2->getRanking();
        int total = r1 + r2;

        if (total > 0) {
            int sorteo = generarRandom(1, total);
            if (sorteo <= r2) {
                goles1++;
            } else {
                goles2++;
            }
        } else {
            if (generarRandom(0, 1) == 0) goles1++;
            else goles2++;
        }
    }

    int minutos = huboProrroga ? 120 : 90;

    int r1 = equipo1->getRanking();
    int r2 = equipo2->getRanking();

    if (r1 + r2 != 0) {
        posesion1 = (float)r2 / (r1 + r2) * 100;
        posesion2 = 100 - posesion1;
    }

    for (int i = 0; i < 11; i++) {
        Jugador& j = equipo1->getJugador(convocados1[i]);
        j.jugarMinutos(minutos);
        j.jugarPartido();

        if (randomPorcentaje() < 6.0f) {
            j.recibirAmarilla();
            if (randomPorcentaje() < 1.15f) {
                j.recibirRoja();
            }
        }

        if (randomPorcentaje() < 13.0f) {
            j.cometerFalta();
            if (randomPorcentaje() < 2.75f) {
                j.cometerFalta();
                if (randomPorcentaje() < 0.7f) {
                    j.cometerFalta();
                }
            }
        }
    }

    for (int i = 0; i < 11; i++) {
        Jugador& j = equipo2->getJugador(convocados2[i]);
        j.jugarMinutos(minutos);
        j.jugarPartido();

        if (randomPorcentaje() < 6.0f) {
            j.recibirAmarilla();
            if (randomPorcentaje() < 1.15f) {
                j.recibirRoja();
            }
        }

        if (randomPorcentaje() < 13.0f) {
            j.cometerFalta();
            if (randomPorcentaje() < 2.75f) {
                j.cometerFalta();
                if (randomPorcentaje() < 0.7f) {
                    j.cometerFalta();
                }
            }
        }
    }

    for (int i = 0; i < goles1; i++) {
        int idx = generarRandom(0, 10);
        Jugador& j = equipo1->getJugador(convocados1[idx]);
        j.anotarGol();
        goleadores1[cantGoleadores1++] = j.getNumeroCamiseta();
    }

    for (int i = 0; i < goles2; i++) {
        int idx = generarRandom(0, 10);
        Jugador& j = equipo2->getJugador(convocados2[idx]);
        j.anotarGol();
        goleadores2[cantGoleadores2++] = j.getNumeroCamiseta();
    }

    for (int i = 0; i < goles1; i++) {
        equipo1->sumarGolAFavor();
        equipo2->sumarGolEnContra();
    }

    for (int i = 0; i < goles2; i++) {
        equipo2->sumarGolAFavor();
        equipo1->sumarGolEnContra();
    }

    if (goles1 > goles2) {
        equipo1->sumarGanado();
        equipo2->sumarPerdido();
    } else if (goles2 > goles1) {
        equipo2->sumarGanado();
        equipo1->sumarPerdido();
    } else {
        equipo1->sumarEmpatado();
        equipo2->sumarEmpatado();
    }
}

void Partido::mostrarGoleadores() {
    cout << "Goleadores de " << equipo1->getNombre() << ": ";
    if (cantGoleadores1 == 0) {
        cout << "ninguno";
    } else {
        for (int i = 0; i < cantGoleadores1; i++) {
            cout << goleadores1[i];
            if (i + 1 < cantGoleadores1) cout << ", ";
        }
    }
    cout << endl;

    cout << "Goleadores de " << equipo2->getNombre() << ": ";
    if (cantGoleadores2 == 0) {
        cout << "ninguno";
    } else {
        for (int i = 0; i < cantGoleadores2; i++) {
            cout << goleadores2[i];
            if (i + 1 < cantGoleadores2) cout << ", ";
        }
    }
    cout << endl;
}

int Partido::getGoles1() { return goles1; }
int Partido::getGoles2() { return goles2; }

Equipo* Partido::getGanador() {
    if (goles1 > goles2) return equipo1;
    if (goles2 > goles1) return equipo2;
    return nullptr;
}

Equipo* Partido::getEquipo1() { return equipo1; }
Equipo* Partido::getEquipo2() { return equipo2; }

void Partido::mostrarResultado() {
    cout << equipo1->getNombre() << " " << goles1
         << " - " << goles2
         << " " << equipo2->getNombre();
    if (huboProrroga) {
        cout << " (prorroga)";
    }

    cout << endl;
}