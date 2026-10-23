#include "Actualizar.h"
#include "../Base/Json.h"
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

// Verifica si un texto está vacío o solo tiene espacios
static bool textoVacio(const string& s) {
    return s.find_first_not_of(" \t") == string::npos;
}

// Convierte texto a double de forma segura
static bool aDecimal(const string& s, double& valor) {
    try {
        size_t pos;
        valor = stod(s, &pos);
        return pos == s.size();
    } catch (...) {
        return false;
    }
}

// Busca el índice de un registro por su ID (string)
static int buscarIndicePorId(const vector<Registro>& lista, const string& idBuscado) {
    for (size_t i = 0; i < lista.size(); i++) {
        if (lista[i].id == idBuscado) return static_cast<int>(i);
    }
    return -1;
}

bool actualizarNota(vector<Registro>& listaNotas, const string& nombreArchivo) {
    if (listaNotas.empty()) {
        cout << "No hay registros para actualizar.\n";
        return false;
    }

    string idBuscado;
    cout << "Ingrese el ID del registro a modificar: ";
    getline(cin, idBuscado);

    int idx = buscarIndicePorId(listaNotas, idBuscado);
    if (idx == -1) {
        cout << "Error: No existe un registro con el ID " << idBuscado << ".\n";
        return false;
    }

    Registro r = listaNotas[idx];
    cout << "\n--- Registro Actual ---\n";
    cout << "ID             : " << r.id << "\n";
    cout << "Estudiante     : " << r.estudiante << "\n";
    cout << "Tipo Evaluacion: " << r.tipoEvaluacion << "\n";
    cout << "Nota           : " << fixed << setprecision(2) << r.nota << "\n";
    cout << "Ponderacion    : " << r.ponderacion << "%\n";
    cout << "\n(Presione Enter sin escribir nada para dejar el campo sin cambios)\n\n";

    Registro nuevo = r;
    string entrada;

    cout << "Nuevo estudiante [" << r.estudiante << "]: ";
    getline(cin, entrada);
    if (!entrada.empty()) {
        if (textoVacio(entrada)) {
            cout << "Error: el estudiante no puede estar vacio.\n";
            return false;
        }
        nuevo.estudiante = entrada;
    }

    cout << "Nuevo tipo de evaluacion [" << r.tipoEvaluacion << "]: ";
    getline(cin, entrada);
    if (!entrada.empty()) {
        if (textoVacio(entrada)) {
            cout << "Error: el tipo de evaluacion no puede estar vacio.\n";
            return false;
        }
        nuevo.tipoEvaluacion = entrada;
    }

    cout << "Nueva nota (0-100) [" << r.nota << "]: ";
    getline(cin, entrada);
    if (!entrada.empty()) {
        double n;
        if (!aDecimal(entrada, n) || n < 0 || n > 100) {
            cout << "Error: la nota debe ser un numero entre 0 y 100. No se modifico nada.\n";
            return false;
        }
        nuevo.nota = n;
    }

    cout << "Nueva ponderacion (mayor a 0, maximo 100) [" << r.ponderacion << "]: ";
    getline(cin, entrada);
    if (!entrada.empty()) {
        double p;
        if (!aDecimal(entrada, p) || p <= 0 || p > 100) {
            cout << "Error: la ponderacion debe ser mayor a 0 y maximo 100. No se modifico nada.\n";
            return false;
        }
        nuevo.ponderacion = p;
    }

    listaNotas[idx] = nuevo;
    guardarJSON(listaNotas, nombreArchivo);
    cout << "\nRegistro actualizado y guardado correctamente.\n";
    return true;
}

// Promedio final ponderado por tipo de evaluación
double calcularPromedioFinal(const vector<Registro>& listaNotas, const string& estudiante) {
    double sumaPonderada = 0.0;
    double sumaPesos = 0.0;

    for (const Registro& r : listaNotas) {
        if (r.estudiante == estudiante) {
            sumaPonderada += (r.nota * r.ponderacion);
            sumaPesos += r.ponderacion;
        }
    }

    if (sumaPesos <= 0.0) return -1.0;
    return sumaPonderada / sumaPesos;
}

void mostrarPromedioFinal(const vector<Registro>& listaNotas) {
    if (listaNotas.empty()) {
        cout << "No hay notas registradas.\n";
        return;
    }

    string estudiante;
    cout << "Ingrese el nombre exacto del estudiante: ";
    getline(cin, estudiante);

    double promedio = calcularPromedioFinal(listaNotas, estudiante);
    if (promedio < 0) {
        cout << "No se encontraron notas registradas para el estudiante: " << estudiante << ".\n";
        return;
    }

    double totalPesos = 0.0;
    cout << "\n--- Detalle de Calificaciones para: " << estudiante << " ---\n";
    cout << left << setw(25) << "Evaluacion"
         << right << setw(10) << "Nota"
         << setw(10) << "Pond."
         << setw(12) << "Aporte" << "\n";
    cout << string(57, '-') << "\n";

    for (const Registro& r : listaNotas) {
        if (r.estudiante == estudiante) {
            totalPesos += r.ponderacion;
            double aporte = (r.nota * r.ponderacion) / 100.0;
            cout << left << setw(25) << r.tipoEvaluacion.substr(0, 24)
                 << right << fixed << setprecision(2)
                 << setw(10) << r.nota
                 << setw(10) << r.ponderacion
                 << setw(12) << aporte << "\n";
        }
    }

    cout << string(57, '-') << "\n";
    cout << "Suma total de ponderaciones: " << totalPesos << "%\n";
    if (fabs(totalPesos - 100.0) > 0.01) {
        cout << "Aviso: Las ponderaciones no suman exactamente 100% (Suma actual: " << totalPesos << "%).\n";
    }
    cout << "PROMEDIO FINAL PONDERADO: " << fixed << setprecision(2) << promedio << "\n";
}