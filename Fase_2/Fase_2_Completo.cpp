#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdio>
#include <cstdlib>

using namespace std;

// ==========================================
// ESTRUCTURA GLOBAL 
// ==========================================
struct Registro {
    int id;
    string categoria;
    float monto;
    
    Registro(int _id = 0, string _categoria = "Sin_asignar", float _monto = 0) {
        id = _id;
        categoria = _categoria;
        monto = _monto;
    }
};

const int MAX_REGISTROS = 100;
Registro historialGastos[MAX_REGISTROS];
int contadorGastos = 0;
Registro historialIngresos[MAX_REGISTROS];
int contadorIngresos = 0;

// ==========================================
// PROTOTIPOS GENERALES
// ==========================================
// Integrante 1 (CRUD y Menus)
void menuPrincipal();
void menuGastos();
void menuIngresos();
bool crearRegistro(Registro[], int&, string);
void modificarRegistro(Registro[], int, string);
void eliminarRegistro(Registro[], int&, string);

// Integrante 2 (Archivos y Login)
bool sistemaLogin();
void cargarDatos();
void guardarDatos();

// Integrante 3 (Algoritmia y Reportes)
void listarRegistrosPaginados(Registro[], int, string);
void resumenFinanciero();

// Utilidades Compartidas
void pausaYLimpiar();
string seleccionarCategoria(string);

// ==========================================
// MAIN (PUNTO DE ARRANQUE)
// ==========================================
int main() {
    // 1. Ejecucion de Seguridad (I2)
    if (!sistemaLogin()) {
        return 0; // Cierra si falla la clave
    }
    
    // 2. Carga de memoria (I2)
    cargarDatos();

    // 3. Ejecucion del Sistema Principal (I1 e I3)
    menuPrincipal();

    // 4. Respaldo de memoria antes de salir (I2)
    guardarDatos();
    return 0;
}

// ==========================================
// INTEGRANTE 2: SISTEMA DE LOGIN Y ARCHIVOS (TXT)
// ==========================================
bool sistemaLogin() {
    string passCorrecta = "admin123";
    string passIngresada;
    int intentos = 0;

    while (intentos < 3) {
        system("cls");
        cout << "========================================\n";
        cout << setw(25) << "PROYECTO LOGIN\n";
        cout << "========================================\n";
        cout << "--- ACCESO AL SISTEMA (Intento " << intentos + 1 << " de 3) ---\n\n";
        cout << "Contrasena: ";
        getline(cin, passIngresada);

        if (passIngresada == passCorrecta) {
            cout << "\n[+] Acceso concedido.\n";
            pausaYLimpiar();
            return true;
        }
        
        intentos++;
        cout << "\n[-] Contrasena incorrecta.\n";
        pausaYLimpiar();
    }
    return false;
}

void cargarDatos() {
    int _id;
    char _cat[50];
    float _mon;

    FILE *archGastos = fopen("gastos.txt", "r");
    contadorGastos = 0;
    if (archGastos != NULL) {
        while (fscanf(archGastos, "%d %49s %f", &_id, _cat, &_mon) == 3) {
            historialGastos[contadorGastos] = Registro(_id, _cat, _mon);
            contadorGastos++;
        }
        fclose(archGastos);
    }

    FILE *archIngresos = fopen("ingresos.txt", "r");
    contadorIngresos = 0;
    if (archIngresos != NULL) {
        while (fscanf(archIngresos, "%d %49s %f", &_id, _cat, &_mon) == 3) {
            historialIngresos[contadorIngresos] = Registro(_id, _cat, _mon);
            contadorIngresos++;
        }
        fclose(archIngresos);
    }
}

void guardarDatos() {
    FILE *archGastos = fopen("gastos.txt", "w");
    if (archGastos != NULL) {
        for (int i = 0; i < contadorGastos; i++) {
            fprintf(archGastos, "%d %s %.2f\n", 
                    historialGastos[i].id, historialGastos[i].categoria.c_str(), historialGastos[i].monto);
        }
        fclose(archGastos);
    }

    FILE *archIngresos = fopen("ingresos.txt", "w");
    if (archIngresos != NULL) {
        for (int i = 0; i < contadorIngresos; i++) {
            fprintf(archIngresos, "%d %s %.2f\n", 
                    historialIngresos[i].id, historialIngresos[i].categoria.c_str(), historialIngresos[i].monto);
        }
        fclose(archIngresos);
    }
}

// ==========================================
// INTEGRANTE 1: MENUS ANIDADOS Y MOTOR CRUD 
// ==========================================
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
        cout << "\t0. Guardar y Salir\n";
        cout << "Opcion: ";
        cin >> op;
        cin.ignore(); 

        switch (op) {
            case 0: cout << "Guardando en archivos...\n"; return;
            case 1: menuGastos(); break;
            case 2: menuIngresos(); break;
            case 3: resumenFinanciero(); break;
        }
    } while (true);
}

void menuGastos() {
    int op;
    do {
        system("cls");
        cout << "--- SUBMENU GASTOS ---\n";
        cout << "1. Crear Registro\n2. Listar Registros\n3. Modificar Registro\n4. Eliminar Registro\n0. Volver\nOpcion: ";
        cin >> op;
        cin.ignore(); 

        switch (op) {
            case 0: return; 
            case 1: crearRegistro(historialGastos, contadorGastos, "Gasto"); break;
            case 2: listarRegistrosPaginados(historialGastos, contadorGastos, "GASTOS"); break;
            case 3: modificarRegistro(historialGastos, contadorGastos, "Gasto"); break;
            case 4: eliminarRegistro(historialGastos, contadorGastos, "Gasto"); break;
        }
    } while (true);
}

void menuIngresos() {
    int op;
    do {
        system("cls");
        cout << "--- SUBMENU INGRESOS ---\n";
        cout << "1. Crear Registro\n2. Listar Registros\n3. Modificar Registro\n4. Eliminar Registro\n0. Volver\nOpcion: ";
        cin >> op;
        cin.ignore(); 

        switch (op) {
            case 0: return; 
            case 1: crearRegistro(historialIngresos, contadorIngresos, "Ingreso"); break;
            case 2: listarRegistrosPaginados(historialIngresos, contadorIngresos, "INGRESOS"); break;
            case 3: modificarRegistro(historialIngresos, contadorIngresos, "Ingreso"); break;
            case 4: eliminarRegistro(historialIngresos, contadorIngresos, "Ingreso"); break;
        }
    } while (true);
}

bool crearRegistro(Registro arreglo[], int &contador, string tipo) {
    system("cls");
    if (contador >= MAX_REGISTROS) {
        cout << "Error: Memoria llena.\n";
        pausaYLimpiar();
        return false;
    }

    cout << "--- NUEVO " << tipo << " ---\n";
    float monto;
    cout << "Ingrese monto: ";
    cin >> monto;
    cin.ignore();
    
    string categoria = seleccionarCategoria(tipo); 
    int nuevoId = (contador > 0) ? arreglo[contador - 1].id + 1 : 1;
    
    arreglo[contador] = Registro(nuevoId, categoria, monto);
    contador++;

    cout << "\nRegistro guardado correctamente.\n";
    pausaYLimpiar();
    return true;
}

void modificarRegistro(Registro arreglo[], int contador, string tipo) {
    system("cls");
    if (contador == 0) {
        cout << "No hay datos para modificar.\n";
        pausaYLimpiar(); return;
    }
    
    int idBuscado;
    cout << "Ingrese el ID a modificar: ";
    cin >> idBuscado;
    cin.ignore(); 
    
    for (int i = 0; i < contador; i++) {
        if (arreglo[i].id == idBuscado) {
            cout << "\nNuevo monto: ";
            cin >> arreglo[i].monto;
            cin.ignore();
            arreglo[i].categoria = seleccionarCategoria(tipo);
            cout << "\nModificado con exito.\n";
            pausaYLimpiar();
            return;
        }
    }
    cout << "\nError: ID no encontrado.\n";
    pausaYLimpiar();
}

void eliminarRegistro(Registro arreglo[], int &contador, string tipo) {
    system("cls");
    if (contador == 0) {
        cout << "No hay datos para eliminar.\n";
        pausaYLimpiar(); return;
    }
    
    int idBuscado;
    cout << "Ingrese el ID a eliminar: ";
    cin >> idBuscado;
    cin.ignore();
    
    for (int i = 0; i < contador; i++) {
        if (arreglo[i].id == idBuscado) {
            // Reordenamiento de array
            for (int j = i; j < contador - 1; j++) {
                arreglo[j] = arreglo[j + 1];
            }
            contador--;
            cout << "\nEliminado con exito.\n";
            pausaYLimpiar();
            return;
        }
    }
    cout << "\nError: ID no encontrado.\n";
    pausaYLimpiar();
}

// ==========================================
// INTEGRANTE 3: LISTADOS PAGINADOS Y RESUMEN 
// ==========================================
void listarRegistrosPaginados(Registro arreglo[], int contador, string titulo) {
    if (contador == 0) {
        cout << "Lista vacia.\n";
        pausaYLimpiar();
        return;
    }

    int pagina = 0;
    char op;
    do {
        system("cls");
        cout << "--- " << titulo << " (Pagina " << pagina + 1 << ") ---\n";

        int inicio = pagina * 20;
        int fin = inicio + 20;
        if (fin > contador) fin = contador; 

        for (int i = inicio; i < fin; i++) {
            cout << "ID: " << setw(3) << arreglo[i].id 
                 << " | Categoria: " << setw(15) << arreglo[i].categoria 
                 << " | Monto: S/ " << arreglo[i].monto << "\n";
        }

        cout << "\n[D] Siguiente  [A] Anterior  [0] Salir\nOpcion: ";
        cin >> op;
        cin.ignore();
        op = toupper(op);

        if (op == 'D' && fin < contador) pagina++;
        else if (op == 'A' && pagina > 0) pagina--;

    } while (op != '0');
}

void resumenFinanciero() {
    system("cls");
    cout << "========================================\n";
    cout << setw(25) << "RESUMEN FINANCIERO\n";
    cout << "========================================\n\n";
    
    float tIngresos = 0, tGastos = 0;
    
    for (int i = 0; i < contadorIngresos; i++) tIngresos += historialIngresos[i].monto;
    for (int i = 0; i < contadorGastos; i++) tGastos += historialGastos[i].monto;

    cout << "Total Ingresos Brutos: S/ " << fixed << setprecision(2) << tIngresos << "\n";
    cout << "Total Gastos Generales: S/ " << tGastos << "\n";
    cout << "----------------------------------------\n";
    cout << "SALDO NETO ACTUAL:      S/ " << (tIngresos - tGastos) << "\n";
    
    pausaYLimpiar();
}

// ==========================================
// UTILIDADES COMPARTIDAS
// ==========================================
void pausaYLimpiar() {
    cout << "\nPresione Enter para continuar...";
    cin.get(); 
}

string seleccionarCategoria(string tipo) {
    int op;
    string seleccion = "";

    cout << "\n--- ASIGNAR CATEGORIA ---\n";
    if (tipo == "Gasto") {
        cout << "1. Alimentacion\n2. Transporte\n3. Educacion\n4. Recreativo\n5. Salud\n6. Proyectos\n7. Otra\nOpcion: ";
        cin >> op; cin.ignore();
        switch(op) {
            case 1: seleccion = "Alimentacion"; break;
            case 2: seleccion = "Transporte"; break;
            case 3: seleccion = "Educacion"; break;
            case 4: seleccion = "Recreativo"; break;
            case 5: seleccion = "Salud"; break;
            case 6: seleccion = "Proyectos"; break;
            case 7: cout << "Escriba (una palabra sin espacios): "; cin >> seleccion; cin.ignore(); break;
            default: seleccion = "Otros_Gastos"; break;
        }
    } else {
        cout << "1. Trabajo\n2. Donacion\n3. Ventas\n4. Otra\nOpcion: ";
        cin >> op; cin.ignore();
        switch(op) {
            case 1: seleccion = "Trabajo"; break;
            case 2: seleccion = "Donacion"; break;
            case 3: seleccion = "Ventas"; break;
            case 4: cout << "Escriba (una palabra sin espacios): "; cin >> seleccion; cin.ignore(); break;
            default: seleccion = "Otros_Ingresos"; break;
        }
    }
    return seleccion;
}