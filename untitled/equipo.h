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

public:
    Equipo();
    Equipo(int n);
    ~Equipo();

    void setNombre(const char* n);
    void setDirector(const char* d);
    void setFederacion(const char* f);
    void setConfederacion(const char* c);
    void setRanking(int r);
    void setEstadisticas(int gf, int gc, int g, int e, int p);

    void agregarJugador(int index, const char* nombre, int numero);
    Jugador& getJugador(int index);
    int getCantidadJugadores();

    const char* getNombre();
    int getRanking();
    const char* getDirector();
    const char* getFederacion();
    const char* getConfederacion();
    int getGolesAFavor();
    int getGolesEnContra();
    int getGanados();
    int getEmpatados();
    int getPerdidos();

    void mostrarInfo();
};

#endif