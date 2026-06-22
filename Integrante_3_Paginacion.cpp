#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>

using namespace std;

// Estructura necesaria para la prueba
struct Registro {
    int id;
    string categoria, descripcion;
    float monto;
};

// Prototipos
void listarRegistrosPaginados(Registro[], int, string);
void pausaYLimpiar();

int main() {
    // Generar datos de prueba para que el Integrante 3 verifique su paginacion
    const int MAX_REGISTROS = 100;
    Registro historialPrueba[MAX_REGISTROS];
    int contadorPrueba = 0; 

    for(int i = 0; i < 45; i++) {
        historialPrueba[i] = {i+1, "Prueba", "Data generada", 10.5f};
        contadorPrueba++;
    }

    // Ejecucion individual del modulo
    listarRegistrosPaginados(historialPrueba, contadorPrueba, "LISTADO DE PRUEBA");
    
    return 0;
}

void listarRegistrosPaginados(Registro arreglo[], int contador, string titulo) {
    if (contador == 0) {
        system("cls");
        cout << "--- LISTA DE " << titulo << " ---\n\n";
        cout << "Actualmente no hay ningun registro para mostrar.\n";
        pausaYLimpiar();
        return;
    }

    int paginaActual = 0;
    int registrosPorPagina = 20;
    int totalPaginas = (contador + registrosPorPagina - 1) / registrosPorPagina;
    char opcionNavegacion;

    do {
        system("cls");
        cout << "--- LISTA DE " << titulo << " (Pagina " << paginaActual + 1 << " de " << totalPaginas << ") ---\n\n";

        int inicio = paginaActual * registrosPorPagina;
        int fin = inicio + registrosPorPagina;
        if (fin > contador) fin = contador; 

        for (int i = inicio; i < fin; i++) {
            cout << "ID: " << arreglo[i].id 
                 << " | Monto: S/ " << arreglo[i].monto << "\n"
                 << "    Cat: " << arreglo[i].categoria 
                 << " | Desc: " << arreglo[i].descripcion << "\n";
            cout << "------------------------------------------------\n";
        }

        cout << "\nOpciones de navegacion:\n";
        if (paginaActual < totalPaginas - 1) cout << "[D] Avanzar a la siguiente pagina ->\n";
        if (paginaActual > 0)                cout << "[A] <- Volver a la pagina anterior\n";
        cout << "[0] Salir de la lista\n";
        cout << "\nQue deseas hacer?: ";
        
        cin >> opcionNavegacion;
        cin.ignore(256, '\n');
        opcionNavegacion = toupper(opcionNavegacion); 

        if (opcionNavegacion == 'D' && paginaActual < totalPaginas - 1) {
            paginaActual++;
        } else if (opcionNavegacion == 'A' && paginaActual > 0) {
            paginaActual--;
        } else if (opcionNavegacion != '0') {
            cout << "\nOpcion no valida. Intente nuevamente.\n";
            pausaYLimpiar();
        }

    } while (opcionNavegacion != '0');
}

void pausaYLimpiar() {
    cout << "\nPresione Enter para continuar...";
    cin.get(); 
}