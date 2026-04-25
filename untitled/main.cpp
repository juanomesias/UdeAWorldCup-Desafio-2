#include <iostream>
#include "Torneo.h"
#include "Equipo.h"

using namespace std;

int main() {
    // Crear equipos manualmente (dummy para pruebas)
    Equipo equipos[4];

    equipos[0] = Equipo(26);
    equipos[0].setNombre("Equipo A");
    equipos[0].setRanking(1);

    equipos[1] = Equipo(26);
    equipos[1].setNombre("Equipo B");
    equipos[1].setRanking(2);

    equipos[2] = Equipo(26);
    equipos[2].setNombre("Equipo C");
    equipos[2].setRanking(3);

    equipos[3] = Equipo(26);
    equipos[3].setNombre("Equipo D");
    equipos[3].setRanking(4);

    // Crear torneo con 1 grupo (solo prueba)
    Torneo torneo(1);

    Grupo* grupos = torneo.getGrupos();

    // Inicializar grupo manualmente
    grupos[0] = Grupo('A');

    for (int i = 0; i < 4; i++) {
        grupos[0].agregarEquipo(i, &equipos[i]);
    }

    // Ejecutar tu parte
    torneo.simularFaseGrupos();
    torneo.mostrarResultadosGrupos();

    return 0;
}