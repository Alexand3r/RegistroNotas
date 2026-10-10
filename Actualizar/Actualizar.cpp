#include "Actualizar.h"
#include "../Base/Json.h"  
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

static double& ponderacionDe(Registro& r)             { return r.ponderacion; }
static double  ponderacionDe(const Registro& r)       { return r.ponderacion; }


static bool textoVacio(const string& s) {
    return s.find_first_not_of(" \t") == string::npos;
}

static bool aEntero(const string& s, int& valor) {
    try {
        size_t pos;
        valor = stoi(s, &pos);
        return pos == s.size();
    } catch (...) {
        return false;
    }
}

static bool aDecimal(const string& s, double& valor) {
    try {
        size_t pos;
        valor = stod(s, &pos);
        return pos == s.size();
    } catch (...) {
        return false;
    }
}

static int buscarIndicePorId(const vector<Registro>& lista, int id) {
    for (size_t i = 0; i < lista.size(); i++) {
        if (lista[i].id == id) return (int)i;
    }
    return -1;
}

bool actualizarNota(vector<Registro>& listaNotas, const string& nombreArchivo) {
    string entrada;
    int id;

    cout << "ID del registro a modificar: ";
    getline(cin, entrada);
    if (!aEntero(entrada, id)) {
        cout << "Error: el ID debe ser un numero entero.\n";
        return false;
    }

    int idx = buscarIndicePorId(listaNotas, id);
    if (idx == -1) {
        cout << "Error: no existe un registro con ID " << id << ".\n";
        return false;
    }

    Registro& r = listaNotas[idx];
    cout << "\nRegistro actual:\n"
         << "  Estudiante : " << r.estudiante << "\n"
         << "  Curso      : " << r.curso << "\n"
         << "  Evaluacion : " << r.tipoEvaluacion << "\n"
         << fixed << setprecision(2)
         << "  Nota       : " << r.nota << "\n"
         << "  Ponderacion: " << ponderacionDe(r) << "\n"
         << "\n(Presiona Enter para dejar un campo sin cambios)\n\n";

    Registro nuevo = r;

    cout << "Nuevo estudiante [" << r.estudiante << "]: ";
    getline(cin, entrada);
    if (!entrada.empty()) {
        if (textoVacio(entrada)) { cout << "Error: el estudiante no puede estar vacio.\n"; return false; }
        nuevo.estudiante = entrada;
    }

    cout << "Nuevo curso [" << r.curso << "]: ";
    getline(cin, entrada);
    if (!entrada.empty()) {
        if (textoVacio(entrada)) { cout << "Error: el curso no puede estar vacio.\n"; return false; }
        nuevo.curso = entrada;
    }

    cout << "Nuevo tipo de evaluacion [" << r.tipoEvaluacion << "]: ";
    getline(cin, entrada);
    if (!entrada.empty()) {
        if (textoVacio(entrada)) { cout << "Error: el tipo de evaluacion no puede estar vacio.\n"; return false; }
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

    cout << "Nueva ponderacion (mayor que 0, maximo 100) [" << ponderacionDe(r) << "]: ";
    getline(cin, entrada);
    if (!entrada.empty()) {
        double p;
        if (!aDecimal(entrada, p) || p <= 0 || p > 100) {
            cout << "Error: la ponderacion debe ser mayor que 0 y maximo 100. No se modifico nada.\n";
            return false;
        }
        ponderacionDe(nuevo) = p;
    }

    r = nuevo;                           
    guardarJSON(listaNotas, nombreArchivo); 
    cout << "\nRegistro actualizado correctamente.\n";
    return true;
}

double calcularPromedioFinal(const vector<Registro>& listaNotas,
                             const string& estudiante,
                             const string& curso) {
    double sumaPonderada = 0.0;
    double sumaPesos = 0.0;

    for (const Registro& r : listaNotas) {
        if (r.estudiante == estudiante && r.curso == curso) {
            sumaPonderada += r.nota * ponderacionDe(r);
            sumaPesos += ponderacionDe(r);
        }
    }

    if (sumaPesos <= 0.0) return -1.0;  
    return sumaPonderada / sumaPesos;
}

void mostrarPromedioFinal(const vector<Registro>& listaNotas) {
    string estudiante, curso;

    cout << "Estudiante: ";
    getline(cin, estudiante);
    cout << "Curso: ";
    getline(cin, curso);

    double promedio = calcularPromedioFinal(listaNotas, estudiante, curso);
    if (promedio < 0) {
        cout << "No hay notas registradas para ese estudiante en ese curso.\n";
        return;
    }

    double totalPesos = 0.0;
    cout << "\nDetalle de " << estudiante << " - " << curso << ":\n";
    cout << left << setw(22) << "Evaluacion"
         << right << setw(8) << "Nota"
         << setw(10) << "Pond."
         << setw(12) << "Aporte" << "\n";
    cout << string(52, '-') << "\n";

    for (const Registro& r : listaNotas) {
        if (r.estudiante == estudiante && r.curso == curso) {
            totalPesos += ponderacionDe(r);
            cout << left << setw(22) << r.tipoEvaluacion
                 << right << fixed << setprecision(2)
                 << setw(8) << r.nota
                 << setw(10) << ponderacionDe(r)
                 << setw(12) << (r.nota * ponderacionDe(r) / 100.0) << "\n";
        }
    }
    cout << string(52, '-') << "\n";
    cout << "Suma de ponderaciones: " << totalPesos << "%\n";
    if (fabs(totalPesos - 100.0) > 0.01) {
        cout << "Aviso: las ponderaciones no suman 100%; el promedio se calcula con la suma actual.\n";
    }
    cout << "PROMEDIO FINAL PONDERADO: " << fixed << setprecision(2) << promedio << "\n";
}
