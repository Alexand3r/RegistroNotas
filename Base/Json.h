#ifndef JSON_H
#define JSON_H
#include <vector>
#include <string>
#include "Registro.h"

//Declaro las dos funciones que necesitaran para los archivos
void guardarJSON(const std::vector<Registro>& listaNotas, const std::string& nombreArchivo);
std::vector<Registro> cargarJSON(const std::string& nombreArchivo);
#endif