#ifndef CREAR_H
#define CREAR_H

#include <string>
#include <vector>
#include "../Base/Registro.h"

// Registra una nota en la lista en memoria. Devuelve true si se guardó con éxito.
bool crearNota(std::vector<Registro>& registros, const Registro& nuevo, std::string& error);

// Pide los datos por consola, valida, agrega y guarda en el archivo JSON.
void solicitarNuevaNota(std::vector<Registro>& registros, const std::string& nombreArchivo);

#endif