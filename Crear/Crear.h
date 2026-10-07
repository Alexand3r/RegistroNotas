#pragma once
#include <string>
#include <vector>

struct RegistroNota {
    int id;
    std::string estudiante;
    std::string curso;
    std::string tipoEvaluacion;
    double nota;
    double peso;
};

// Registra una nota en la lista. Devuelve true si se guardó.
// Si falla, "error" explica el motivo.
bool crearNota(std::vector<RegistroNota>& registros,
               const RegistroNota& nuevo,
               std::string& error);

// Pide los datos por consola y llama a crearNota.
void solicitarNuevaNota(std::vector<RegistroNota>& registros);