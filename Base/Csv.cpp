#include <iostream>
#include <fstream>
#include <vector>
#include "Registro.h" 

using namespace std;

void exportarCSV(const vector<Registro>& lista) {
    // Abrimos/creamos el archivo CSV
    ofstream archivo("notas_estudiantes.csv");

    if (!archivo.is_open()) {
        cout << "Error al crear el archivo CSV." << endl;
        return;
    }

    // Escribimos los encabezados de las columnas para Excel
    // Usamos punto y coma para separar 
    archivo << "ID;Estudiante;Tipo Evaluacion;Nota;Ponderacion\n";

    // Recorremos cada registro guardado en la lista
    for (const auto& reg : lista) {
        archivo << reg.id << ";"
                << reg.estudiante << ";"
                << reg.tipoEvaluacion << ";"
                << reg.nota << ";"
                << reg.ponderacion << "\n";
    }

    archivo.close();
    cout << "\n==============================================" << endl;
    cout << " Datos exportados exitosamente a notas_estudiantes.csv " << endl;
    cout << " Puede abrir este archivo directamente " << endl;
    cout << "==============================================\n" << endl;
}