#include <iostream>
#include "Equipo.h"
using namespace std;

Equipo::Equipo() {
    nombre[0] = directorTecnico[0] = federacion[0] = confederacion[0] = '\0';
    rankingFIFA = golesAFavor = golesEnContra = 0;
    partidosGanados = partidosEmpatados = partidosPerdidos = 0;
    cantidadJugadores = 0;
    jugadores = nullptr;
}

Equipo::Equipo(int n) {
    nombre[0] = directorTecnico[0] = federacion[0] = confederacion[0] = '\0';
    rankingFIFA = golesAFavor = golesEnContra = 0;
    partidosGanados = partidosEmpatados = partidosPerdidos = 0;
    cantidadJugadores = n;
    jugadores = new Jugador[n];
}

Equipo::~Equipo() {
    delete[] jugadores;
    jugadores = nullptr;
}

void Equipo::setNombre(const char* n) {
    int i = 0;
    while (n[i] != '\0' && i < 49) { nombre[i] = n[i]; i++; }
    nombre[i] = '\0';
}
void Equipo::setDirector(const char* d) {
    int i = 0;
    while (d[i] != '\0' && i < 49) { directorTecnico[i] = d[i]; i++; }
    directorTecnico[i] = '\0';
}
void Equipo::setFederacion(const char* f) {
    int i = 0;
    while (f[i] != '\0' && i < 99) { federacion[i] = f[i]; i++; }
    federacion[i] = '\0';
}
void Equipo::setConfederacion(const char* c) {
    int i = 0;
    while (c[i] != '\0' && i < 49) { confederacion[i] = c[i]; i++; }
    confederacion[i] = '\0';
}
void Equipo::setRanking(int r) { rankingFIFA = r; }
void Equipo::setEstadisticas(int gf, int gc, int g, int e, int p) {
    golesAFavor = gf; golesEnContra = gc;
    partidosGanados = g; partidosEmpatados = e; partidosPerdidos = p;
}

void Equipo::agregarJugador(int index, const char* nom, int numero) {
    if (index >= 0 && index < cantidadJugadores) {
        jugadores[index].setNombre(nom);
        jugadores[index].setNumeroCamiseta(numero);
    }
}
Jugador& Equipo::getJugador(int index) { return jugadores[index]; }
int Equipo::getCantidadJugadores()     { return cantidadJugadores; }

const char* Equipo::getNombre()        { return nombre;          }
int         Equipo::getRanking()       { return rankingFIFA;     }
const char* Equipo::getDirector()      { return directorTecnico; }
const char* Equipo::getFederacion()    { return federacion;      }
const char* Equipo::getConfederacion() { return confederacion;   }
int Equipo::getGolesAFavor()           { return golesAFavor;     }
int Equipo::getGolesEnContra()         { return golesEnContra;   }
int Equipo::getGanados()               { return partidosGanados; }
int Equipo::getEmpatados()             { return partidosEmpatados;}
int Equipo::getPerdidos()              { return partidosPerdidos; }

void Equipo::mostrarInfo() {
    cout << "Equipo:        " << nombre          << endl;
    cout << "Director:      " << directorTecnico << endl;
    cout << "Federacion:    " << federacion      << endl;
    cout << "Confederacion: " << confederacion   << endl;
    cout << "Ranking FIFA:  " << rankingFIFA     << endl;
    cout << "GF: " << golesAFavor << "  GC: " << golesEnContra << endl;
    cout << "G: " << partidosGanados << "  E: " << partidosEmpatados
         << "  P: " << partidosPerdidos << endl;
}
