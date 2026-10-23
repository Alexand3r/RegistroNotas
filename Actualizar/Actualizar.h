#ifndef ACTUALIZAR_H
#define ACTUALIZAR_H

#include <vector>
#include <string>
#include "../Base/Registro.h"

// Modifica un registro existente y guarda los cambios en el archivo JSON
bool actualizarNota(std::vector<Registro>& listaNotas, const std::string& nombreArchivo);

// Calcula el promedio final ponderado por tipo de evaluación para un estudiante
double calcularPromedioFinal(const std::vector<Registro>& listaNotas, const std::string& estudiante);

// Muestra en pantalla el detalle de notas, ponderaciones y el promedio final del estudiante
void mostrarPromedioFinal(const std::vector<Registro>& listaNotas);

#endif