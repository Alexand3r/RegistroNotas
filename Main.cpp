#include <iostream>
#include <vector>
#include <string>

// Incluimos los headers de todos los módulos del equipo
#include "Base/Registro.h"
#include "Base/Json.h"
#include "Crear/Crear.h"
#include "Leer/Leer.h"
#include "Actualizar/Actualizar.h"
#include "Eliminar/Eliminar.h"

using namespace std;

// Nombre del archivo físico donde persistirán los datos
const string NOMBRE_ARCHIVO = "datos.json";

// Función auxiliar para limpiar la pantalla de la consola de forma compatible
static void limpiarPantalla() {
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #else
        system("clear");
    #endif
}

int main() {
    // 1. Al iniciar, cargamos los datos existentes desde el archivo JSON a la memoria (Vector)
    vector<Registro> listaNotas = cargarJSON(NOMBRE_ARCHIVO);
    
    int opcion = 0;
    string entrada;

    do {
        // Pausa breve para que el usuario pueda leer los mensajes antes de redibujar el menú
        cout << "\nPresione ENTER para continuar...";
        getline(cin, entrada);
        limpiarPantalla();

        // 2. Menú principal numerado exigido por la rúbrica
        cout << "===========================================\n";
        cout << "    SISTEMA DE REGISTRO DE NOTAS - GRUPO 4 \n";
        cout << "===========================================\n";
        cout << "1. Registrar nueva nota (Crear)\n";
        cout << "2. Listar todas las notas\n";
        cout << "3. Buscar nota por ID\n";
        cout << "4. Actualizar nota existente\n";
        cout << "5. Eliminar nota\n";
        cout << "6. Calcular promedio final ponderado (Regla Grupo 4)\n";
        cout << "7. Salir del programa\n";
        cout << "===========================================\n";
        cout << "Seleccione una opcion (1-7): ";

        getline(cin, entrada);

        // Validación segura para evitar que letras colapsen el menú
        try {
            opcion = stoi(entrada);
        } catch (...) {
            opcion = -1; 
        }

        switch (opcion) {
            case 1:
                solicitarNuevaNota(listaNotas, NOMBRE_ARCHIVO);
                break;
            case 2:
                listarNotas(listaNotas);
                break;
            case 3: {
                string idBuscado;
                cout << "Ingrese el ID a buscar: ";
                getline(cin, idBuscado);
                buscarPorId(listaNotas, idBuscado);
                break;
            }
            case 4:
                actualizarNota(listaNotas, NOMBRE_ARCHIVO);
                break;
            case 5:
                eliminarNota(listaNotas, NOMBRE_ARCHIVO);
                break;
            case 6:
                mostrarPromedioFinal(listaNotas);
                break;
            case 7:
                cout << "\nSaliendo del sistema. Guardando cambios finales...\n";
                guardarJSON(listaNotas, NOMBRE_ARCHIVO);
                cout << "¡Programa finalizado con exito!\n";
                break;
            default:
                cout << "\n[Error] Opcion invalida. Ingrese un numero entre 1 y 7.\n";
        }

    } while (opcion != 7);

    return 0;
}