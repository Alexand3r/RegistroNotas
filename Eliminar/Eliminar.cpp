#include "Eliminar.h"
#include "../Base/Json.h"
#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

bool eliminarNota(vector<Registro>& listaNotas,
                  const string& nombreArchivo) {

    if (listaNotas.empty()) {
        cout << "No hay registros para eliminar.\n";
        return false;
    }

    string id;

    cout << "ID del registro a eliminar: ";
    getline(cin, id);

    int idx = -1;

    for (size_t i = 0; i < listaNotas.size(); i++) {
        if (listaNotas[i].id == id) {
            idx = static_cast<int>(i);
            break;
        }
    }

    if (idx == -1) {
        cout << "No existe un registro con ID "
             << id << ".\n";
        return false;
    }

    const Registro& r = listaNotas[idx];

    cout << "\nRegistro seleccionado:\n";
    cout << "ID: " << r.id << "\n";
    cout << "Estudiante: " << r.estudiante << "\n";
    cout << "Tipo de evaluacion: " << r.tipoEvaluacion << "\n";
    cout << "Nota: " << r.nota << "\n";
    cout << "Ponderacion: " << r.ponderacion << "\n";

    cout << "\nDesea eliminar este registro? (s/n): ";

    string confirmacion;
    getline(cin, confirmacion);

    if (confirmacion.size() != 1) {
        cout << "Entrada invalida. No se elimino nada.\n";
        return false;
    }

    char respuesta = static_cast<char>(
        tolower(static_cast<unsigned char>(confirmacion[0]))
    );

    if (respuesta == 'n') {
        cout << "Eliminacion cancelada.\n";
        return false;
    }

    if (respuesta != 's') {
        cout << "Opcion invalida. No se elimino nada.\n";
        return false;
    }

    listaNotas.erase(listaNotas.begin() + idx);

    guardarJSON(listaNotas, nombreArchivo);

    cout << "Registro eliminado correctamente.\n";
    return true;
}
