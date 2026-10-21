#include "Leer.h"
#include <iostream>
#include <iomanip>

using namespace std;

// Ancho total de la tabla en consola
static const int ANCHO_TABLA = 76;

static void imprimirEncabezado() {
    cout << left
         << setw(12) << "ID"
         << setw(22) << "Estudiante"
         << setw(22) << "Evaluacion"
         << right
         << setw(10) << "Nota"
         << setw(10) << "Pond." << "\n";
    cout << string(ANCHO_TABLA, '-') << "\n";
}

static void imprimirFila(const Registro& r) {
    // Usamos .substr por seguridad para que si un texto es muy largo no rompa la tabla
    cout << left
         << setw(12) << r.id.substr(0, 10)
         << setw(22) << r.estudiante.substr(0, 20)
         << setw(22) << r.tipoEvaluacion.substr(0, 20)
         << right << fixed << setprecision(2)
         << setw(10) << r.nota
         << setw(10) << r.ponderacion << "\n";
}

void listarNotas(const vector<Registro>& registros) {
    if (registros.empty()) {
        cout << "No hay notas registradas.\n";
        return;
    }
    imprimirEncabezado();
    for (const auto& r : registros) {
        imprimirFila(r);
    }
    cout << string(ANCHO_TABLA, '-') << "\n"
         << "Total de registros: " << registros.size() << "\n";
}

void buscarPorId(const vector<Registro>& registros, const string& idBuscado) {
    if (registros.empty()) {
        cout << "No hay registros para buscar.\n";
        return;
    }

    bool encontrado = false;
    imprimirEncabezado();
    for (const auto& r : registros) {
        if (r.id == idBuscado) {
            imprimirFila(r);
            encontrado = true;
            break; // Como el ID es único, podemos salir al encontrarlo
        }
    }

    if (!encontrado) {
        // Borramos el encabezado impreso si no hubo resultados para no dejar la tabla flotando vacía
        cout << "No se encontro ningun registro con el ID: " << idBuscado << ".\n";
    } else {
        cout << string(ANCHO_TABLA, '-') << "\n";
    }
}