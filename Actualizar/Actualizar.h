#ifndef ACTUALIZAR_H
#define ACTUALIZAR_H

#include <vector>
#include <string>
#include "../Base/Registro.h" 

bool actualizarNota(std::vector<Registro>& listaNotas, const std::string& nombreArchivo);

double calcularPromedioFinal(const std::vector<Registro>& listaNotas,
                             const std::string& estudiante,
                             const std::string& curso);

void mostrarPromedioFinal(const std::vector<Registro>& listaNotas);

#endif

