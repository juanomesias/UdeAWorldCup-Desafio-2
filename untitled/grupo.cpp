#include <iostream>
#include "Grupo.h"

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

void Grupo::agregarEquipo(int index, Equipo* eq) {
    if (index >= 0 && index < 4) {
        equipos[index] = eq;
    }
}

void Grupo::generarPartidos() {
    int idx = 0;

    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {

            partidos[idx] = new Partido(
                equipos[i],
                equipos[j],
                "20/06/2026",
                "Sede"
                );

            partidos[idx]->setArbitros("A1", "A2", "A3");

            idx++;
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
    // Reiniciar puntos
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