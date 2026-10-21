#include "Json.h"
#include "../json.hpp"
#include <fstream>
#include <iostream>
using namespace std;
using json = nlohmann::json;

//nlomann convierte mi struct a formato Json y viceversa.
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Registro, id, estudiante, tipoEvaluacion, nota, ponderacion)

//Esta es la funcion para guardar en Json
void guardarJSON(const std::vector<Registro>& listaNotas, const std::string& nombreArchivo) {
    json j = listaNotas; //Convertimos el vector de C++ (listaNotas) a un objeto JSON de la librería
    ofstream archivoSalida(nombreArchivo); //Abrimos el archivo en modo escritura (std::ofstream)

    if (archivoSalida.is_open()) {  //Verificamos si el archivo se abrió correctamente
        archivoSalida << j.dump(4);  //Escribimos el JSON en el archivo con una sangría de 4 espacios para que sea legible
        archivoSalida.close();
    } else {
        cerr << "Error: No se pudo abrir el archivo para guardar." << std::endl;
    }
}

//Aqui escribo la funcion para cargar el Json
vector<Registro> cargarJSON(const std::string& nombreArchivo) {
    vector<Registro> listaNotas;
    ifstream archivoEntrada(nombreArchivo); // Abrimos en modo lectura

    // Verificamos si el archivo existe y se abrió correctamente
    if (archivoEntrada.is_open()) {
        json j;
        archivoEntrada >> j; // Pasamos el texto del archivo al objeto json
        listaNotas = j.get<std::vector<Registro>>(); // Convertimos de json a nuestro vector de C++
        archivoEntrada.close();
    } else {
        // Si el archivo no existe, no es un error. Simplemente empezamos con una lista vacía.
        cout << "Aviso: No se encontro archivo previo. Se creara uno nuevo al guardar." << std::endl;
    }

    return listaNotas;
}