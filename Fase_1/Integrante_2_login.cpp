#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>

using namespace std;

// Prototipos
bool sistemaLogin();
void pausaYLimpiar();

int main() {
    // Prueba individual del Integrante 2
    if (sistemaLogin()) {
        cout << "\n--- EL PROGRAMA PRINCIPAL SE EJECUTARIA AQUI ---\n";
    } else {
        cout << "\n--- EL PROGRAMA SE CIERRA POR SEGURIDAD ---\n";
    }
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

void pausaYLimpiar() {
    cout << "\nPresione Enter para continuar...";
    cin.get(); 
}