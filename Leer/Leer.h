#ifndef LEER_H
#define LEER_H

#include <vector>
#include <string>
#include "../Base/Registro.h"

// Muestra todos los registros en formato de tabla alineada
void listarNotas(const std::vector<Registro>& registros);

// Busca un registro específico por su ID (string) y lo muestra
void buscarPorId(const std::vector<Registro>& registros, const std::string& idBuscado);

#endif