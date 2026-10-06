#ifndef JSON_H
#define JSON_H
#include <vector>
#include <string>
#include "Registro.h"

//Declaro las dos funciones que necesitaran para los archivos
void guardarJSON(const vector<Registro>& listaNotas, const string& nombreArchivo);

vector<Registro> cargarJSON(const string& nombreArchivo);
#endif