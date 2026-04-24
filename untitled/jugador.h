#ifndef JUGADOR_H
#define JUGADOR_H

#include <iostream>

using namespace std;

// Estructura de estadísticas del jugador
struct estadisticasjugador {
    int goles = 0;
    int minutos = 0;
    int asistencias = 0;
    int amarillas = 0;
    int rojas = 0;
    int faltas = 0;
    int partidos = 0;
};

// Para poder imprimir stats con <<
ostream& operator<<(ostream& os, const estadisticasjugador& e);

class jugador {
private:
    char* nombre;
    char* apellido;
    int numeroCamiseta;
    estadisticasjugador stats;

public:
    // Regla de los 3
    jugador();
    jugador(const jugador& otro);
    ~jugador();
    jugador& operator=(const jugador& otro);

    // Getters
    const char* getNombre() const;
    const char* getApellido() const;
    int getNumeroCamiseta() const;
    estadisticasjugador& getStats();

    // Setters
    void setNombre(const char* valor);
    void setApellido(const char* valor);
    void setNumeroCamiseta(int valor);

    // Funciones del diagrama
    void agregarGol();
    void agregarMinutos(int m);
    void agregarTarjetaAmarilla();
    void agregarTarjetaRoja();
    void agregarFalta();

    // Operadores
    bool operator==(const jugador& otro) const;
    friend ostream& operator<<(ostream& os, const jugador& j);
};

#endif