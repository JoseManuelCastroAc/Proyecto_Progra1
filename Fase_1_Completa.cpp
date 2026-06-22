#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>

using namespace std;

// Estructura basica para la prueba
struct Registro {
    int id;
    string categoria, descripcion;
    float monto;
};

const int MAX_REGISTROS = 100;
Registro historialGastos[MAX_REGISTROS];
int contadorGastos = 0; 
Registro historialIngresos[MAX_REGISTROS];
int contadorIngresos = 0;

// ==========================================
// PROTOTIPOS
// ==========================================
bool sistemaLogin(); 
void menuPrincipal(); 
void menuGastos(); 
void menuIngresos(); 
void resumenFinanciero(); 
void listarRegistrosPaginados(Registro[], int, string); 
void funcionEnConstruccion(string); 
void pausaYLimpiar();

// ==========================================
// MAIN (INTEGRACION GRUPAL)
// ==========================================
int main() {
    // 1. Integrante 2: Login 
    if (!sistemaLogin()) {
        return 0; 
    }

    // Generamos datos falsos solo para probar la integracion de la vista
    for(int i = 0; i < 45; i++) {
        historialGastos[i] = {i+1, "Categoria_Prueba", "Descripcion falsa", 15.5f};
        contadorGastos++;
    }

    // 2. Integrante 1 y 3: Llamada al menu principal con paginacion anidada
    menuPrincipal();

    return 0;
}

bool sistemaLogin() {
    string contrasenaCorrecta = "admin123";
    string contrasenaIngresada;
    int intentos = 0;
    const int MAX_INTENTOS = 3;

    while (intentos < MAX_INTENTOS) {
        system("cls");
        cout << "========================================\n";
        cout << setw(25) << "ACCESO AL SISTEMA\n";
        cout << "========================================\n";
        cout << "Intento " << (intentos + 1) << " de " << MAX_INTENTOS << "\n\n";
        cout << "Ingrese la contrasena de administrador: ";
        
        getline(cin, contrasenaIngresada);

        if (contrasenaIngresada == contrasenaCorrecta) {
            cout << "\n[+] Acceso concedido. Bienvenido al sistema.\n";
            pausaYLimpiar();
            return true;
        } else {
            intentos++;
            cout << "\n[-] Contrasena incorrecta.\n";
            if (intentos < MAX_INTENTOS) {
                cout << "Le quedan " << (MAX_INTENTOS - intentos) << " intentos.\n";
            } else {
                cout << "ACCESO BLOQUEADO. Contacte soporte.\n";
            }
            pausaYLimpiar();
        }
    }
    return false;
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
            case 3: resumenFinanciero(); break;
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
        cout << "\t2. Listar Gastos (Prueba Paginacion)\n";
        cout << "\t3. Modificar Gasto\n";
        cout << "\t4. Eliminar Gasto\n";
        cout << "\t0. Volver al Menu Principal\n";
        cout << "Escoja una opcion: ";
        cin >> op;
        cin.ignore(256, '\n'); 

        switch (op) {
            case 0: return; 
            case 1: funcionEnConstruccion("Crear Gasto"); break;
            case 2: listarRegistrosPaginados(historialGastos, contadorGastos, "GASTOS"); break;
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
            case 2: listarRegistrosPaginados(historialIngresos, contadorIngresos, "INGRESOS"); break;
            case 3: funcionEnConstruccion("Modificar Ingreso"); break;
            case 4: funcionEnConstruccion("Eliminar Ingreso"); break;
            default: cout << "ERROR: Opcion invalida.\n"; pausaYLimpiar(); break;
        }
    } while (true);
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

void funcionEnConstruccion(string nombreModulo) {
    system("cls");
    cout << "========================================\n";
    cout << "   " << nombreModulo << "\n";
    cout << "========================================\n";
    cout << "\n[!] Este modulo estara disponible en la Fase 2.\n";
    pausaYLimpiar();
}

void resumenFinanciero() {
    funcionEnConstruccion("RESUMEN FINANCIERO");
}

void pausaYLimpiar() {
    cout << "\nPresione Enter para continuar...";
    cin.get(); 
}