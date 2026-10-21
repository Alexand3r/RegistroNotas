#include "Eliminar.h"
#include "../Base/Json.h"
#include <iostream>

using namespace std;

bool eliminarNota(vector<Registro>& listaNotas, const string& nombreArchivo) {
    // 1. Validar si la lista está vacía
    if (listaNotas.empty()) {
        cout << "No hay registros para eliminar.\n";
        return false;
    }

    // 2. Pedir el ID a buscar
    string idBuscado;
    cout << "Ingrese el ID del registro a eliminar: ";
    getline(cin, idBuscado);

    // 3. Buscar el índice del registro en el vector
    int idx = -1;
    for (size_t i = 0; i < listaNotas.size(); i++) {
        if (listaNotas[i].id == idBuscado) {
            idx = static_cast<int>(i);
            break;
        }
    }

    // 4. Si no se encuentra, avisar claramente
    if (idx == -1) {
        cout << "Error: No existe un registro con el ID " << idBuscado << ".\n";
        return false;
    }

    // 5. Mostrar los datos del registro encontrado antes de borrar
    const Registro& r = listaNotas[idx];
    cout << "\n--- Registro Encontrado ---\n";
    cout << "ID            : " << r.id << "\n";
    cout << "Estudiante    : " << r.estudiante << "\n";
    cout << "Tipo Evaluacion: " << r.tipoEvaluacion << "\n";
    cout << "Nota          : " << r.nota << "\n";
    cout << "Ponderacion   : " << r.ponderacion << "\n";

    // 6. Validación crítica exigida por la rúbrica: Confirmación (s/n) antes de borrar
    char respuesta;
    cout << "\nDesea eliminar este registro? (s/n): ";
    cin >> respuesta;
    cin.ignore(); // Limpiar el salto de línea pendiente en el buffer

    if (respuesta == 'n' || respuesta == 'N') {
        cout << "Eliminacion cancelada.\n";
        return false;
    }

    if (respuesta != 's' && respuesta != 'S') {
        cout << "Opcion invalida. No se elimino nada.\n";
        return false;
    }

    // 7. Borrar del vector y actualizar el archivo JSON inmediatamente
    listaNotas.erase(listaNotas.begin() + idx);
    guardarJSON(listaNotas, nombreArchivo);
    
    cout << "Registro eliminado y guardado correctamente.\n";
    return true;
}