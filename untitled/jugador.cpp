#include "jugador.h"
#include <cstring>
#include <iostream>

using namespace std;

jugador::jugador() {
    nombre = new char[1];
    nombre[0] = '\0';

    apellido = new char[1];
    apellido[0] = '\0';

    numeroCamiseta = 0;
}

jugador::jugador(const jugador& otro) {
    if (otro.nombre) {
        nombre = new char[strlen(otro.nombre) + 1];
        strcpy(nombre, otro.nombre);
    } else {
        nombre = new char[1];
        nombre[0] = '\0';
    }

    if (otro.apellido) {
        apellido = new char[strlen(otro.apellido) + 1];
        strcpy(apellido, otro.apellido);
    } else {
        apellido = new char[1];
        apellido[0] = '\0';
    }

    numeroCamiseta = otro.numeroCamiseta;
    stats = otro.stats;
}

jugador::~jugador() {
    delete[] nombre;
    delete[] apellido;
}

jugador& jugador::operator=(const jugador& otro) {
    if (this != &otro) {
        delete[] nombre;
        delete[] apellido;

        if (otro.nombre) {
            nombre = new char[strlen(otro.nombre) + 1];
            strcpy(nombre, otro.nombre);
        } else {
            nombre = new char[1];
            nombre[0] = '\0';
        }

        if (otro.apellido) {
            apellido = new char[strlen(otro.apellido) + 1];
            strcpy(apellido, otro.apellido);
        } else {
            apellido = new char[1];
            apellido[0] = '\0';
        }

        numeroCamiseta = otro.numeroCamiseta;
        stats = otro.stats;
    }
    return *this;
}

// GETTERS
const char* jugador::getNombre() const { return nombre; }
const char* jugador::getApellido() const { return apellido; }
int jugador::getNumeroCamiseta() const { return numeroCamiseta; }
estadisticasjugador& jugador::getStats() { return stats; }

// SETTERS
void jugador::setNombre(const char* valor) {
    delete[] nombre;
    nombre = new char[strlen(valor) + 1];
    strcpy(nombre, valor);
}

void jugador::setApellido(const char* valor) {
    delete[] apellido;
    apellido = new char[strlen(valor) + 1];
    strcpy(apellido, valor);
}

void jugador::setNumeroCamiseta(int valor) {
    numeroCamiseta = valor;
}

// FUNCIONES DEL DIAGRAMA
void jugador::agregarGol() {
    stats.goles++;
}

void jugador::agregarMinutos(int m) {
    stats.minutos += m;
}

void jugador::agregarTarjetaAmarilla() {
    stats.amarillas++;
}

void jugador::agregarTarjetaRoja() {
    stats.rojas++;
}

void jugador::agregarFalta() {
    stats.faltas++;
}

// OPERADORES
bool jugador::operator==(const jugador& otro) const {
    return numeroCamiseta == otro.numeroCamiseta;
}

ostream& operator<<(ostream& os, const jugador& j) {
    os << "Camiseta: " << j.numeroCamiseta
       << " | " << j.nombre << " " << j.apellido
       << " | " << j.stats;
    return os;
}