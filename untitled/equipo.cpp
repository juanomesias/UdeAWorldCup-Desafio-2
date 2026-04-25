#include <iostream>
#include <fstream>
#include "Equipo.h"

using namespace std;

// copiar cadena
void Equipo::copiarCadena(char* dest, const char* src, int maxLen) {
    int i = 0;
    while (src[i] != '\0' && i < maxLen - 1) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

// constructor
Equipo::Equipo() {
    nombre[0] = '\0';
    directorTecnico[0] = '\0';
    federacion[0] = '\0';
    confederacion[0] = '\0';

    rankingFIFA = 0;
    golesAFavor = 0;
    golesEnContra = 0;
    partidosGanados = 0;
    partidosEmpatados = 0;
    partidosPerdidos = 0;

    jugadores = nullptr;
    cantidadJugadores = 0;
}

Equipo::Equipo(int n) {
    nombre[0] = '\0';
    directorTecnico[0] = '\0';
    federacion[0] = '\0';
    confederacion[0] = '\0';

    rankingFIFA = 0;
    golesAFavor = 0;
    golesEnContra = 0;
    partidosGanados = 0;
    partidosEmpatados = 0;
    partidosPerdidos = 0;

    cantidadJugadores = n;
    jugadores = new Jugador[n];
}

// copia
Equipo::Equipo(const Equipo& otro) {
    copiarCadena(nombre, otro.nombre, 50);
    copiarCadena(directorTecnico, otro.directorTecnico, 50);
    copiarCadena(federacion, otro.federacion, 100);
    copiarCadena(confederacion, otro.confederacion, 50);

    rankingFIFA = otro.rankingFIFA;
    golesAFavor = otro.golesAFavor;
    golesEnContra = otro.golesEnContra;
    partidosGanados = otro.partidosGanados;
    partidosEmpatados = otro.partidosEmpatados;
    partidosPerdidos = otro.partidosPerdidos;

    cantidadJugadores = otro.cantidadJugadores;

    if (cantidadJugadores > 0) {
        jugadores = new Jugador[cantidadJugadores];
        for (int i = 0; i < cantidadJugadores; i++)
            jugadores[i] = otro.jugadores[i];
    } else {
        jugadores = nullptr;
    }
}

// asignación
Equipo& Equipo::operator=(const Equipo& otro) {
    if (this == &otro) return *this;

    delete[] jugadores;

    copiarCadena(nombre, otro.nombre, 50);
    copiarCadena(directorTecnico, otro.directorTecnico, 50);
    copiarCadena(federacion, otro.federacion, 100);
    copiarCadena(confederacion, otro.confederacion, 50);

    rankingFIFA = otro.rankingFIFA;
    golesAFavor = otro.golesAFavor;
    golesEnContra = otro.golesEnContra;
    partidosGanados = otro.partidosGanados;
    partidosEmpatados = otro.partidosEmpatados;
    partidosPerdidos = otro.partidosPerdidos;

    cantidadJugadores = otro.cantidadJugadores;

    if (cantidadJugadores > 0) {
        jugadores = new Jugador[cantidadJugadores];
        for (int i = 0; i < cantidadJugadores; i++)
            jugadores[i] = otro.jugadores[i];
    } else {
        jugadores = nullptr;
    }

    return *this;
}

// destructor
Equipo::~Equipo() {
    delete[] jugadores;
}

// setters
void Equipo::setNombre(const char* n) { copiarCadena(nombre, n, 50); }
void Equipo::setDirector(const char* d) { copiarCadena(directorTecnico, d, 50); }
void Equipo::setFederacion(const char* f) { copiarCadena(federacion, f, 100); }
void Equipo::setConfederacion(const char* c) { copiarCadena(confederacion, c, 50); }
void Equipo::setRanking(int r) { rankingFIFA = r; }

void Equipo::setEstadisticas(int gf, int gc, int g, int e, int p) {
    golesAFavor = gf;
    golesEnContra = gc;
    partidosGanados = g;
    partidosEmpatados = e;
    partidosPerdidos = p;
}

// jugadores
void Equipo::agregarJugador(int index, const char* nom, int numero) {
    if (index >= 0 && index < cantidadJugadores) {
        jugadores[index].setNombre(nom);
        jugadores[index].setNumeroCamiseta(numero);
    }
}

Jugador& Equipo::getJugador(int index) {
    return jugadores[index];
}

int Equipo::getCantidadJugadores() {
    return cantidadJugadores;
}

// getters
const char* Equipo::getNombre() { return nombre; }
const char* Equipo::getDirector() { return directorTecnico; }
const char* Equipo::getFederacion() { return federacion; }
const char* Equipo::getConfederacion() { return confederacion; }
int Equipo::getRanking() { return rankingFIFA; }

int Equipo::getGolesAFavor() { return golesAFavor; }
int Equipo::getGolesEnContra() { return golesEnContra; }
int Equipo::getGanados() { return partidosGanados; }
int Equipo::getEmpatados() { return partidosEmpatados; }
int Equipo::getPerdidos() { return partidosPerdidos; }

int Equipo::getPuntos() {
    return partidosGanados * 3 + partidosEmpatados;
}

int Equipo::getDiferenciaGoles() {
    return golesAFavor - golesEnContra;
}

// CARGAR CSV
void Equipo::cargarEquipos(Equipo equipos[], int& cantidad) {
    ifstream archivo("equipos.csv");

    if (!archivo.is_open()) {
        cout << "Error abriendo equipos.csv\n";
        cantidad = 0;
        return;
    }

    cantidad = 0;

    int ranking, gf, gc, g, e, p;
    char nom[50], dt[50], fed[100], conf[50];

    while (archivo >> ranking) {
        archivo.ignore();

        archivo.getline(nom, 50, ',');
        archivo.getline(dt, 50, ',');
        archivo.getline(fed, 100, ',');
        archivo.getline(conf, 50, ',');

        archivo >> gf; archivo.ignore();
        archivo >> gc; archivo.ignore();
        archivo >> g; archivo.ignore();
        archivo >> e; archivo.ignore();
        archivo >> p;
        archivo.ignore();

        equipos[cantidad] = Equipo(26);

        equipos[cantidad].setNombre(nom);
        equipos[cantidad].setDirector(dt);
        equipos[cantidad].setFederacion(fed);
        equipos[cantidad].setConfederacion(conf);
        equipos[cantidad].setRanking(ranking);
        equipos[cantidad].setEstadisticas(gf, gc, g, e, p);

        cantidad++;
    }

    archivo.close();
}