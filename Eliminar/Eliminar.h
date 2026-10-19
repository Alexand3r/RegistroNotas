#ifndef ELIMINAR_H
#define ELIMINAR_H

#include <string>
#include <vector>
#include "../Base/Registro.h"

bool eliminarNota(std::vector<Registro>& listaNotas,
                  const std::string& nombreArchivo);

#endif
