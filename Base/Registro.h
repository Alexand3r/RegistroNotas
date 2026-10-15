#ifndef REGISTRO_H
#define REGISTRO_H //Bibliotecas a utilizar
#include <string>

struct Registro //Conjunto de datos relacionados que agregare en un sola variable
{
  std::string id;
  std::string estudiante;
  std::string tipoEvaluacion;
  double nota;
  double ponderacion;

};
#endif
