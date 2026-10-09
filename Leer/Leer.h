#ifndef LEER_H
#define LEER_H
#include <vector>
#include "../Base/Registro.h"

void listarNotas(const std::vector<Registro>& listaNotas);
void buscarPorID(const std::vector<Registro>& listaNotas, int id);

#endif
