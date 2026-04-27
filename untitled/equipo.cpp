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

    golesAFavorTorneo = 0;
    golesEnContraTorneo = 0;
    partidosGanadosTorneo = 0;
    partidosEmpatadosTorneo = 0;
    partidosPerdidosTorneo = 0;

    cantidadJugadores = n;
    jugadores = new Jugador[n];
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
//para las estadisticas del torneo
void Equipo::reiniciarEstadisticasTorneo() {
    golesAFavorTorneo = 0;
    golesEnContraTorneo = 0;
    partidosGanadosTorneo = 0;
    partidosEmpatadosTorneo = 0;
    partidosPerdidosTorneo = 0;
}
void Equipo::sumarGolAFavorTorneo() { golesAFavorTorneo++; }
void Equipo::sumarGolEnContraTorneo() { golesEnContraTorneo++; }
void Equipo::sumarGanadoTorneo() { partidosGanadosTorneo++; }
void Equipo::sumarEmpatadoTorneo() { partidosEmpatadosTorneo++; }
void Equipo::sumarPerdidoTorneo() { partidosPerdidosTorneo++; }
int Equipo::getGolesAFavorTorneo() { return golesAFavorTorneo; }
int Equipo::getGolesEnContraTorneo() { return golesEnContraTorneo; }
int Equipo::getGanadosTorneo() { return partidosGanadosTorneo; }
int Equipo::getEmpatadosTorneo() { return partidosEmpatadosTorneo; }
int Equipo::getPerdidosTorneo() { return partidosPerdidosTorneo; }

int Equipo::getPuntosTorneo() {
    return partidosGanadosTorneo * 3 + partidosEmpatadosTorneo;
}

int Equipo::getDiferenciaGolesTorneo() {
    return golesAFavorTorneo - golesEnContraTorneo;
}
//para las estadisticas del torneo

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

void Equipo::cargarEquipos(Equipo equipos[], int& cantidad) {
    ifstream archivo("selecciones_clasificadas_mundial.csv");

    if (!archivo.is_open()) {
        cout << "Error abriendo CSV\n";
        cantidad = 0;
        return;
    }

    cantidad = 0;
    archivo.ignore(1000, '\n');
    archivo.ignore(1000, '\n');

    int ranking, gf, gc, g, e, p;

    char pais[50];
    char dt[50];
    char fed[100];
    char conf[50];

    while (archivo >> ranking) {

        archivo.ignore();

        archivo.getline(pais, 50, ';');
        archivo.getline(dt, 50, ';');
        archivo.getline(fed, 100, ';');
        archivo.getline(conf, 50, ';');

        archivo >> gf; archivo.ignore();
        archivo >> gc; archivo.ignore();
        archivo >> g; archivo.ignore();
        archivo >> e; archivo.ignore();
        archivo >> p;

        archivo.ignore();

        equipos[cantidad] = Equipo(26);

        equipos[cantidad].setNombre(pais);
        equipos[cantidad].setDirector(dt);
        equipos[cantidad].setFederacion(fed);
        equipos[cantidad].setConfederacion(conf);
        equipos[cantidad].setRanking(ranking);
        equipos[cantidad].setEstadisticas(gf, gc, g, e, p);

        for (int i = 0; i < 26; i++) {
            char nombre[50] = "nombre";

            int j = 6;
            int num = i + 1;

            if (num >= 10) {
                nombre[j++] = '0' + (num / 10);
            }
            nombre[j++] = '0' + (num % 10);
            nombre[j] = '\0';

            equipos[cantidad].agregarJugador(i, nombre, i + 1);
        }

        int total = equipos[cantidad].getGolesAFavor();
        int base = total / 26;
        int extra = total % 26;

        for (int i = 0; i < 26; i++) {
            for (int j = 0; j < base; j++) {
                equipos[cantidad].getJugador(i).anotarGol();
            }
        }

        for (int i = 0; i < extra; i++) {
            equipos[cantidad].getJugador(i).anotarGol();
        }

        cantidad++;
    }

    archivo.close();
}

void Equipo::sumarGolAFavor() {
    golesAFavor++;
}

void Equipo::sumarGolEnContra() {
    golesEnContra++;
}

void Equipo::sumarGanado() {
    partidosGanados++;
}

void Equipo::sumarEmpatado() {
    partidosEmpatados++;
}

void Equipo::sumarPerdido() {
    partidosPerdidos++;
}

void Equipo::guardarDatos(Equipo equipos[], int cantidad) {
    ofstream archivo("salida.csv");

    if (!archivo.is_open()) {
        cout << "Error al guardar datos\n";
        return;
    }

    for (int i = 0; i < cantidad; i++) {
        archivo << equipos[i].getNombre() << ","
                << equipos[i].getConfederacion() << ","
                << equipos[i].getRanking() << ","
                << equipos[i].getGolesAFavor() << ","
                << equipos[i].getGolesEnContra() << ","
                << equipos[i].getGanados() << ","
                << equipos[i].getEmpatados() << ","
                << equipos[i].getPerdidos()
                << endl;
    }

    archivo.close();
}