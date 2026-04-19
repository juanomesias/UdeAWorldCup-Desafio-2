#include <iostream>
#include "Jugador.h"

using namespace std;

//CNST//
Jugador::Jugador() {
    nombre[0] = '\0';
    goles = 0;
    tarjetasAmarillas = 0;
    tarjetasRojas = 0;
    minutosJugados = 0;
}

//STTNMB//
void Jugador::setNombre(const char* n) {
    int i = 0;
    while (n[i] != '\0' && i < 49) {
        nombre[i] = n[i];
        i++;
    }
    nombre[i] = '\0';
}

//MTDEST//
void Jugador::anotarGol() {
    goles++;
}

void Jugador::recibirAmarilla() {
    tarjetasAmarillas++;
}

void Jugador::recibirRoja() {
    tarjetasRojas++;
}

void Jugador::jugarMinutos(int minutos) {
    minutosJugados += minutos;
}

//Gttrs//
const char* Jugador::getNombre() {
    return nombre;
}

int Jugador::getGoles() {
    return goles;
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

//Mstrdts//
void Jugador::mostrarDatos() {
    cout << "Nombre: " << nombre << endl;
    cout << "Goles: " << goles << endl;
    cout << "Amarillas: " << tarjetasAmarillas << endl;
    cout << "Rojas: " << tarjetasRojas << endl;
    cout << "Minutos jugados: " << minutosJugados << endl;
}