#ifndef EQUIPO_H
#define EQUIPO_H

#include "Jugador.h"

class Equipo {
private:
    char nombre[50];
    char directorTecnico[50];
    char federacion[100];
    char confederacion[50];

    int rankingFIFA;

    int golesAFavor;
    int golesEnContra;
    int partidosGanados;
    int partidosEmpatados;
    int partidosPerdidos;

    Jugador* jugadores;
    int cantidadJugadores;

    void copiarCadena(char* dest, const char* src, int maxLen);

public:
    Equipo();
    Equipo(int n);
    Equipo(const Equipo& otro);
    Equipo& operator=(const Equipo& otro);
    ~Equipo();

    void setNombre(const char* n);
    void setDirector(const char* d);
    void setFederacion(const char* f);
    void setConfederacion(const char* c);
    void setRanking(int r);
    void setEstadisticas(int gf, int gc, int g, int e, int p);

    void sumarGolAFavor();
    void sumarGolEnContra();
    void sumarGanado();
    void sumarEmpatado();
    void sumarPerdido();

    void agregarJugador(int index, const char* nom, int numero);

    Jugador& getJugador(int index);
    int getCantidadJugadores();

    const char* getNombre();
    const char* getDirector();
    const char* getFederacion();
    const char* getConfederacion();
    int getRanking();

    int getGolesAFavor();
    int getGolesEnContra();
    int getGanados();
    int getEmpatados();
    int getPerdidos();

    int getPuntos();
    int getDiferenciaGoles();

    static void cargarEquipos(Equipo equipos[], int& cantidad);
    static void guardarDatos(Equipo equipos[], int cantidad);

    void mostrarInfo();
    void mostrarJugadores();
};

#endif