#include "Torneo.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Torneo::Torneo() {
    equipos = new Equipo[48];
    cantidadEquipos = 0;
}

Torneo::~Torneo() {
    delete[] equipos;
}

void Torneo::cargarDatos() {
    Equipo::cargarEquipos(equipos, cantidadEquipos);
}

// FORMAR GRUPOS
void Torneo::formarGrupos() {

    // ordenar por ranking
    for (int i = 0; i < cantidadEquipos - 1; i++) {
        for (int j = i + 1; j < cantidadEquipos; j++) {
            if (equipos[j].getRanking() < equipos[i].getRanking()) {
                Equipo temp = equipos[i];
                equipos[i] = equipos[j];
                equipos[j] = temp;
            }
        }
    }

    // bombos
    Equipo bombos[4][12];

    int index = 0;
    for (int b = 0; b < 4; b++) {
        for (int i = 0; i < 12; i++) {
            bombos[b][i] = equipos[index++];
        }
    }

    // mezclar
    for (int b = 0; b < 4; b++) {
        for (int i = 0; i < 12; i++) {
            int r = rand() % 12;
            Equipo temp = bombos[b][i];
            bombos[b][i] = bombos[b][r];
            bombos[b][r] = temp;
        }
    }

    // asignar a grupos
    for (int g = 0; g < 12; g++) {
        for (int b = 0; b < 4; b++) {
            grupos[g][b] = bombos[b][g];
        }
    }

    cout << "Grupos formados correctamente\n";
}

void Torneo::mostrarGrupos() {
    for (int i = 0; i < 12; i++) {
        cout << "Grupo " << char('A' + i) << ":\n";

        for (int j = 0; j < 4; j++) {
            cout << " - "
                 << grupos[i][j].getNombre()
                 << " (" << grupos[i][j].getConfederacion() << ")\n";
        }

        cout << endl;
    }
}