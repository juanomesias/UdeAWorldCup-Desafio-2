#ifndef JUGADOR_H
#define JUGADOR_H

class Jugador {
private:
    char nombre[50];
    int goles;
    int tarjetasAmarillas;
    int tarjetasRojas;
    int minutosJugados;

public:
    //CNST//
    Jugador();

    //STTNMB//
    void setNombre(const char* n);

    //METDACTESTA//
    void anotarGol();
    void recibirAmarilla();
    void recibirRoja();
    void jugarMinutos(int minutos);


};

#endif