#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>

using namespace std;

// Prototipos
void menuPrincipal();
void menuGastos();
void menuIngresos();
void funcionEnConstruccion(string);
void pausaYLimpiar();

int main() {
    // Prueba individual del Integrante 1
    menuPrincipal();
    return 0;
}

void menuPrincipal() {
    int op;
    do {
        system("cls");
        cout << "========================================\n";
        cout << setw(25) << "MENU PRINCIPAL\n";
        cout << "========================================\n";
        cout << "\t1. Modulo de Gastos\n";
        cout << "\t2. Modulo de Ingresos\n";
        cout << "\t3. Resumen Financiero\n";
        cout << "\t0. Salir del Sistema\n";
        cout << "Escoja una opcion: ";
        cin >> op;
        cin.ignore(256, '\n'); 

        switch (op) {
            case 0: cout << "Saliendo...\n"; return;
            case 1: menuGastos(); break;
            case 2: menuIngresos(); break;
            case 3: funcionEnConstruccion("RESUMEN FINANCIERO"); break;
            default: cout << "ERROR: Opcion invalida.\n"; pausaYLimpiar(); break;
        }
    } while (true);
}

void menuGastos() {
    int op;
    do {
        system("cls");
        cout << "========================================\n";
        cout << setw(25) << "SUBMENU GASTOS\n";
        cout << "========================================\n";
        cout << "\t1. Crear Gasto\n";
        cout << "\t2. Listar Gastos\n";
        cout << "\t3. Modificar Gasto\n";
        cout << "\t4. Eliminar Gasto\n";
        cout << "\t0. Volver al Menu Principal\n";
        cout << "Escoja una opcion: ";
        cin >> op;
        cin.ignore(256, '\n'); 

        switch (op) {
            case 0: return; 
            case 1: funcionEnConstruccion("Crear Gasto"); break;
            case 2: funcionEnConstruccion("Listar Gastos"); break;
            case 3: funcionEnConstruccion("Modificar Gasto"); break;
            case 4: funcionEnConstruccion("Eliminar Gasto"); break;
            default: cout << "ERROR: Opcion invalida.\n"; pausaYLimpiar(); break;
        }
    } while (true);
}

void menuIngresos() {
    int op;
    do {
        system("cls");
        cout << "========================================\n";
        cout << setw(25) << "SUBMENU INGRESOS\n";
        cout << "========================================\n";
        cout << "\t1. Crear Ingreso\n";
        cout << "\t2. Listar Ingresos\n";
        cout << "\t3. Modificar Ingreso\n";
        cout << "\t4. Eliminar Ingreso\n";
        cout << "\t0. Volver al Menu Principal\n";
        cout << "Escoja una opcion: ";
        cin >> op;
        cin.ignore(256, '\n'); 

        switch (op) {
            case 0: return; 
            case 1: funcionEnConstruccion("Crear Ingreso"); break;
            case 2: funcionEnConstruccion("Listar Ingresos"); break;
            case 3: funcionEnConstruccion("Modificar Ingreso"); break;
            case 4: funcionEnConstruccion("Eliminar Ingreso"); break;
            default: cout << "ERROR: Opcion invalida.\n"; pausaYLimpiar(); break;
        }
    } while (true);
}

void funcionEnConstruccion(string nombreModulo) {
    system("cls");
    cout << "========================================\n";
    cout << "   " << nombreModulo << "\n";
    cout << "========================================\n";
    cout << "\n[!] Este modulo estara disponible en la Fase 2.\n";
    pausaYLimpiar();
}

void pausaYLimpiar() {
    cout << "\nPresione Enter para continuar...";
    cin.get(); 
}