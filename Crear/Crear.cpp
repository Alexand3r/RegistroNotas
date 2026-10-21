#include "Crear.h"
#include "../Base/Json.h"
#include <iostream>

using namespace std;

// Función auxiliar para verificar si el ID ya existe en el vector
static bool existeId(const vector<Registro>& registros, const string& id) {
    for (const auto& r : registros) {
        if (r.id == id) return true;
    }
    return false;
}

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

bool crearNota(vector<Registro>& registros, const Registro& nuevo, string& error) {
    // Validación crítica exigida por la rúbrica: ID no vacío y no duplicado[cite: 1]
    if (textoVacio(nuevo.id)) {
        error = "El ID no puede estar vacio.";
        return false;
    }
    if (existeId(registros, nuevo.id)) {
        error = "Ya existe un registro con el ID " + nuevo.id + ".";
        return false;
    }
    if (textoVacio(nuevo.estudiante)) {
        error = "El nombre del estudiante no puede estar vacio.";
        return false;
    }
    if (textoVacio(nuevo.tipoEvaluacion)) {
        error = "El tipo de evaluacion no puede estar vacio.";
        return false;
    }
    // Validación de rangos lógicos
    if (nuevo.nota < 0 || nuevo.nota > 100) {
        error = "La nota debe estar entre 0 y 100.";
        return false;
    }
    if (nuevo.ponderacion <= 0 || nuevo.ponderacion > 100) {
        error = "La ponderacion debe ser mayor que 0 y maximo 100.";
        return false;
    }

    registros.push_back(nuevo);
    return true;
}

void solicitarNuevaNota(vector<Registro>& registros, const string& nombreArchivo) {
    Registro r;
    string entrada, error;

    cout << "\n--- Registrar Nueva Nota ---\n";
    cout << "ID (clave unica): ";
    getline(cin, r.id);

    cout << "Estudiante: ";
    getline(cin, r.estudiante);

    cout << "Tipo de evaluacion (ej. Parcial, Tarea): ";
    getline(cin, r.tipoEvaluacion);

    cout << "Nota (0-100): ";
    getline(cin, entrada);
    if (!aDecimal(entrada, r.nota)) {
        cout << "Error: la nota debe ser un numero valido.\n";
        return;
    }

    cout << "Peso/Ponderacion (ej. 20 para 20%): ";
    getline(cin, entrada);
    if (!aDecimal(entrada, r.ponderacion)) {
        cout << "Error: la ponderacion debe ser un numero valido.\n";
        return;
    }

    // Intentamos agregar la nota usando la lógica validada
    if (crearNota(registros, r, error)) {
        // Guardado automático en el archivo JSON
        guardarJSON(registros, nombreArchivo);
        cout << "Nota registrada y guardada correctamente en el archivo.\n";
    } else {
        cout << "Error: " << error << "\n";
    }
}