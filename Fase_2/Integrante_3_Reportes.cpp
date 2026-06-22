#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>

using namespace std;

struct Registro {
    int id;
    string categoria;
    float monto;
    
    Registro(int _id = 0, string _categoria = "Sin_asignar", float _monto = 0) {
        id = _id; categoria = _categoria; monto = _monto;
    }
};

const int MAX_REGISTROS = 100;
Registro historialGastos[MAX_REGISTROS];
int contadorGastos = 0;
Registro historialIngresos[MAX_REGISTROS];
int contadorIngresos = 0;

// Prototipos
void listarRegistrosPaginados(Registro[], int, string);
void resumenFinanciero();
void pausaYLimpiar();

int main() {
    // Generar datos de prueba para que el Integrante 3 verifique su paginacion y resumen
    for(int i = 0; i < 25; i++) {
        historialGastos[i] = Registro(i+1, "Gasto_Prueba", 10.5f);
        contadorGastos++;
    }
    for(int i = 0; i < 5; i++) {
        historialIngresos[i] = Registro(i+1, "Ingreso_Prueba", 100.0f);
        contadorIngresos++;
    }

    // Ejecucion
    listarRegistrosPaginados(historialGastos, contadorGastos, "LISTADO DE GASTOS");
    resumenFinanciero();
    
    return 0;
}

void listarRegistrosPaginados(Registro arreglo[], int contador, string titulo) {
    if (contador == 0) {
        cout << "No hay registros.\n";
        pausaYLimpiar();
        return;
    }

    int pagina = 0;
    char op;
    do {
        system("cls");
        cout << "--- " << titulo << " (Pag " << pagina + 1 << ") ---\n";

        int inicio = pagina * 20;
        int fin = inicio + 20;
        if (fin > contador) fin = contador; 

        for (int i = inicio; i < fin; i++) {
            cout << "ID: " << setw(3) << arreglo[i].id 
                 << " | Cat: " << setw(15) << arreglo[i].categoria 
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
    cout << "--- RESUMEN FINANCIERO ---\n";
    float tIngresos = 0, tGastos = 0;
    
    for (int i = 0; i < contadorIngresos; i++) tIngresos += historialIngresos[i].monto;
    for (int i = 0; i < contadorGastos; i++) tGastos += historialGastos[i].monto;

    cout << "Total Ingresos: S/ " << fixed << setprecision(2) << tIngresos << "\n";
    cout << "Total Gastos:   S/ " << tGastos << "\n";
    cout << "---------------------------\n";
    cout << "SALDO NETO:     S/ " << (tIngresos - tGastos) << "\n";
    
    pausaYLimpiar();
}

void pausaYLimpiar() {
    cout << "\nPresione Enter para continuar...";
    cin.get(); 
}
