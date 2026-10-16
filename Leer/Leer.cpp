#include "Leer.h"
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

static const int ANCHO_TABLA = 96;

static void imprimirEncabezado() {
    cout << left
         << setw(10) << "Carnet"
         << setw(20) << "Estudiante"
         << setw(18) << "Carrera"
         << setw(18) << "Curso"
         << setw(14) << "Evaluacion"
         << right
         << setw(8)  << "Nota"
         << setw(8)  << "Pond." << "\n";
    cout << string(ANCHO_TABLA, '-') << "\n";
}

static void imprimirFila(const Registrodenotas& r) {
    cout << left
         << setw(10) << r.carnet
         << setw(20) << r.estudiante.substr(0, 19)
         << setw(18) << r.Carrera.substr(0, 17)
         << setw(18) << r.curso.substr(0, 17)
         << setw(14) << r.tipoEvaluacion.substr(0, 13)
         << right << fixed << setprecision(2)
         << setw(8)  << r.nota
         << setw(8)  << r.ponderacion << "\n";
}

void listarNotas(const vector<Registrodenotas>& registros) {
    if (registros.empty()) {
        cout << "No hay notas registradas.\n";
        return;
    }
    imprimirEncabezado();
    for (const auto& r : registros) {
        imprimirFila(r);
    }
    cout << string(ANCHO_TABLA, '-') << "\n"
         << "Total: " << registros.size() << " registro(s)\n";
}

void buscarPorCarnet(const vector<Registrodenotas>& registros, int carnet) {
    for (const auto& r : registros) {
        if (r.carnet == carnet) {
            imprimirEncabezado();
            imprimirFila(r);
            return;
        }
    }
    cout << "No se encontro ninguna nota con el carnet " << carnet << ".\n";
}