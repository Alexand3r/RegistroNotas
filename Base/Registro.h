#ifndef REGISTRO_H
#define REGISTRO_H
#include <iostream> //Bibliotecas a utilizar
#include <string>
using namespace std;

struct Registrodenotas //Conjunto de datos relacionados que agregare en un sola variable
{
  int carnet;
  string estudiante;
  string Carrera;
  string curso;
  string tipoEvaluacion;
  double nota;
  double ponderacion;

};
#endif
