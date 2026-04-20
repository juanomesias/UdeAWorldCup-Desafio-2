#include <iostream>
#include "Jugador.h"

using namespace std;

//CNST//
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

//STTRS//
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

//MTDOSJUGS//
void Jugador::anotarGol() {
    goles++;
}

void Jugador::darAsistencia() {
    asistencias++;
}

void Jugador::cometerFalta() {
    faltas++;
}

void Jugador::jugarPartido() {
    partidosJugados++;
}

void Jugador::jugarMinutos(int minutos) {
    minutosJugados += minutos;
}

void Jugador::recibirAmarilla() {
    tarjetasAmarillas++;
}

void Jugador::recibirRoja() {
    tarjetasRojas++;
}

//GTTRS//
const char* Jugador::getNombre() {
    return nombre;
}

int Jugador::getNumeroCamiseta() {
    return numeroCamiseta;
}

int Jugador::getGoles() {
    return goles;
}

int Jugador::getAsistencias() {
    return asistencias;
}

int Jugador::getFaltas() {
    return faltas;
}

int Jugador::getPartidos() {
    return partidosJugados;
}

int Jugador::getAmarillas() {
    return tarjetasAmarillas;
}

int Jugador::getRojas() {
    return tarjetasRojas;
}

int Jugador::getMinutos() {
    return minutosJugados;
}

//MSTRDTS//
void Jugador::mostrarDatos() {
    cout << "Nombre: " << nombre << endl;
    cout << "Numero de camiseta: " << numeroCamiseta << endl;

    cout << "Goles: " << goles << endl;
    cout << "Asistencias: " << asistencias << endl;
    cout << "Faltas: " << faltas << endl;
    cout << "Partidos jugados: " << partidosJugados << endl;

    cout << "Tarjetas amarillas: " << tarjetasAmarillas << endl;
    cout << "Tarjetas rojas: " << tarjetasRojas << endl;

    cout << "Minutos jugados: " << minutosJugados << endl;
}