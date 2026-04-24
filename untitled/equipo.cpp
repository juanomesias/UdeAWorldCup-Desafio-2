#include "equipo.h"
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

equipo::equipo() {
    pais = new char[1]; pais[0] = '\0';
    confederacion = new char[1]; confederacion[0] = '\0';
    directorTecnico = new char[1]; directorTecnico[0] = '\0';

    rankingFIFA = 0;
    plantilla = nullptr;
    numJugadores = 0;
    puntos = 0;
    diferenciaGoles = 0;
}

equipo::~equipo() {
    delete[] pais;
    delete[] confederacion;
    delete[] directorTecnico;
    delete[] plantilla;
}

equipo::equipo(const equipo& otro) {
    pais = new char[strlen(otro.pais)+1];
    strcpy(pais, otro.pais);

    confederacion = new char[strlen(otro.confederacion)+1];
    strcpy(confederacion, otro.confederacion);

    directorTecnico = new char[strlen(otro.directorTecnico)+1];
    strcpy(directorTecnico, otro.directorTecnico);

    rankingFIFA = otro.rankingFIFA;
    puntos = otro.puntos;
    diferenciaGoles = otro.diferenciaGoles;
    numJugadores = otro.numJugadores;

    plantilla = new jugador[numJugadores];
    for(int i=0;i<numJugadores;i++)
        plantilla[i] = otro.plantilla[i];

    statsHistoricas = otro.statsHistoricas;
}

equipo& equipo::operator=(const equipo& otro) {
    if(this != &otro){
        delete[] pais;
        delete[] confederacion;
        delete[] directorTecnico;
        delete[] plantilla;

        pais = new char[strlen(otro.pais)+1];
        strcpy(pais, otro.pais);

        confederacion = new char[strlen(otro.confederacion)+1];
        strcpy(confederacion, otro.confederacion);

        directorTecnico = new char[strlen(otro.directorTecnico)+1];
        strcpy(directorTecnico, otro.directorTecnico);

        rankingFIFA = otro.rankingFIFA;
        puntos = otro.puntos;
        diferenciaGoles = otro.diferenciaGoles;
        numJugadores = otro.numJugadores;

        plantilla = new jugador[numJugadores];
        for(int i=0;i<numJugadores;i++)
            plantilla[i] = otro.plantilla[i];

        statsHistoricas = otro.statsHistoricas;
    }
    return *this;
}

// SETTERS
void equipo::setPais(const char* v){
    delete[] pais;
    pais = new char[strlen(v)+1];
    strcpy(pais,v);
}

void equipo::setConfederacion(const char* v){
    delete[] confederacion;
    confederacion = new char[strlen(v)+1];
    strcpy(confederacion,v);
}

void equipo::setDirectorTecnico(const char* v){
    delete[] directorTecnico;
    directorTecnico = new char[strlen(v)+1];
    strcpy(directorTecnico,v);
}

void equipo::setRankingFIFA(int v){ rankingFIFA = v; }

// AGREGAR JUGADOR
void equipo::agregarJugador(const jugador& j){
    jugador* nuevo = new jugador[numJugadores+1];

    for(int i=0;i<numJugadores;i++)
        nuevo[i] = plantilla[i];

    nuevo[numJugadores] = j;

    delete[] plantilla;
    plantilla = nuevo;
    numJugadores++;
}

// GENERAR PLANTILLA
void equipo::generarPlantilla(){
    delete[] plantilla;

    numJugadores = 26;
    plantilla = new jugador[numJugadores];

    for(int i=0;i<numJugadores;i++){
        char nombre[20];
        char apellido[20];

        sprintf(nombre,"Jugador%d",i+1);
        sprintf(apellido,"Apellido%d",i+1);

        plantilla[i].setNombre(nombre);
        plantilla[i].setApellido(apellido);
        plantilla[i].setNumeroCamiseta(i+1);
    }
}


void equipo::cargarDesdeCSV(const char* archivo){
    ifstream file(archivo);
    if(!file) return;

    string linea;
    getline(file, linea); // encabezado

    if(getline(file, linea)){
        stringstream ss(linea);
        string campo;

        getline(ss, campo, ',');
        rankingFIFA = stoi(campo);

        getline(ss, campo, ',');
        setPais(campo.c_str());

        getline(ss, campo, ',');
        setDirectorTecnico(campo.c_str());

        getline(ss, campo, ','); // federacion

        getline(ss, campo, ',');
        setConfederacion(campo.c_str());

        getline(ss, campo, ',');
        statsHistoricas.golesFavor = stoi(campo);

        getline(ss, campo, ',');
        statsHistoricas.golesContra = stoi(campo);

        getline(ss, campo, ',');
        statsHistoricas.partidosGanados = stoi(campo);

        getline(ss, campo, ',');
        statsHistoricas.partidosEmpatados = stoi(campo);

        getline(ss, campo, ',');
        statsHistoricas.partidosPerdidos = stoi(campo);
    }

    file.close();
}

// OPERADORES
bool equipo::operator<(const equipo& otro) const{
    return rankingFIFA < otro.rankingFIFA;
}

ostream& operator<<(ostream& os, const equipo& e){
    os<<"Pais: "<<e.pais
       <<" | Ranking: "<<e.rankingFIFA
       <<" | Confederacion: "<<e.confederacion
       <<" | DT: "<<e.directorTecnico
       <<" | Puntos: "<<e.puntos<<"\n";
    return os;
}