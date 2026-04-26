#include <iostream>
#include "Torneo.h"

using namespace std;

int main() {
    cout << "========================================" << endl;
    cout << "     UdeA World Cup 2026 Simulator" << endl;
    cout << "========================================" << endl;
    Torneo torneo;

    torneo.cargarDatos();
    torneo.formarGrupos();
    torneo.mostrarGrupos();

    cout << "========================================" << endl;
    cout << "     Simulación de la fase de grupos" << endl;
    cout << "========================================" << endl;
    torneo.simularTorneo();
    torneo.mostrarGrupos();

    cout << "========================================" << endl;
    cout << "   Simulación de la fase eliminatoria" << endl;
    cout << "========================================" << endl;
    torneo.simularEliminatorias();

    cout << "========================================" << endl;
    cout << "          Estadisticas finales" << endl;
    cout << "========================================" << endl;
    torneo.mostrarEstadisticasFinales();

    torneo.guardarResultados();

    return 0;
}