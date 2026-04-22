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

    // Funcion auxiliar interna para copiar cadenas sin usar strcpy
    void copiarCadena(char* dest, const char* src, int maxLen);

public:

    Equipo();                               // Constructor por defecto (necesario para arrays)
    Equipo(int n);                          // Constructor con cantidad de jugadores
    Equipo(const Equipo& otro);             // Constructor de copia
    Equipo& operator=(const Equipo& otro);  // Operador de asignacion
    ~Equipo();                              // Destructor

    //SETTERS//
    void setNombre(const char* n);
    void setDirector(const char* d);
    void setFederacion(const char* f);
    void setConfederacion(const char* c);
    void setRanking(int r);
    void setEstadisticas(int gf, int gc, int g, int e, int p);

    //Actualizar estadisticas partido a partido//
    void sumarGolAFavor();
    void sumarGolEnContra();
    void sumarGanado();
    void sumarEmpatado();
    void sumarPerdido();

    //JUGADORES//
    void     agregarJugador(int index, const char* nombre, int numero);
    Jugador& getJugador(int index);
    int      getCantidadJugadores();

    //GETTERS//
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

    //PERSISTENCIA//
    static void cargarEquipos(Equipo equipos[], int& cantidad);
    static void guardarDatos(Equipo equipos[], int cantidad);

    //MOSTRAR//
    void mostrarInfo();
    void mostrarJugadores();
};

#endif