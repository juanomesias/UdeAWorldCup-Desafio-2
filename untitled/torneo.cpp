#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include "Torneo.h"

using namespace std;

Torneo::Torneo() {
    equipos = new Equipo[48];
    cantidadEquipos = 0;

    for (int i = 0; i < 12; i++) {
        grupos[i] = Grupo('A' + i);
    }
    for (int i = 0; i < 32; i++) r16Clasificados[i] = nullptr;
    for (int i = 0; i < 8; i++) r8Clasificados[i] = nullptr;
    for (int i = 0; i < 4; i++) r4Clasificados[i] = nullptr;

    campeon = nullptr;
    subcampeon = nullptr;
    tercerLugar = nullptr;
    cuartoLugar = nullptr;

    srand(time(0));
}

Torneo::~Torneo() {
    delete[] equipos;
}

int Torneo::generarRandom(int min, int max) {
    return min + rand() % (max - min + 1);
}

void Torneo::simularLlave(Equipo* entrada[], int n, Equipo* ganadores[], const char* nombreFase) {
    cout << "\n===== " << nombreFase << " =====" << endl;
    int diaBase = 0;
    if (strcmp(nombreFase, "R8") == 0) diaBase = 16;
    else if (strcmp(nombreFase, "QF") == 0) diaBase = 20;
    else diaBase = 25; // fallback por si acaso

    for (int i = 0; i < n; i += 2) {
        int partidoIndex = i / 2;
        int dia = diaBase + (partidoIndex / 4);
        char fecha[20];
        sprintf(fecha, "%02d/07/2026", dia);
        Partido* p = new Partido(
            entrada[i],
            entrada[i + 1],
            fecha,
            "nombreSede"
            );

        p->setArbitros(
            "codArbitro1",
            "codArbitro2",
            "codArbitro3"
            );
        p->simular(true);
        p->mostrarResultado();
        cout << "Hora: 00:00" << endl;
        p->mostrarGoleadores();
        ganadores[i / 2] = p->getGanador();
        delete p;
    }
}



void Torneo::ordenarPorRanking() {
    for (int i = 0; i < cantidadEquipos - 1; i++) {
        for (int j = 0; j < cantidadEquipos - i - 1; j++) {
            if (equipos[j].getRanking() > equipos[j + 1].getRanking()) {
                Equipo temp = equipos[j];
                equipos[j] = equipos[j + 1];
                equipos[j + 1] = temp;
            }
        }
    }
}

bool Torneo::esValidoGrupo(int grupoIndex, Equipo* equipo) {
    int conteoUEFA = 0;
    for (int i = 0; i < 4; i++) {
        Equipo* e = grupos[grupoIndex].getEquipo(i);

        if (e == nullptr) continue;

        if (strcmp(e->getConfederacion(), equipo->getConfederacion()) == 0) {
            if (strcmp(equipo->getConfederacion(), "UEFA") == 0) {
                conteoUEFA++;
            } else {
                return false;
            }
        }
    }

    if (strcmp(equipo->getConfederacion(), "UEFA") == 0 && conteoUEFA >= 2) {
        return false;
    }
    return true;
}

bool Torneo::mismoGrupo(Equipo* a, Equipo* b) {
    for (int i = 0; i < 12; i++) {
        int encontrados = 0;

        for (int j = 0; j < 4; j++) {
            Equipo* e = grupos[i].getEquipo(j);

            if (e == a || e == b) {
                encontrados++;
            }
        }

        if (encontrados == 2) return true;
    }
    return false;
}

void Torneo::cargarDatos() {
    Equipo::cargarEquipos(equipos, cantidadEquipos);
    for (int i = 0; i < cantidadEquipos; i++) {
        equipos[i].reiniciarEstadisticasTorneo();
    }
}

void Torneo::formarGrupos() {
    ordenarPorRanking();

    Equipo* bombos[4][12];
    bool usados[4][12] = {false};

    int index = 0;

    for (int i = 0; i < cantidadEquipos; i++) {
        if (strcmp(equipos[i].getNombre(), "United States") == 0) {

            Equipo temp = equipos[0];
            equipos[0] = equipos[i];
            equipos[i] = temp;

            break;
        }
    }


    for (int b = 0; b < 4; b++) {
        for (int i = 0; i < 12; i++) {
            bombos[b][i] = &equipos[index++];
        }
    }


    for (int g = 0; g < 12; g++) {

        for (int b = 0; b < 4; b++) {

            int intentos = 0;

            while (true) {
                int r = generarRandom(0, 11);

                if (usados[b][r]) continue;

                Equipo* candidato = bombos[b][r];

                if (esValidoGrupo(g, candidato)) {
                    grupos[g].agregarEquipo(b, candidato);
                    usados[b][r] = true;
                    break;
                }

                if (++intentos > 100) {
                    grupos[g].agregarEquipo(b, candidato);
                    usados[b][r] = true;
                    break;
                }
            }
        }
    }
}

void Torneo::simularTorneo() {
    cout << "===== FASE DE GRUPOS =====" << endl;

    for (int i = 0; i < 12; i++) {
        cout << endl << "Grupo " << char('A' + i) << endl;

        grupos[i].generarPartidos();
        grupos[i].simularGrupo();
        grupos[i].calcularTabla();
    }
}

void Torneo::mostrarGrupos() {
    cout << endl << "===== GRUPOS CONFORMADOS =====" << endl;
    for (int i = 0; i < 12; i++) {
        grupos[i].mostrarGrupo();
        cout << endl;
    }
}

void Torneo::mostrarTablas() {
    cout << "\n===== TABLAS DE GRUPOS =====" << endl;

    for (int i = 0; i < 12; i++) {

        cout << "\nGrupo " << char('A' + i) << endl;
        cout << "Pos | Equipo            | Pts | PJ | G | E | P | GF | GC | DG" << endl;

        for (int j = 0; j < 4; j++) {

            Equipo* e = grupos[i].getEquipoEnPosicion(j);

            int pj = e->getGanadosTorneo()
                     + e->getEmpatadosTorneo()
                     + e->getPerdidosTorneo();

            cout << j + 1 << "   | "
                 << e->getNombre();

            int len = 20 - strlen(e->getNombre());
            for (int k = 0; k < len; k++) cout << " ";

            cout << "| "
                 << e->getPuntosTorneo() << "   | "
                 << pj << "  | "
                 << e->getGanadosTorneo() << " | "
                 << e->getEmpatadosTorneo() << " | "
                 << e->getPerdidosTorneo() << " | "
                 << e->getGolesAFavorTorneo() << "  | "
                 << e->getGolesEnContraTorneo() << "  | "
                 << e->getDiferenciaGolesTorneo()
                 << endl;
        }
    }
}

void Torneo::ordenarEquipos(Equipo* arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {

            if (arr[j]->getPuntos() < arr[j + 1]->getPuntos()) {
                Equipo* temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void Torneo::clasificarR16(Equipo* clasificados[]) {

    Equipo* terceros[12];

    int idx = 0;

    for (int i = 0; i < 12; i++) {
        clasificados[idx++] = grupos[i].getEquipoEnPosicion(0);
    }

    for (int i = 0; i < 12; i++) {
        clasificados[idx++] = grupos[i].getEquipoEnPosicion(1);
    }

    for (int i = 0; i < 12; i++) {
        terceros[i] = grupos[i].getEquipoEnPosicion(2);
    }

    ordenarEquipos(terceros, 12);

    for (int i = 0; i < 8; i++) {
        clasificados[idx++] = terceros[i];
    }
}

void Torneo::generarR16(Equipo* clasificados[], Partido* partidosR16[]) {

    int idx = 0;
    int diaBase = 10;
    for (int i = 0; i < 32; i += 2) {
        Equipo* a = clasificados[i];
        Equipo* b = clasificados[i + 1];
        if (mismoGrupo(a, b)) {
            for (int j = i + 2; j < 32; j++) {
                if (!mismoGrupo(a, clasificados[j])) {
                    Equipo* temp = clasificados[i + 1];
                    clasificados[i + 1] = clasificados[j];
                    clasificados[j] = temp;
                    b = clasificados[i + 1];
                    break;
                }
            }
        }

        int partidoIndex = idx;
        int dia = diaBase + (partidoIndex / 4);
        char fecha[20];
        sprintf(fecha, "%02d/07/2026", dia);
        partidosR16[idx] = new Partido(a, b, fecha, "nombreSede");
        partidosR16[idx]->setArbitros(
            "codArbitro1",
            "codArbitro2",
            "codArbitro3"
            );
        idx++;
    }
}

void Torneo::simularEliminatorias() {
    Equipo* clasificados[32];
    Partido* partidosR16[16];

    clasificarR16(clasificados);
    generarR16(clasificados, partidosR16);

    cout << "\n===== R16 =====" << endl;
    for (int i = 0; i < 16; i++) {
        partidosR16[i]->simular(true);
        partidosR16[i]->mostrarResultado();
        partidosR16[i]->mostrarGoleadores();
        r16Clasificados[i] = partidosR16[i]->getGanador();
    }

    Equipo* r8Entrantes[16];
    for (int i = 0; i < 16; i++) {
        r8Entrantes[i] = r16Clasificados[i];
    }

    Equipo* cuartos[8];
    simularLlave(r8Entrantes, 16, cuartos, "R8");
    for (int i = 0; i < 8; i++) {
        r8Clasificados[i] = cuartos[i];
    }

    Equipo* semis[4];
    simularLlave(cuartos, 8, semis, "QF");
    for (int i = 0; i < 4; i++) {
        r4Clasificados[i] = semis[i];
    }

    Equipo* finalistas[2];
    Equipo* perdedoresSF[2];

    cout << "\n===== SF =====" << endl;
    for (int i = 0; i < 4; i += 2) {
        Partido* p = new Partido(semis[i], semis[i + 1], "23/07/2026", "nombreSede");
        p->setArbitros("codArbitro1", "codArbitro2", "codArbitro3");
        p->simular(true);

        p->mostrarResultado();
        p->mostrarGoleadores();

        finalistas[i / 2] = p->getGanador();
        perdedoresSF[i / 2] = (p->getGanador() == semis[i]) ? semis[i + 1] : semis[i];

        delete p;
    }

    cout << "\n===== TERCER PUESTO =====" << endl;
    Partido* tercerPuesto = new Partido(perdedoresSF[0], perdedoresSF[1], "26/07/2026", "nombreSede");
    tercerPuesto->setArbitros("codArbitro1", "codArbitro2", "codArbitro3");
    tercerPuesto->simular(true);
    tercerPuesto->mostrarResultado();
    tercerPuesto->mostrarGoleadores();

    tercerLugar = tercerPuesto->getGanador();
    cuartoLugar = (tercerLugar == perdedoresSF[0]) ? perdedoresSF[1] : perdedoresSF[0];

    cout << "\n===== FINAL =====" << endl;
    Partido* final = new Partido(finalistas[0], finalistas[1], "26/07/2026", "nombreSede");
    final->setArbitros("codArbitro1", "codArbitro2", "codArbitro3");
    final->simular(true);
    final->mostrarResultado();
    final->mostrarGoleadores();

    campeon = final->getGanador();
    subcampeon = (campeon == finalistas[0]) ? finalistas[1] : finalistas[0];

    delete tercerPuesto;
    delete final;
}

void Torneo::mostrarEstadisticasFinales() {
    cout << "\n===== ESTADISTICAS FINALES DEL TORNEO =====" << endl;

    if (campeon != nullptr && subcampeon != nullptr && tercerLugar != nullptr && cuartoLugar != nullptr) {
        cout << "1. Puesto 1: " << campeon->getNombre() << endl;
        cout << "2. Puesto 2: " << subcampeon->getNombre() << endl;
        cout << "3. Puesto 3: " << tercerLugar->getNombre() << endl;
        cout << "4. Puesto 4: " << cuartoLugar->getNombre() << endl;
    }

    if (campeon != nullptr) {
        Jugador* mejor = &campeon->getJugador(0);
        for (int i = 1; i < campeon->getCantidadJugadores(); i++) {
            Jugador* act = &campeon->getJugador(i);
            if (act->getGoles() > mejor->getGoles()) {
                mejor = act;
            }
        }

        cout << "Maximo goleador del campeon: "
             << mejor->getNombre()
             << " | Camiseta: " << mejor->getNumeroCamiseta()
             << " | Goles: " << mejor->getGoles()
             << endl;
    }

    Jugador* top1 = nullptr;
    Jugador* top2 = nullptr;
    Jugador* top3 = nullptr;

    for (int i = 0; i < cantidadEquipos; i++) {
        for (int j = 0; j < equipos[i].getCantidadJugadores(); j++) {
            Jugador* act = &equipos[i].getJugador(j);

            if (top1 == nullptr || act->getGoles() > top1->getGoles()) {
                top3 = top2;
                top2 = top1;
                top1 = act;
            } else if (top2 == nullptr || act->getGoles() > top2->getGoles()) {
                top3 = top2;
                top2 = act;
            } else if (top3 == nullptr || act->getGoles() > top3->getGoles()) {
                top3 = act;
            }
        }
    }

    cout << "Top 3 goleadores de la copa:" << endl;
    if (top1) cout << "1) " << top1->getNombre() << " | #" << top1->getNumeroCamiseta() << " | Goles: " << top1->getGoles() << endl;
    if (top2) cout << "2) " << top2->getNombre() << " | #" << top2->getNumeroCamiseta() << " | Goles: " << top2->getGoles() << endl;
    if (top3) cout << "3) " << top3->getNombre() << " | #" << top3->getNumeroCamiseta() << " | Goles: " << top3->getGoles() << endl;

    Equipo* maxEquipo = &equipos[0];
    for (int i = 1; i < cantidadEquipos; i++) {
        if (equipos[i].getGolesAFavor() > maxEquipo->getGolesAFavor()) {
            maxEquipo = &equipos[i];
        }
    }

    cout << "Equipo con mas goles historicos: "
         << maxEquipo->getNombre()
         << " | GF: " << maxEquipo->getGolesAFavor()
         << endl;

    const char* nombresConf[6] = {
        "UEFA", "CONMEBOL", "CONCACAF", "CAF", "AFC", "OFC"
    };

    cout << "Presencia por confederacion:" << endl;
    for (int etapa = 0; etapa < 3; etapa++) {
        int conteo[6] = {0, 0, 0, 0, 0, 0};
        Equipo** arr = nullptr;
        int n = 0;
        const char* nombreEtapa = nullptr;

        if (etapa == 0) {
            arr = r16Clasificados;
            n = 32;
            nombreEtapa = "R16";
        } else if (etapa == 1) {
            arr = r8Clasificados;
            n = 8;
            nombreEtapa = "R8";
        } else {
            arr = r4Clasificados;
            n = 4;
            nombreEtapa = "R4";
        }

        for (int i = 0; i < n; i++) {
            if (arr[i] == nullptr) continue;

            for (int c = 0; c < 6; c++) {
                if (strcmp(arr[i]->getConfederacion(), nombresConf[c]) == 0) {
                    conteo[c]++;
                }
            }
        }

        cout << nombreEtapa << ":" << endl;
        for (int c = 0; c < 6; c++) {
            if (conteo[c] > 0) {
                cout << "  " << nombresConf[c] << ": " << conteo[c] << endl;
            }
        }
    }
}

void Torneo::guardarResultados() {
    Equipo::guardarDatos(equipos, cantidadEquipos);
}