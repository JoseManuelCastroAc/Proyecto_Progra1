#include <iostream>
#include <iomanip>
#include <string>
#include <cstdio>
#include <cstdlib>
// No se incluye <ctime> según las especificaciones

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

// Variables globales para el manejo del tiempo (ingresadas por el usuario)
int mesProceso = 0;
int anioProceso = 0;

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
void cargarDatos(int mes, int anio);
void guardarDatos(int mes, int anio);
void cierreDeMes(); 

// Integrante 3 (Algoritmia y Reportes)
void listarRegistrosPaginados(Registro[], int, string);
void resumenFinanciero();
float calcularSaldoMensual(); // NUEVA: Funcion para calcular el saldo

// Utilidades Compartidas
void pausaYLimpiar();
string seleccionarCategoria(string);
void generarNombreArchivo(char* buffer, const char* prefijo, int mes, int anio);

// ==========================================
// MAIN (PUNTO DE ARRANQUE)
// ==========================================
int main() {
    // 1. Ejecucion de Seguridad
    if (!sistemaLogin()) {
        return 0; // Cierra si falla la clave
    }
    
    // 2. Solicitud de fecha de proceso con Validación de Consistencia
    system("cls");
    cout << "========================================\n";
    cout << setw(30) << "CONFIGURACION DE PERIODO\n";
    cout << "========================================\n";
    
    // Validación para el Mes
    do {
        cout << "Ingrese el mes a procesar (1 al 12): ";
        cin >> mesProceso;
        if (mesProceso < 1 || mesProceso > 12) {
            cout << "[-] Error: El mes debe estar entre 1 y 12. Intente nuevamente.\n\n";
        }
    } while (mesProceso < 1 || mesProceso > 12);

    // Validación para el Año
    do {
        cout << "Ingrese el ano a procesar (ej. 2026): ";
        cin >> anioProceso;
        if (anioProceso < 2000 || anioProceso > 2100) {
            cout << "[-] Error: Ingrese un ano valido (Rango sugerido: 2000 - 2100).\n\n";
        }
    } while (anioProceso < 2000 || anioProceso > 2100);
    
    cin.ignore();
    
    // 3. Carga de memoria
    cargarDatos(mesProceso, anioProceso);

    // 4. Ejecucion del Sistema Principal
    menuPrincipal();

    // 5. Respaldo de memoria antes de salir
    guardarDatos(mesProceso, anioProceso);
    return 0;
}

// ==========================================
// INTEGRANTE 2: SISTEMA DE LOGIN Y ARCHIVOS (C)
// ==========================================
bool sistemaLogin() {
    string passCorrecta = "admin123";
    string passIngresada;
    int intentos = 0;

    while (intentos < 3) {
        system("cls");
        cout << "========================================\n";
        cout << setw(25) << "Login Page\n";
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

void generarNombreArchivo(char* buffer, const char* prefijo, int mes, int anio) {
    sprintf(buffer, "%s_%02d_%04d.txt", prefijo, mes, anio);
}

void cargarDatos(int mes, int anio) {
    int _id;
    char _cat[50];
    float _mon;
    char nombreArchivo[100];

    // Cargar Gastos
    generarNombreArchivo(nombreArchivo, "gastos", mes, anio);
    FILE *archGastos = fopen(nombreArchivo, "r");
    contadorGastos = 0;
    if (archGastos != NULL) {
        while (fscanf(archGastos, "%d %49s %f", &_id, _cat, &_mon) == 3) {
            historialGastos[contadorGastos] = Registro(_id, _cat, _mon);
            contadorGastos++;
        }
        fclose(archGastos);
    }

    // Cargar Ingresos
    generarNombreArchivo(nombreArchivo, "ingresos", mes, anio);
    FILE *archIngresos = fopen(nombreArchivo, "r");
    contadorIngresos = 0;
    if (archIngresos != NULL) {
        while (fscanf(archIngresos, "%d %49s %f", &_id, _cat, &_mon) == 3) {
            historialIngresos[contadorIngresos] = Registro(_id, _cat, _mon);
            contadorIngresos++;
        }
        fclose(archIngresos);
    }
}

void guardarDatos(int mes, int anio) {
    char nombreArchivo[100];

    // Guardar Gastos
    generarNombreArchivo(nombreArchivo, "gastos", mes, anio);
    FILE *archGastos = fopen(nombreArchivo, "w");
    if (archGastos != NULL) {
        for (int i = 0; i < contadorGastos; i++) {
            fprintf(archGastos, "%d %s %.2f\n",
                    historialGastos[i].id, historialGastos[i].categoria.c_str(), historialGastos[i].monto);
        }
        fclose(archGastos);
    }

    // Guardar Ingresos
    generarNombreArchivo(nombreArchivo, "ingresos", mes, anio);
    FILE *archIngresos = fopen(nombreArchivo, "w");
    if (archIngresos != NULL) {
        for (int i = 0; i < contadorIngresos; i++) {
            fprintf(archIngresos, "%d %s %.2f\n",
                    historialIngresos[i].id, historialIngresos[i].categoria.c_str(), historialIngresos[i].monto);
        }
        fclose(archIngresos);
    }
}

void cierreDeMes() {
    system("cls");
    cout << "--- PROCESANDO CIERRE DE MES ---\n";
    
    guardarDatos(mesProceso, anioProceso);
    cout << "[+] Datos del mes " << mesProceso << "/" << anioProceso << " guardados correctamente.\n";

    int sigMes = mesProceso + 1;
    int sigAnio = anioProceso;
    if (sigMes > 12) {
        sigMes = 1;
        sigAnio++;
    }

    char nombreArchivoG[100], nombreArchivoI[100];
    generarNombreArchivo(nombreArchivoG, "gastos", sigMes, sigAnio);
    generarNombreArchivo(nombreArchivoI, "ingresos", sigMes, sigAnio);

    FILE* archNuevoG = fopen(nombreArchivoG, "w");
    if(archNuevoG) fclose(archNuevoG);

    FILE* archNuevoI = fopen(nombreArchivoI, "w");
    if(archNuevoI) fclose(archNuevoI);

    cout << "[+] Archivos generados para el mes " << sigMes << "/" << sigAnio << ".\n";

    mesProceso = sigMes;
    anioProceso = sigAnio;
    contadorGastos = 0;
    contadorIngresos = 0;

    cout << "\nCierre completado. El sistema ahora operara en el nuevo mes.\n";
    pausaYLimpiar();
}

// ==========================================
// INTEGRANTE 1: MENUS ANIDADOS Y MOTOR CRUD
// ==========================================
float calcularSaldoMensual() {
    float totalIngresos = 0, totalGastos = 0;
    for(int i = 0; i < contadorIngresos; i++) totalIngresos += historialIngresos[i].monto;
    for(int i = 0; i < contadorGastos; i++) totalGastos += historialGastos[i].monto;
    return totalIngresos - totalGastos;
}

void menuPrincipal() {
    int op;
    do {
        float saldoActual = calcularSaldoMensual();
        
        system("cls");
        cout << "========================================\n";
        cout << setw(25) << "MENU PRINCIPAL\n";
        cout << "========================================\n";
        cout << " Periodo: Mes " << mesProceso << " | Anio " << anioProceso << "\n";
        cout << " Saldo del Mes: S/ " << fixed << setprecision(2) << saldoActual << "\n";
        
        // ADVERTENCIA SI HAY SALDO NEGATIVO
        if(saldoActual < 0) {
            cout << "\n [!] ADVERTENCIA: Esta gastando mas de sus ingresos.\n";
        }
        
        cout << "----------------------------------------\n";
        cout << "\t1. Modulo de Gastos\n";
        cout << "\t2. Modulo de Ingresos\n";
        cout << "\t3. Resumen Financiero\n";
        cout << "\t4. Cierre de Mes\n";
        cout << "\t0. Guardar y Salir\n";
        cout << "Opcion: ";
        cin >> op;
        cin.ignore();

        switch (op) {
            case 0: cout << "Guardando en archivos...\n"; return;
            case 1: menuGastos(); break;
            case 2: menuIngresos(); break;
            case 3: resumenFinanciero(); break;
            case 4: cierreDeMes(); break;
        }
    } while (true);
}

void menuGastos() {
    int op;
    do {
        system("cls");
        cout << "--- SUBMENU GASTOS ---\n";
        cout << "1. Ingresar Gastos Multiples\n2. Listar Registros\n3. Modificar Registro\n4. Eliminar Registro\n0. Volver\nOpcion: ";
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
        cout << "1. Ingresar Ingresos Multiples\n2. Listar Registros\n3. Modificar Registro\n4. Eliminar Registro\n0. Volver\nOpcion: ";
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

// NUEVA FORMA: PREGUNTA POR TODAS LAS CATEGORÍAS
bool crearRegistro(Registro arreglo[], int &contador, string tipo) {
    system("cls");
    if (contador >= MAX_REGISTROS) {
        cout << "Error: Memoria llena.\n";
        pausaYLimpiar();
        return false;
    }

    cout << "--- NUEVO REGISTRO DE " << (tipo == "Gasto" ? "GASTOS" : "INGRESOS") << " ---\n";
    cout << "(Ingrese 0 si no tiene movimientos en una categoria)\n\n";

    string catGastos[] = {"Alimentacion", "Transporte", "Educacion", "Recreativo", "Salud"};
    string catIngresos[] = {"Trabajo", "Donacion", "Ventas"};
    
    int numCat = (tipo == "Gasto") ? 5 : 3;
    string* categorias = (tipo == "Gasto") ? catGastos : catIngresos;
    
    bool huboRegistros = false;

    for(int i = 0; i < numCat; i++) {
        if (contador >= MAX_REGISTROS) {
            cout << "\n[!] Memoria llena, no se pueden seguir agregando.\n";
            break;
        }

        float monto;
        cout << "Cuanto ha " << (tipo == "Gasto" ? "gastado" : "ingresado") << " en [" << categorias[i] << "]?: S/ ";
        cin >> monto;
        cin.ignore();

        if (monto > 0) {
            int nuevoId = (contador > 0) ? arreglo[contador - 1].id + 1 : 1;
            arreglo[contador] = Registro(nuevoId, categorias[i], monto);
            contador++;
            huboRegistros = true;
        }
    }

    if (huboRegistros) {
        cout << "\nRegistros guardados correctamente.\n";
    } else {
        cout << "\nNo se guardo ningun registro nuevo.\n";
    }
    
    pausaYLimpiar();
    return true;
}

void modificarRegistro(Registro arreglo[], int contador, string tipo) {
    system("cls");
    if (contador == 0) {
        cout << "No hay datos para modificar.\n";
        pausaYLimpiar();
        return;
    }
    
    int idBuscado;
    cout << "Ingrese el ID a modificar: ";
    cin >> idBuscado;
    cin.ignore();
    
    for (int i = 0; i < contador; i++) {
        if (arreglo[i].id == idBuscado) {
            cout << "\nNuevo monto: S/ ";
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
        pausaYLimpiar();
        return;
    }
    
    int idBuscado;
    cout << "Ingrese el ID a eliminar: ";
    cin >> idBuscado;
    cin.ignore();
    
    for (int i = 0; i < contador; i++) {
        if (arreglo[i].id == idBuscado) {
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
    float sumIngresos[3][12] = {0}; 
    float sumGastos[5][12] = {0};   
    
    string catIngresos[] = {"Trabajo", "Donacion", "Ventas"};
    string catGastos[] = {"Alimentacion", "Transporte", "Educacion", "Recreativo", "Salud"};
    string nombresMeses[] = {"Ene", "Feb", "Mar", "Abr", "May", "Jun",
                             "Jul", "Ago", "Set", "Oct", "Nov", "Dic"};

    for (int m = 1; m <= 12; m++) {
        char nombreArchivo[100];
        int _id;
        char _cat[50];
        float _mon;
        
        sprintf(nombreArchivo, "ingresos_%02d_%04d.txt", m, anioProceso);
        FILE* archI = fopen(nombreArchivo, "r");
        if (archI) {
            while (fscanf(archI, "%d %49s %f", &_id, _cat, &_mon) == 3) {
                string sCat(_cat);
                for(int c = 0; c < 3; c++) {
                    if(sCat == catIngresos[c]) {
                        sumIngresos[c][m-1] += _mon;
                        break;
                    }
                }
            }
            fclose(archI);
        }
        
        sprintf(nombreArchivo, "gastos_%02d_%04d.txt", m, anioProceso);
        FILE* archG = fopen(nombreArchivo, "r");
        if (archG) {
            while (fscanf(archG, "%d %49s %f", &_id, _cat, &_mon) == 3) {
                string sCat(_cat);
                for(int c = 0; c < 5; c++) {
                    if(sCat == catGastos[c]) {
                        sumGastos[c][m-1] += _mon;
                        break;
                    }
                }
            }
            fclose(archG);
        }
    }
    
    int pagina = 0; 
    char op;
    
    do {
        system("cls");
        int mesInicio = pagina * 6;
        int mesFin = mesInicio + 6;
        
        cout << "================================================================================\n";
        cout << "               RESUMEN ANUAL TIPO EXCEL (Anio: " << anioProceso << ") - Pagina " << pagina + 1 << "/2\n";
        cout << "================================================================================\n";
        
        cout << left << setw(15) << "CATEGORIAS" << "|";
        for (int m = mesInicio; m < mesFin; m++) {
            cout << right << setw(9) << nombresMeses[m] << " |";
        }
        cout << "\n--------------------------------------------------------------------------------\n";
        
        cout << "[ INGRESOS ]\n";
        for (int c = 0; c < 3; c++) {
            cout << left << setw(15) << catIngresos[c] << "|";
            for (int m = mesInicio; m < mesFin; m++) {
                cout << right << setw(9) << fixed << setprecision(2) << sumIngresos[c][m] << " |";
            }
            cout << "\n";
        }
        
        cout << "--------------------------------------------------------------------------------\n";
        
        cout << "[ GASTOS ]\n";
        for (int c = 0; c < 5; c++) {
            cout << left << setw(15) << catGastos[c] << "|";
            for (int m = mesInicio; m < mesFin; m++) {
                cout << right << setw(9) << fixed << setprecision(2) << sumGastos[c][m] << " |";
            }
            cout << "\n";
        }
        cout << "================================================================================\n";
        
        cout << "\nControles: [D] Semestre 2 (Jul-Dic)   [A] Semestre 1 (Ene-Jun)   [0] Salir\n";
        cout << "Opcion: ";
        cin >> op;
        cin.ignore();
        op = toupper(op);
        
        if (op == 'D') pagina = 1;      
        else if (op == 'A') pagina = 0; 
        
    } while (op != '0');
}

//======================================
// UTILIDADES COMPARTIDAS
// ==========================================
void pausaYLimpiar() {
    cout << "\nPresione Enter para continuar...";
    cin.get();
}

// Se mantiene para cuando se necesite MODIFICAR un registro especifico
string seleccionarCategoria(string tipo) {
    int op;
    string seleccion = "";

    cout << "\n--- ASIGNAR NUEVA CATEGORIA ---\n";
    if (tipo == "Gasto") {
        cout << "1. Alimentacion\n2. Transporte\n3. Educacion\n4. Recreativo\n5. Salud\nOpcion: ";
        cin >> op; cin.ignore();
        switch(op) {
            case 1: seleccion = "Alimentacion"; break;
            case 2: seleccion = "Transporte"; break;
            case 3: seleccion = "Educacion"; break;
            case 4: seleccion = "Recreativo"; break;
            case 5: seleccion = "Salud"; break;
            default: seleccion = "Alimentacion"; break; 
        }
    } else {
        cout << "1. Trabajo\n2. Donacion\n3. Ventas\nOpcion: ";
        cin >> op; cin.ignore();
        switch(op) {
            case 1: seleccion = "Trabajo"; break;
            case 2: seleccion = "Donacion"; break;
            case 3: seleccion = "Ventas"; break;
            default: seleccion = "Trabajo"; break; 
        }
    }
    return seleccion;
}
