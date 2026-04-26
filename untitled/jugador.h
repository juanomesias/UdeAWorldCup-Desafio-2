#ifndef JUGADOR_H
#define JUGADOR_H

class Jugador {
private:
    char nombre[50];
    int numeroCamiseta;

    int goles;
    int asistencias;
    int faltas;
    int partidosJugados;
    int tarjetasAmarillas;
    int tarjetasRojas;
    int minutosJugados;

public:
    Jugador();
    Jugador(const Jugador& otro);
    Jugador& operator=(const Jugador& otro);

    void setNombre(const char* n);
    void setNumeroCamiseta(int num);

    void anotarGol();
    void darAsistencia();
    void cometerFalta();
    void jugarPartido();
    void jugarMinutos(int minutos);
    void recibirAmarilla();
    void recibirRoja();

    const char* getNombre();
    int getNumeroCamiseta();
    int getGoles();
    int getAsistencias();
    int getFaltas();
    int getPartidos();
    int getAmarillas();
    int getRojas();
    int getMinutos();
};

#endif