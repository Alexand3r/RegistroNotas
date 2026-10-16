#ifndef LEER_H
#define LEER_H

#include <vector>
#include "../Base/Registro.h"

void listarNotas(const std::vector<Registrodenotas>& registros);
void buscarPorCarnet(const std::vector<Registrodenotas>& registros, int carnet);

#endif