#include <iostream>
#include "Grupo.h"
#include <cstdio>

using namespace std;

Grupo::Grupo(char l) {
    letra = l;

    for (int i = 0; i < 4; i++) {
        equipos[i] = nullptr;
        puntos[i] = 0;
    }

    for (int i = 0; i < 6; i++) {
        partidos[i] = nullptr;
    }
}

Grupo::Grupo() {
    letra = '?';

    for (int i = 0; i < 4; i++) {
        equipos[i] = nullptr;
        puntos[i] = 0;
    }

    for (int i = 0; i < 6; i++) {
        partidos[i] = nullptr;
    }
}

void Grupo::agregarEquipo(int index, Equipo* eq) {
    if (index >= 0 && index < 4) {
        equipos[index] = eq;
    }
}

Equipo* Grupo::getEquipo(int index) {
    if (index >= 0 && index < 4)
        return equipos[index];
    return nullptr;
}

Equipo* Grupo::getEquipoEnPosicion(int pos) {
    if (pos >= 0 && pos < 4)
        return equipos[pos];
    return nullptr;
}

void Grupo::generarPartidos() {
    int idx = 0;

    static int partidoGlobal = 0;

    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {


            int dia = 20 + (partidoGlobal / 4);

            char fechaStr[20];
            sprintf(fechaStr, "%02d/06/2026", dia);

            partidos[idx] = new Partido(
                equipos[i],
                equipos[j],
                fechaStr,
                "nombreSede"
                );

            partidos[idx]->setArbitros("codArbitro1", "codArbitro2", "codArbitro3");

            idx++;
            partidoGlobal++;
        }
    }
}

void Grupo::simularGrupo() {
    for (int i = 0; i < 6; i++) {
        partidos[i]->simular();
        partidos[i]->mostrarResultado();
    }
}

void Grupo::calcularTabla() {
    for (int i = 0; i < 4; i++) {
        puntos[i] = 0;
    }

    for (int i = 0; i < 6; i++) {
        Partido* p = partidos[i];

        Equipo* e1 = p->getEquipo1();
        Equipo* e2 = p->getEquipo2();

        int g1 = p->getGoles1();
        int g2 = p->getGoles2();

        int idx1 = -1, idx2 = -1;

        for (int j = 0; j < 4; j++) {
            if (equipos[j] == e1) idx1 = j;
            if (equipos[j] == e2) idx2 = j;
        }

        if (g1 > g2) {
            puntos[idx1] += 3;
        } else if (g2 > g1) {
            puntos[idx2] += 3;
        } else {
            puntos[idx1] += 1;
            puntos[idx2] += 1;
        }
    }

    ordenarTabla();
}

void Grupo::ordenarTabla() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3 - i; j++) {

            bool cambiar = false;

            if (puntos[j] < puntos[j + 1]) {
                cambiar = true;
            } else if (puntos[j] == puntos[j + 1]) {
                if (equipos[j]->getDiferenciaGoles() <
                    equipos[j + 1]->getDiferenciaGoles()) {
                    cambiar = true;
                }
                else if (equipos[j]->getDiferenciaGoles() ==
                         equipos[j + 1]->getDiferenciaGoles()) {

                    if (equipos[j]->getGolesAFavor() <
                        equipos[j + 1]->getGolesAFavor()) {
                        cambiar = true;
                    }
                }
            }

            if (cambiar) {
                Equipo* tempE = equipos[j];
                equipos[j] = equipos[j + 1];
                equipos[j + 1] = tempE;

                int tempP = puntos[j];
                puntos[j] = puntos[j + 1];
                puntos[j + 1] = tempP;
            }
        }
    }
}

void Grupo::mostrarTabla() {
    cout << "===== Grupo " << letra << " =====" << endl;

    for (int i = 0; i < 4; i++) {
        cout << i + 1 << ". "
             << equipos[i]->getNombre()
             << " | Pts: " << puntos[i]
             << " | DG: " << equipos[i]->getDiferenciaGoles()
             << " | GF: " << equipos[i]->getGolesAFavor()
             << endl;
    }
}

void Grupo::mostrarGrupo() {
    cout << "===== Grupo " << letra << " =====" << endl;
    for (int i = 0; i < 4; i++) {
        cout << i + 1 << ". "
             << equipos[i]->getNombre()
             << " | Confederacion: " << equipos[i]->getConfederacion()
             << " | Ranking: " << equipos[i]->getRanking()
             << endl;
    }
}

Grupo::~Grupo() {
    for (int i = 0; i < 6; i++) {
        delete partidos[i];
    }
}