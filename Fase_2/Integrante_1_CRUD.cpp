#include <iostream>
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

// Prototipos
void menuGastos();
bool crearRegistro(Registro[], int&, string);
void modificarRegistro(Registro[], int, string);
void eliminarRegistro(Registro[], int&, string);
string seleccionarCategoria(string);
void pausaYLimpiar();

int main() {
    // Prueba del motor CRUD del Integrante 1
    cout << "Iniciando prueba del modulo CRUD...\n";
    pausaYLimpiar();
    menuGastos();
    return 0;
}

void menuGastos() {
    int op;
    do {
        system("cls");
        cout << "--- MODULO GASTOS (Prueba CRUD) ---\n";
        cout << "1. Crear\n2. Modificar\n3. Eliminar\n0. Salir\nOpcion: ";
        cin >> op;
        cin.ignore(); 

        switch (op) {
            case 0: return; 
            case 1: crearRegistro(historialGastos, contadorGastos, "Gasto"); break;
            case 2: modificarRegistro(historialGastos, contadorGastos, "Gasto"); break;
            case 3: eliminarRegistro(historialGastos, contadorGastos, "Gasto"); break;
        }
    } while (true);
}

bool crearRegistro(Registro arreglo[], int &contador, string tipo) {
    system("cls");
    if (contador >= MAX_REGISTROS) return false;

    cout << "--- NUEVO " << tipo << " ---\n";
    float monto;
    cout << "Ingrese monto: ";
    cin >> monto;
    cin.ignore();
    
    string categoria = seleccionarCategoria(tipo); 
    int nuevoId = (contador > 0) ? arreglo[contador - 1].id + 1 : 1;
    
    arreglo[contador] = Registro(nuevoId, categoria, monto);
    contador++;

    cout << "\nRegistro guardado (ID: " << nuevoId << ").\n";
    pausaYLimpiar();
    return true;
}

void modificarRegistro(Registro arreglo[], int contador, string tipo) {
    system("cls");
    int idBuscado;
    cout << "ID a modificar: ";
    cin >> idBuscado;
    cin.ignore(); 
    
    for (int i = 0; i < contador; i++) {
        if (arreglo[i].id == idBuscado) {
            cout << "Nuevo monto: ";
            cin >> arreglo[i].monto;
            cin.ignore();
            arreglo[i].categoria = seleccionarCategoria(tipo);
            cout << "Modificado con exito.\n";
            pausaYLimpiar();
            return;
        }
    }
    cout << "No encontrado.\n";
    pausaYLimpiar();
}

void eliminarRegistro(Registro arreglo[], int &contador, string tipo) {
    system("cls");
    int idBuscado;
    cout << "ID a eliminar: ";
    cin >> idBuscado;
    cin.ignore();
    
    for (int i = 0; i < contador; i++) {
        if (arreglo[i].id == idBuscado) {
            for (int j = i; j < contador - 1; j++) {
                arreglo[j] = arreglo[j + 1];
            }
            contador--;
            cout << "Eliminado con exito.\n";
            pausaYLimpiar();
            return;
        }
    }
    cout << "No encontrado.\n";
    pausaYLimpiar();
}

string seleccionarCategoria(string tipo) {
    int op;
    string seleccion = "";
    cout << "\n--- CATEGORIAS ---\n";
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
            case 7: cout << "Escriba la categoria: "; cin >> seleccion; cin.ignore(); break;
            default: seleccion = "Otros_Gastos"; break;
        }
    }
    return seleccion;
}

void pausaYLimpiar() {
    cout << "\nPresione Enter para continuar...";
    cin.get(); 
}
