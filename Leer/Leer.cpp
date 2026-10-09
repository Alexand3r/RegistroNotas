#include "Leer.h"
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// Imprime la fila de títulos de la tabla
static void imprimirEncabezado() {
    cout << left
         << setw(8)  << "ID"
         << setw(25) << "Estudiante"
         << setw(20) << "Curso"
         << setw(18) << "Evaluacion"
         << right
         << setw(8)  << "Nota"
         << setw(8)  << "Peso" << "\n";
    cout << string(87, '-') << "\n";
}

// Imprime un registro como una fila de la tabla
static void imprimirFila(const Registro& r) {
    cout << left
         << setw(8)  << r.id
         << setw(25) << r.estudiante
         << setw(20) << r.curso
         << setw(18) << r.tipoEvaluacion
         << right << fixed << setprecision(2)
         << setw(8)  << r.nota
         << setw(8)  << r.ponderacion << "\n";
}

// Muestra todas las notas en formato de tabla
void listarNotas(const vector<Registro>& listaNotas) {
    if (listaNotas.empty()) {
        cout << "No hay notas registradas.\n";
        return;
    }
    imprimirEncabezado();
    for (const Registro& r : listaNotas) {
        imprimirFila(r);
    }
}

// Busca un registro por ID y lo muestra
void buscarPorID(const vector<Registro>& listaNotas, int id) {
    for (const Registro& r : listaNotas) {
        if (r.id == id) {
            imprimirEncabezado();
            imprimirFila(r);
            return;
        }
    }
    cout << "No se encontro ningun registro con ID " << id << ".\n";
}
