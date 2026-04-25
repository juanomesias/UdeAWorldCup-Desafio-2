#include <iostream>
#include "Torneo.h"

using namespace std;

Torneo::Torneo(int n) {
    cantidadGrupos = n;
    grupos = new Grupo[n];
}

Torneo::~Torneo() {
    delete[] grupos;
}

Grupo* Torneo::getGrupos() {
    return grupos;
}

void Torneo::simularFaseGrupos() {
    cout << "===== FASE DE GRUPOS =====" << endl;

    for (int i = 0; i < cantidadGrupos; i++) {
        cout << endl << "Grupo " << char('A' + i) << endl;

        grupos[i].generarPartidos();
        grupos[i].simularGrupo();
        grupos[i].calcularTabla();
    }
}

void Torneo::mostrarResultadosGrupos() {
    cout << endl << "===== TABLAS DE GRUPOS =====" << endl;

    for (int i = 0; i < cantidadGrupos; i++) {
        grupos[i].mostrarTabla();
        cout << endl;
    }
}