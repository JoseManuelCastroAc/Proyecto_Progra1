#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstdio>
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

// Prototipos
bool sistemaLogin();
void cargarDatos();
void guardarDatos();
void pausaYLimpiar();

int main() {
    // Prueba del Integrante 2
    if (!sistemaLogin()) return 0;
    
    cout << "Cargando datos del disco...\n";
    cargarDatos();
    cout << "Datos cargados: " << contadorGastos << " registros.\n";
    pausaYLimpiar();
    
    // Generar un dato falso para probar que guarda
    historialGastos[contadorGastos] = Registro(999, "Prueba_Sistema", 50.0);
    contadorGastos++;
    
    cout << "Guardando datos en disco...\n";
    guardarDatos();
    cout << "Revisa tu carpeta, deberia existir 'gastos.txt'.\n";
    
    return 0;
}

bool sistemaLogin() {
    string passCorrecta = "admin123";
    string passIngresada;
    int intentos = 0;

    while (intentos < 3) {
        system("cls");
        cout << "--- LOGIN (Intento " << intentos + 1 << " de 3) ---\n";
        cout << "Contrasena: ";
        getline(cin, passIngresada);

        if (passIngresada == passCorrecta) return true;
        
        intentos++;
        cout << "Contrasena incorrecta.\n";
        pausaYLimpiar();
    }
    return false;
}

void cargarDatos() {
    int _id; char _cat[50]; float _mon;

    FILE *archGastos = fopen("gastos.txt", "r");
    contadorGastos = 0;
    if (archGastos != NULL) {
        while (fscanf(archGastos, "%d %49s %f", &_id, _cat, &_mon) == 3) {
            historialGastos[contadorGastos] = Registro(_id, _cat, _mon);
            contadorGastos++;
        }
        fclose(archGastos);
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
}

void pausaYLimpiar() {
    cout << "\nPresione Enter para continuar...";
    cin.get(); 
}
