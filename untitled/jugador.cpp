#include <iostream>
#include "Jugador.h"

using namespace std;

Jugador::Jugador() {
    nombre[0] = '\0';
    numeroCamiseta = 0;
    goles = 0;
    asistencias = 0;
    faltas = 0;
    partidosJugados = 0;
    tarjetasAmarillas = 0;
    tarjetasRojas = 0;
    minutosJugados = 0;
}

Jugador::Jugador(const Jugador& otro) {
    int i = 0;
    while (otro.nombre[i] != '\0' && i < 49) {
        nombre[i] = otro.nombre[i];
        i++;
    }
    nombre[i] = '\0';

    numeroCamiseta = otro.numeroCamiseta;
    goles = otro.goles;
    asistencias = otro.asistencias;
    faltas = otro.faltas;
    partidosJugados = otro.partidosJugados;
    tarjetasAmarillas = otro.tarjetasAmarillas;
    tarjetasRojas = otro.tarjetasRojas;
    minutosJugados = otro.minutosJugados;
}

Jugador& Jugador::operator=(const Jugador& otro) {
    if (this == &otro) return *this;

    int i = 0;
    while (otro.nombre[i] != '\0' && i < 49) {
        nombre[i] = otro.nombre[i];
        i++;
    }
    nombre[i] = '\0';

    numeroCamiseta = otro.numeroCamiseta;
    goles = otro.goles;
    asistencias = otro.asistencias;
    faltas = otro.faltas;
    partidosJugados = otro.partidosJugados;
    tarjetasAmarillas = otro.tarjetasAmarillas;
    tarjetasRojas = otro.tarjetasRojas;
    minutosJugados = otro.minutosJugados;

    return *this;
}

// setters
void Jugador::setNombre(const char* n) {
    int i = 0;
    while (n[i] != '\0' && i < 49) {
        nombre[i] = n[i];
        i++;
    }
    nombre[i] = '\0';
}

void Jugador::setNumeroCamiseta(int num) {
    numeroCamiseta = num;
}

// acciones
void Jugador::anotarGol() { goles++; }
void Jugador::darAsistencia() { asistencias++; }
void Jugador::cometerFalta() { faltas++; }
void Jugador::jugarPartido() { partidosJugados++; }
void Jugador::jugarMinutos(int minutos) { minutosJugados += minutos; }
void Jugador::recibirAmarilla() { tarjetasAmarillas++; }
void Jugador::recibirRoja() { tarjetasRojas++; }

// getters
const char* Jugador::getNombre() { return nombre; }
int Jugador::getNumeroCamiseta() { return numeroCamiseta; }
int Jugador::getGoles() { return goles; }
int Jugador::getAsistencias() { return asistencias; }
int Jugador::getFaltas() { return faltas; }
int Jugador::getPartidos() { return partidosJugados; }
int Jugador::getAmarillas() { return tarjetasAmarillas; }
int Jugador::getRojas() { return tarjetasRojas; }
int Jugador::getMinutos() { return minutosJugados; }