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
    //CNST//
    Jugador();

    //Constructor de copia//(Ultima actualizacion)
    Jugador(const Jugador& otro);

    //Operador de asignacion//Ultima actualizacion)
    Jugador& operator=(const Jugador& otro);

    //STTNMB//
    void setNombre(const char* n);
    void setNumeroCamiseta(int num);


    //METDACTESTA//
    void anotarGol();
    void recibirAmarilla();
    void recibirRoja();
    void jugarMinutos(int minutos);
    void darAsistencia();
    void cometerFalta();
    void jugarPartido();

    // Gttrs//
    const char* getNombre();
    int getGoles();
    int getAmarillas();
    int getRojas();
    int getMinutos();
    int getNumeroCamiseta();
    int getAsistencias();
    int getFaltas();
    int getPartidos();


    //Mstrinf//
    void mostrarDatos();


};

#endif


