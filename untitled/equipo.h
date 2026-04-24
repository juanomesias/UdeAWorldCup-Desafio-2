#ifndef EQUIPO_H
#define EQUIPO_H

#include "jugador.h"

class equipo {
private:
    char* pais;
    char* confederacion;
    char* directorTecnico;

    int rankingFIFA;

    jugador* plantilla;
    int numJugadores;

    int puntos;
    int diferenciaGoles;

    // Stats históricas del equipo
    struct estadisticasequipo {
        int golesFavor = 0;
        int golesContra = 0;
        int partidosGanados = 0;
        int partidosEmpatados = 0;
        int partidosPerdidos = 0;
    } statsHistoricas;

public:
    // Regla de los 3
    equipo();
    equipo(const equipo& otro);
    ~equipo();
    equipo& operator=(const equipo& otro);

    // Getters
    const char* getPais() const;
    const char* getConfederacion() const;
    const char* getDirectorTecnico() const;
    int getRankingFIFA() const;
    jugador* getPlantilla() const;
    int getNumJugadores() const;
    int getPuntos() const;
    int getDiferenciaGoles() const;
    estadisticasequipo& getStatsHistoricas();

    // Setters
    void setPais(const char* valor);
    void setConfederacion(const char* valor);
    void setDirectorTecnico(const char* valor);
    void setRankingFIFA(int valor);
    void setPuntos(int valor);
    void setDiferenciaGoles(int valor);

    // Funciones del diagrama
    void agregarJugador(const jugador& j);
    void generarPlantilla();

    // CSV
    void cargarDesdeCSV(const char* archivo);

    // Operadores
    bool operator<(const equipo& otro) const;
    friend std::ostream& operator<<(std::ostream& os, const equipo& e);
};

#endif
