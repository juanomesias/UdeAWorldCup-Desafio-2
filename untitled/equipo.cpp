#include <iostream>
#include <fstream>
#include "Equipo.h"

    using namespace std;
//  FUNCION AUXILIAR PRIVADA
//  Copia cadenas caracter a caracter sin usar strcpy

void Equipo::copiarCadena(char* dest, const char* src, int maxLen) {
    int i = 0;
    while (src[i] != '\0' && i < maxLen - 1) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

//  CONSTRUCTOR POR DEFECTO
//  Necesario para poder declarar: Equipo equipos[48]

Equipo::Equipo() {
    nombre[0]          = '\0';
    directorTecnico[0] = '\0';
    federacion[0]      = '\0';
    confederacion[0]   = '\0';

    rankingFIFA        = 0;
    golesAFavor        = 0;
    golesEnContra      = 0;
    partidosGanados    = 0;
    partidosEmpatados  = 0;
    partidosPerdidos   = 0;

    cantidadJugadores  = 0;
    jugadores          = nullptr;
}
//  CONSTRUCTOR CON CANTIDAD DE JUGADORES
//  Uso: Equipo e(26);

Equipo::Equipo(int n) {
    nombre[0]          = '\0';
    directorTecnico[0] = '\0';
    federacion[0]      = '\0';
    confederacion[0]   = '\0';

    rankingFIFA        = 0;
    golesAFavor        = 0;
    golesEnContra      = 0;
    partidosGanados    = 0;
    partidosEmpatados  = 0;
    partidosPerdidos   = 0;

    cantidadJugadores  = n;
    jugadores          = new Jugador[n];
}

//  CONSTRUCTOR DE COPIA
//  Evita que dos objetos compartan el mismo puntero jugadores

Equipo::Equipo(const Equipo& otro) {
    copiarCadena(nombre,          otro.nombre,          50);
    copiarCadena(directorTecnico, otro.directorTecnico, 50);
    copiarCadena(federacion,      otro.federacion,      100);
    copiarCadena(confederacion,   otro.confederacion,   50);

    rankingFIFA        = otro.rankingFIFA;
    golesAFavor        = otro.golesAFavor;
    golesEnContra      = otro.golesEnContra;
    partidosGanados    = otro.partidosGanados;
    partidosEmpatados  = otro.partidosEmpatados;
    partidosPerdidos   = otro.partidosPerdidos;
    cantidadJugadores  = otro.cantidadJugadores;

    if (cantidadJugadores > 0) {
        jugadores = new Jugador[cantidadJugadores];
        for (int i = 0; i < cantidadJugadores; i++)
            jugadores[i] = otro.jugadores[i];
    } else {
        jugadores = nullptr;
    }
}

//  OPERADOR DE ASIGNACION

Equipo& Equipo::operator=(const Equipo& otro) {
    if (this == &otro) return *this;  // proteccion contra autoasignacion

    // Liberar memoria anterior ANTES de pedir nueva
    delete[] jugadores;
    jugadores = nullptr;

    copiarCadena(nombre,          otro.nombre,          50);
    copiarCadena(directorTecnico, otro.directorTecnico, 50);
    copiarCadena(federacion,      otro.federacion,      100);
    copiarCadena(confederacion,   otro.confederacion,   50);

    rankingFIFA        = otro.rankingFIFA;
    golesAFavor        = otro.golesAFavor;
    golesEnContra      = otro.golesEnContra;
    partidosGanados    = otro.partidosGanados;
    partidosEmpatados  = otro.partidosEmpatados;
    partidosPerdidos   = otro.partidosPerdidos;
    cantidadJugadores  = otro.cantidadJugadores;

    if (cantidadJugadores > 0) {
        jugadores = new Jugador[cantidadJugadores];
        for (int i = 0; i < cantidadJugadores; i++)
            jugadores[i] = otro.jugadores[i];
    } else {
        jugadores = nullptr;
    }

    return *this;
}

//  DESTRUCTOR

Equipo::~Equipo() {
    delete[] jugadores;
    jugadores = nullptr;
}


//  SETTERS BASICOS

void Equipo::setNombre(const char* n)        { copiarCadena(nombre,          n, 50);  }
void Equipo::setDirector(const char* d)      { copiarCadena(directorTecnico, d, 50);  }
void Equipo::setFederacion(const char* f)    { copiarCadena(federacion,      f, 100); }
void Equipo::setConfederacion(const char* c) { copiarCadena(confederacion,   c, 50);  }

void Equipo::setRanking(int r) {
    rankingFIFA = r;
}

void Equipo::setEstadisticas(int gf, int gc, int g, int e, int p) {
    golesAFavor       = gf;
    golesEnContra     = gc;
    partidosGanados   = g;
    partidosEmpatados = e;
    partidosPerdidos  = p;
}

//  ACTUALIZAR ESTADISTICAS PARTIDO A PARTIDO
//  Estos metodos los llama la clase Partido al terminar
//  cada encuentro para mantener las estadisticas al dia

void Equipo::sumarGolAFavor()   { golesAFavor++;       }
void Equipo::sumarGolEnContra() { golesEnContra++;     }
void Equipo::sumarGanado()      { partidosGanados++;   }
void Equipo::sumarEmpatado()    { partidosEmpatados++; }
void Equipo::sumarPerdido()     { partidosPerdidos++;  }

//  GESTION DE JUGADORES

void Equipo::agregarJugador(int index, const char* nom, int numero) {
    if (index >= 0 && index < cantidadJugadores) {
        jugadores[index].setNombre(nom);
        jugadores[index].setNumeroCamiseta(numero);
    }
}

Jugador& Equipo::getJugador(int index) {
    return jugadores[index];
}

int Equipo::getCantidadJugadores() {
    return cantidadJugadores;
}

//  GETTERS

const char* Equipo::getNombre()        { return nombre;           }
const char* Equipo::getDirector()      { return directorTecnico;  }
const char* Equipo::getFederacion()    { return federacion;       }
const char* Equipo::getConfederacion() { return confederacion;    }
int         Equipo::getRanking()       { return rankingFIFA;      }
int         Equipo::getGolesAFavor()   { return golesAFavor;      }
int         Equipo::getGolesEnContra() { return golesEnContra;    }
int         Equipo::getGanados()       { return partidosGanados;  }
int         Equipo::getEmpatados()     { return partidosEmpatados;}
int         Equipo::getPerdidos()      { return partidosPerdidos; }

//  CALCULOS DERIVADOS

// Puntos segun reglamento FIFA: victoria=3, empate=1, derrota=0
int Equipo::getPuntos() {
    return (partidosGanados * 3) + (partidosEmpatados * 1);
}

// Diferencia de goles: criterio de desempate en tabla de posiciones
int Equipo::getDiferenciaGoles() {
    return golesAFavor - golesEnContra;
}

//  CARGAR EQUIPOS DESDE CSV
//
//  Formato esperado de cada linea en equipos.csv:
//  ranking,nombre,directorTecnico,federacion,confederacion,gf,gc,g,e,p
//
//  Ejemplo:
//  1,Argentina,Lionel Scaloni,AFA,CONMEBOL,100,35,30,10,5
//
//  IMPORTANTE: se usa while(archivo >> ranking) en vez de
//  while(!archivo.eof()) para evitar que el ultimo equipo
//  se procese dos veces (bug clasico de eof en C++)

void Equipo::cargarEquipos(Equipo equipos[], int& cantidad) {
    ifstream archivo("equipos.csv");

    if (!archivo.is_open()) {
        cout << "Error: no se pudo abrir equipos.csv" << endl;
        cout << "Verifique que el archivo este en la carpeta build." << endl;
        cantidad = 0;
        return;
    }

    cantidad = 0;

    int  ranking, gf, gc, g, e, p;
    char nom[50], dt[50], fed[100], conf[50];

    while (archivo >> ranking) {
        archivo.ignore();  // ignorar la coma despues del ranking

        archivo.getline(nom,  50,  ',');
        archivo.getline(dt,   50,  ',');
        archivo.getline(fed,  100, ',');
        archivo.getline(conf, 50,  ',');

        archivo >> gf; archivo.ignore();
        archivo >> gc; archivo.ignore();
        archivo >> g;  archivo.ignore();
        archivo >> e;  archivo.ignore();
        archivo >> p;
        archivo.ignore();  // salto de linea al final del registro

        // Crear equipo con 26 jugadores (plantilla real de un mundial)
        equipos[cantidad] = Equipo(26);

        equipos[cantidad].setNombre(nom);
        equipos[cantidad].setDirector(dt);
        equipos[cantidad].setFederacion(fed);
        equipos[cantidad].setConfederacion(conf);
        equipos[cantidad].setRanking(ranking);
        equipos[cantidad].setEstadisticas(gf, gc, g, e, p);

        // --- Crear jugadores con estadisticas iniciales ---
        // Los goles historicos se distribuyen uniformemente entre los 26
        // El resto de la division se reparte entre los primeros jugadores
        int golesPorJugador = gf / 26;
        int golesExtra      = gf % 26;

        for (int i = 0; i < 26; i++) {
            // Construir nombre "Jugador 1", "Jugador 2" ... "Jugador 26"
            // manualmente sin usar sprintf ni itoa
            char nombreJug[20];
            nombreJug[0] = 'J'; nombreJug[1] = 'u'; nombreJug[2] = 'g';
            nombreJug[3] = 'a'; nombreJug[4] = 'd'; nombreJug[5] = 'o';
            nombreJug[6] = 'r'; nombreJug[7] = ' ';

            int num = i + 1;
            int len = 8;
            if (num >= 10) {
                nombreJug[len++] = '0' + (num / 10);
            }
            nombreJug[len++] = '0' + (num % 10);
            nombreJug[len]   = '\0';

            equipos[cantidad].agregarJugador(i, nombreJug, i + 1);

            // Asignar goles historicos al jugador
            int golesEste = golesPorJugador + (i < golesExtra ? 1 : 0);
            for (int j = 0; j < golesEste; j++) {
                equipos[cantidad].getJugador(i).anotarGol();
            }
        }

        cantidad++;
    }

    archivo.close();
    cout << "Se cargaron " << cantidad << " equipos desde equipos.csv" << endl;
}

/* GUARDAR DATOS ACTUALIZADOS EN ARCHIVO TXT
 Se llama al finalizar la simulacion para persistir
las estadisticas generadas durante el torneo*/

void Equipo::guardarDatos(Equipo equipos[], int cantidad) {
    ofstream archivo("equipos_actualizados.txt");

    if (!archivo.is_open()) {
        cout << "Error: no se pudo crear equipos_actualizados.txt" << endl;
        return;
    }

    for (int i = 0; i < cantidad; i++) {
        archivo << "========================================" << endl;
        archivo << "Equipo:        " << equipos[i].getNombre()        << endl;
        archivo << "Director:      " << equipos[i].getDirector()      << endl;
        archivo << "Federacion:    " << equipos[i].getFederacion()    << endl;
        archivo << "Confederacion: " << equipos[i].getConfederacion() << endl;
        archivo << "Ranking FIFA:  " << equipos[i].getRanking()       << endl;
        archivo << "Puntos:        " << equipos[i].getPuntos()        << endl;
        archivo << "GF: "  << equipos[i].getGolesAFavor()
                << "  GC: " << equipos[i].getGolesEnContra()
                << "  DG: " << equipos[i].getDiferenciaGoles()        << endl;
        archivo << "G: "   << equipos[i].getGanados()
                << "  E: " << equipos[i].getEmpatados()
                << "  P: " << equipos[i].getPerdidos()                << endl;

        archivo << "Jugadores:" << endl;
        for (int j = 0; j < equipos[i].getCantidadJugadores(); j++) {
            Jugador& jug = equipos[i].getJugador(j);
            archivo << "  #"  << jug.getNumeroCamiseta()
                    << " "    << jug.getNombre()
                    << " | Goles: "     << jug.getGoles()
                    << " | Asist: "     << jug.getAsistencias()
                    << " | Faltas: "    << jug.getFaltas()
                    << " | Amarillas: " << jug.getAmarillas()
                    << " | Rojas: "     << jug.getRojas()
                    << " | Minutos: "   << jug.getMinutos()
                    << " | Partidos: "  << jug.getPartidos()
                    << endl;
        }
    }

    archivo.close();
    cout << "Datos guardados en equipos_actualizados.txt" << endl;
}

//Info consola//
void Equipo::mostrarInfo() {
    cout << "========================================" << endl;
    cout << "Equipo:        " << nombre          << endl;
    cout << "Director:      " << directorTecnico << endl;
    cout << "Federacion:    " << federacion      << endl;
    cout << "Confederacion: " << confederacion   << endl;
    cout << "Ranking FIFA:  " << rankingFIFA     << endl;
    cout << "Puntos:        " << getPuntos()     << endl;
    cout << "GF: "  << golesAFavor
         << "  GC: " << golesEnContra
         << "  DG: " << getDiferenciaGoles()     << endl;
    cout << "G: "   << partidosGanados
         << "  E: " << partidosEmpatados
         << "  P: " << partidosPerdidos          << endl;
}

void Equipo::mostrarJugadores() {
    cout << "Jugadores de " << nombre << ":" << endl;
    for (int i = 0; i < cantidadJugadores; i++) {
        cout << "  #" << jugadores[i].getNumeroCamiseta()
        << " "   << jugadores[i].getNombre()
        << " | Goles: "  << jugadores[i].getGoles()
        << " | Asist: "  << jugadores[i].getAsistencias()
        << " | Min: "    << jugadores[i].getMinutos()
        << endl;
    }
}
