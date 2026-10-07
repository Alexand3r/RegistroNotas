#include "Crear.h"
#include <iostream>

using namespace std;

// ---------- Funciones auxiliares de validación ----------

static bool existeId(const vector<RegistroNota>& registros, int id) {
    for (const auto& r : registros) {
        if (r.id == id) return true;
    }
    return false;
}

static bool textoVacio(const string& s) {
    return s.find_first_not_of(" \t") == string::npos;
}

// Convierte texto a int. Falla si hay letras ("12abc") o está vacío.
static bool aEntero(const string& s, int& valor) {
    try {
        size_t pos;
        valor = stoi(s, &pos);
        return pos == s.size();
    } catch (...) {
        return false;
    }
}

// Convierte texto a double. Falla si hay letras.
static bool aDecimal(const string& s, double& valor) {
    try {
        size_t pos;
        valor = stod(s, &pos);
        return pos == s.size();
    } catch (...) {
        return false;
    }
}

// ---------- Lógica principal ----------

bool crearNota(vector<RegistroNota>& registros,
               const RegistroNota& nuevo,
               string& error) {
    if (nuevo.id <= 0) {
        error = "El ID debe ser un entero positivo.";
        return false;
    }
    if (existeId(registros, nuevo.id)) {
        error = "Ya existe un registro con el ID " + to_string(nuevo.id) + ".";
        return false;
    }
    if (textoVacio(nuevo.estudiante)) {
        error = "El nombre del estudiante no puede estar vacio.";
        return false;
    }
    if (textoVacio(nuevo.curso)) {
        error = "El curso no puede estar vacio.";
        return false;
    }
    if (textoVacio(nuevo.tipoEvaluacion)) {
        error = "El tipo de evaluacion no puede estar vacio.";
        return false;
    }
    if (nuevo.nota < 0 || nuevo.nota > 100) {
        error = "La nota debe estar entre 0 y 100.";
        return false;
    }
    if (nuevo.peso <= 0 || nuevo.peso > 100) {
        error = "El peso debe ser mayor que 0 y maximo 100.";
        return false;
    }

    registros.push_back(nuevo);
    return true;
}

// ---------- Interacción con el usuario ----------

void solicitarNuevaNota(vector<RegistroNota>& registros) {
    RegistroNota r;
    string entrada, error;

    cout << "ID: ";
    getline(cin, entrada);
    if (!aEntero(entrada, r.id)) {
        cout << "Error: el ID debe ser un numero entero.\n";
        return;
    }

    cout << "Estudiante: ";
    getline(cin, r.estudiante);

    cout << "Curso: ";
    getline(cin, r.curso);

    cout << "Tipo de evaluacion: ";
    getline(cin, r.tipoEvaluacion);

    cout << "Nota: ";
    getline(cin, entrada);
    if (!aDecimal(entrada, r.nota)) {
        cout << "Error: la nota debe ser un numero, no texto.\n";
        return;
    }

    cout << "Peso: ";
    getline(cin, entrada);
    if (!aDecimal(entrada, r.peso)) {
        cout << "Error: el peso debe ser un numero, no texto.\n";
        return;
    }

    if (crearNota(registros, r, error)) {
        cout << "Nota registrada correctamente.\n";
    } else {
        cout << "Error: " << error << "\n";
    }
}