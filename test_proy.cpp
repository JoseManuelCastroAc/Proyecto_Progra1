#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>
#include <cstdio>
#include <cstdlib>

using namespace std;

const int MAX_REGISTROS = 100;
int contadorGastos = 0;
int contadorIngresos = 0;
bool flag = 0;

struct Registro {
	int id;
	time_t fecha;
	string categoria, descripcion;
	float monto;
	
	Registro(int _id = 0, string _categoria = "Sin_asignar", string _descripcion = "Sin_asignar", float _monto = 0) {
		id = _id;
		fecha = time(0); 
		categoria = _categoria;
		descripcion = _descripcion;
		monto = _monto;
	}
};

Registro historialGastos[MAX_REGISTROS];
Registro historialIngresos[MAX_REGISTROS];

// Prototipos
void menu(int*);
float calcularSaldo();
bool crearRegistro(Registro[], int&, string);
void listarRegistros(Registro[], int, string);
void modificarRegistro(Registro[], int, string);
void eliminarRegistro(Registro[], int&, string);
void resumenFinanciero(); // Nueva funcion

void cargarDatos();
void guardarDatos();

void pausaYLimpiar();
float inputMonto(string, float);
string inputTexto(string, string, bool);
string seleccionarCategoria(string, string);
string espaciosAGuiones(string);
string guionesAEspacios(string);

int main() {
	cargarDatos();
	int OPCION;
	menu(&OPCION);
	guardarDatos();
	return 0;
}

float calcularSaldo() {
	float totalIngresos = 0.0;
	float totalGastos = 0.0;
	
	for (int i = 0; i < contadorIngresos; i++) {
		totalIngresos += historialIngresos[i].monto;
	}
	for (int i = 0; i < contadorGastos; i++) {
		totalGastos += historialGastos[i].monto;
	}
	
	return totalIngresos - totalGastos;
}

void menu(int* op) {
	do {
		system("cls");
		cout << "========================================\n";
		cout << setw(25) << "SISTEMA FINANCIERO\n";
		cout << "========================================\n";
		cout << "SALDO GLOBAL ACTUAL: S/ " << fixed << setprecision(2) << calcularSaldo() << "\n";
		cout << "========================================\n";
		cout << "   --- GASTOS ---\n";
		cout << "\t1. Crear Gasto\n";
		cout << "\t2. Listar Gastos\n";
		cout << "\t3. Modificar Gasto\n";
		cout << "\t4. Eliminar Gasto\n";
		cout << "   --- INGRESOS ---\n";
		cout << "\t5. Crear Ingreso\n";
		cout << "\t6. Listar Ingresos\n";
		cout << "\t7. Modificar Ingreso\n";
		cout << "\t8. Eliminar Ingreso\n";
		cout << "   --- REPORTES ---\n";
		cout << "\t9. Resumen Financiero\n";
		cout << "\t0. Guardar y Cerrar sistema\n";
		cout << "Sirvase de escoger una opcion: ";
		
		cin >> *op;
		cin.ignore(256, '\n'); 
		
		cout << "\n";
		switch (*op) {
		case 0: cout << "Guardando datos y cerrando el sistema...\n"; return;
		case 1: crearRegistro(historialGastos, contadorGastos, "Gasto"); break;
		case 2: listarRegistros(historialGastos, contadorGastos, "GASTOS"); break;
		case 3: modificarRegistro(historialGastos, contadorGastos, "Gasto"); break;
		case 4: eliminarRegistro(historialGastos, contadorGastos, "Gasto"); break;
		case 5: crearRegistro(historialIngresos, contadorIngresos, "Ingreso"); break;
		case 6: listarRegistros(historialIngresos, contadorIngresos, "INGRESOS"); break;
		case 7: modificarRegistro(historialIngresos, contadorIngresos, "Ingreso"); break;
		case 8: eliminarRegistro(historialIngresos, contadorIngresos, "Ingreso"); break;
		case 9: resumenFinanciero(); break;
		default:
			cout << "ERROR: Seleccione un numero del 0 al 9.\n";
			pausaYLimpiar();
			break;
		}
	} while (true);
}

// Nueva funcion para el Resumen Financiero agrupado
void resumenFinanciero() {
	system("cls");
	cout << "========================================\n";
	cout << setw(28) << "RESUMEN FINANCIERO\n";
	cout << "========================================\n\n";

	// Arreglos temporales para agrupar Ingresos
	string catIngresos[MAX_REGISTROS];
	float totalCatIngresos[MAX_REGISTROS];
	int numCatIngresos = 0;
	float sumaIngresos = 0;

	for (int i = 0; i < contadorIngresos; i++) {
		bool encontrado = false;
		sumaIngresos += historialIngresos[i].monto;
		
		for (int j = 0; j < numCatIngresos; j++) {
			if (catIngresos[j] == historialIngresos[i].categoria) {
				totalCatIngresos[j] += historialIngresos[i].monto;
				encontrado = true;
				break;
			}
		}
		if (!encontrado) {
			catIngresos[numCatIngresos] = historialIngresos[i].categoria;
			totalCatIngresos[numCatIngresos] = historialIngresos[i].monto;
			numCatIngresos++;
		}
	}

	cout << "--- TOTAL DE INGRESOS POR CATEGORIA ---\n";
	if (numCatIngresos == 0) cout << "No hay ingresos registrados.\n";
	for (int i = 0; i < numCatIngresos; i++) {
		cout << left << setw(20) << guionesAEspacios(catIngresos[i]) 
			 << " : S/ " << right << setw(8) << fixed << setprecision(2) << totalCatIngresos[i] << "\n";
	}
	cout << "----------------------------------------\n";
	cout << left << setw(20) << "TOTAL INGRESOS" << " : S/ " << right << setw(8) << sumaIngresos << "\n\n";

	// Arreglos temporales para agrupar Gastos
	string catGastos[MAX_REGISTROS];
	float totalCatGastos[MAX_REGISTROS];
	int numCatGastos = 0;
	float sumaGastos = 0;

	for (int i = 0; i < contadorGastos; i++) {
		bool encontrado = false;
		sumaGastos += historialGastos[i].monto;
		
		for (int j = 0; j < numCatGastos; j++) {
			if (catGastos[j] == historialGastos[i].categoria) {
				totalCatGastos[j] += historialGastos[i].monto;
				encontrado = true;
				break;
			}
		}
		if (!encontrado) {
			catGastos[numCatGastos] = historialGastos[i].categoria;
			totalCatGastos[numCatGastos] = historialGastos[i].monto;
			numCatGastos++;
		}
	}

	cout << "--- TOTAL DE GASTOS POR CATEGORIA ---\n";
	if (numCatGastos == 0) cout << "No hay gastos registrados.\n";
	for (int i = 0; i < numCatGastos; i++) {
		cout << left << setw(20) << guionesAEspacios(catGastos[i]) 
			 << " : S/ " << right << setw(8) << fixed << setprecision(2) << totalCatGastos[i] << "\n";
	}
	cout << "----------------------------------------\n";
	cout << left << setw(20) << "TOTAL GASTOS" << " : S/ " << right << setw(8) << sumaGastos << "\n\n";

	// Balance Final
	cout << "========================================\n";
	cout << left << setw(20) << "SALDO NETO" << " : S/ " << right << setw(8) << (sumaIngresos - sumaGastos) << "\n";
	cout << "========================================\n";

	pausaYLimpiar();
}

bool crearRegistro(Registro arreglo[], int &contador, string tipo) {
	system("cls");
	if (contador >= MAX_REGISTROS) {
		cout << "Error: Limite de registros alcanzado.\n";
		pausaYLimpiar();
		return false;
	}

	cout << "--- CREANDO REGISTRO DE " << tipo << " ---\n";
	
	float monto = inputMonto("Ingrese el monto", -1.0);
	string categoria = seleccionarCategoria(tipo, ""); 
	string descripcion = inputTexto("Ingrese una descripcion", "", false);
	
	int nuevoId;
	if (contador > 0) {
		nuevoId = arreglo[contador - 1].id + 1;
	} else {
		nuevoId = 1;
	}
	
	arreglo[contador] = Registro(nuevoId, categoria, descripcion, monto);
	contador++;

	cout << "\nSe creo el Registro exitosamente!\n";
	guardarDatos();
	pausaYLimpiar();
	return true;
}

void listarRegistros(Registro arreglo[], int contador, string titulo) {
	system("cls");
	cout << "--- LISTA DE " << titulo << " (" << contador << " registrados) ---\n\n";
	
	if (contador == 0) {
		cout << "Actualmente no hay ningun registro para mostrar.\n";
		pausaYLimpiar();
		return;
	}

	for (int i = 0; i < contador; i++) {
		char* dt = ctime(&arreglo[i].fecha);
		
		for (int j = 0; dt[j] != '\0'; j++) {
			if (dt[j] == '\n') {
				dt[j] = '\0';
				break;
			}
		}
		
		cout << "ID: " << arreglo[i].id 
			 << " | Fecha: " << dt
			 << " | Monto: S/ " << arreglo[i].monto << "\n"
			 << "    Cat: " << guionesAEspacios(arreglo[i].categoria) 
			 << " | Desc: " << guionesAEspacios(arreglo[i].descripcion) << "\n";
		cout << "------------------------------------------------\n";
			 
		if ((i + 1) % 10 == 0 && (i + 1) < contador) {
			cout << "\n--- Presione Enter para pasar a la pagina " << ((i+1)/10)+1 << " ---";
			cin.get(); 
			system("cls");
			cout << "--- LISTA DE " << titulo << " (Continuacion) ---\n\n";
		}
	}
	cout << "Fin de la lista.\n";
	pausaYLimpiar();
}

void modificarRegistro(Registro arreglo[], int contador, string tipo) {
	system("cls");
	if (contador == 0) {
		cout << "No hay registros para modificar.\n";
		pausaYLimpiar();
		return;
	}
	
	int idBuscado;
	bool encontrado = false;
	
	cout << "--- MODIFICAR " << tipo << " ---\n";
	cout << "Ingrese el ID que desea modificar: ";
	cin >> idBuscado;
	cin.ignore(256, '\n'); 
	
	for (int i = 0; i < contador; i++) {
		if (arreglo[i].id == idBuscado) {
			encontrado = true;
			cout << "\nModificando el ID " << idBuscado << "\n";
			
			arreglo[i].monto = inputMonto("Nuevo monto", arreglo[i].monto);
			arreglo[i].categoria = seleccionarCategoria(tipo, guionesAEspacios(arreglo[i].categoria));
			arreglo[i].descripcion = inputTexto("Nueva descripcion", guionesAEspacios(arreglo[i].descripcion), false);
			
			cout << "\nRegistro modificado con exito.\n";
			guardarDatos();
			break;
		}
	}
	
	if (!encontrado) cout << "\nError: No se encontro ningun registro con el ID " << idBuscado << ".\n";
	pausaYLimpiar();
}

void eliminarRegistro(Registro arreglo[], int &contador, string tipo) {
	system("cls");
	if (contador == 0) {
		cout << "No hay registros para eliminar.\n";
		pausaYLimpiar();
		return;
	}
	
	int idBuscado;
	bool encontrado = false;
	
	cout << "--- ELIMINAR " << tipo << " ---\n";
	cout << "Ingrese el ID que desea eliminar: ";
	cin >> idBuscado;
	cin.ignore(256, '\n');
	
	for (int i = 0; i < contador; i++) {
		if (arreglo[i].id == idBuscado) {
			encontrado = true;
			
			for (int j = i; j < contador - 1; j++) {
				arreglo[j] = arreglo[j + 1];
			}
			contador--;
			cout << "\nRegistro eliminado con exito.\n";
			guardarDatos();
			break;
		}
	}
	
	if (!encontrado) cout << "\nError: No se encontro ningun registro con el ID " << idBuscado << ".\n";
	pausaYLimpiar();
}

// ---------------------------------------------------------
// FUNCIONES DE ARCHIVOS
// ---------------------------------------------------------

void cargarDatos() {
	int _id;
	long long _fecha;
	char _cat[100], _desc[100];
	float _mon;

	FILE *archGastos = fopen("gastos.txt", "r");
	contadorGastos = 0;
	if (archGastos != NULL) {
		while (contadorGastos < MAX_REGISTROS && 
			   fscanf(archGastos, "%d %lld %99s %99s %f", &_id, &_fecha, _cat, _desc, &_mon) == 5) {
			historialGastos[contadorGastos].id = _id;
			historialGastos[contadorGastos].fecha = _fecha;
			historialGastos[contadorGastos].categoria = _cat; 
			historialGastos[contadorGastos].descripcion = _desc;
			historialGastos[contadorGastos].monto = _mon;
			contadorGastos++;
		}
		fclose(archGastos);
	}

	FILE *archIngresos = fopen("ingresos.txt", "r");
	contadorIngresos = 0;
	if (archIngresos != NULL) {
		while (contadorIngresos < MAX_REGISTROS && 
			   fscanf(archIngresos, "%d %lld %99s %99s %f", &_id, &_fecha, _cat, _desc, &_mon) == 5) {
			historialIngresos[contadorIngresos].id = _id;
			historialIngresos[contadorIngresos].fecha = _fecha;
			historialIngresos[contadorIngresos].categoria = _cat; 
			historialIngresos[contadorIngresos].descripcion = _desc;
			historialIngresos[contadorIngresos].monto = _mon;
			contadorIngresos++;
		}
		fclose(archIngresos);
	}
}

void guardarDatos() {
	FILE *archGastos = fopen("gastos.txt", "w");
	if (archGastos != NULL) {
		for (int i = 0; i < contadorGastos; i++) {
			string catGuardar = espaciosAGuiones(historialGastos[i].categoria);
			string descGuardar = espaciosAGuiones(historialGastos[i].descripcion);
			fprintf(archGastos, "%d %lld %s %s %.2f\n", 
					historialGastos[i].id, (long long)historialGastos[i].fecha, 
					catGuardar.c_str(), descGuardar.c_str(), historialGastos[i].monto);
		}
		fclose(archGastos);
	}

	FILE *archIngresos = fopen("ingresos.txt", "w");
	if (archIngresos != NULL) {
		for (int i = 0; i < contadorIngresos; i++) {
			string catGuardar = espaciosAGuiones(historialIngresos[i].categoria);
			string descGuardar = espaciosAGuiones(historialIngresos[i].descripcion);
			fprintf(archIngresos, "%d %lld %s %s %.2f\n", 
					historialIngresos[i].id, (long long)historialIngresos[i].fecha, 
					catGuardar.c_str(), descGuardar.c_str(), historialIngresos[i].monto);
		}
		fclose(archIngresos);
	}
}

// ---------------------------------------------------------
// UTILIDADES, MENUS Y VALIDACIONES
// ---------------------------------------------------------

void pausaYLimpiar() {
	cout << "\nPresione Enter para continuar...";
	cin.get(); 
}

string espaciosAGuiones(string str) {
	for (size_t i = 0; i < str.length(); i++) {
		if (str[i] == ' ') str[i] = '_';
	}
	return str;
}

string guionesAEspacios(string str) {
	for (size_t i = 0; i < str.length(); i++) {
		if (str[i] == '_') str[i] = ' ';
	}
	return str;
}

string seleccionarCategoria(string tipo, string valorActual) {
	int op;
	string seleccion = "";

	do {
		cout << "\n--- CATEGORIAS ---\n";
		if (valorActual != "") cout << "Categoria actual: " << valorActual << "\n\n";

		if (tipo == "Gasto") {
			cout << "1. Alimentacion\n";
			cout << "2. Transporte\n";
			cout << "3. Educacion\n";
			cout << "4. Recreativo\n";
			cout << "5. Salud\n";
			cout << "6. Proyectos / Hogar\n";
			cout << "7. Otra (Escribir manualmente)\n";
		} else {
			cout << "1. Trabajo / Sueldo\n";
			cout << "2. Apoyo / Donacion\n";
			cout << "3. Ventas\n";
			cout << "4. Otra (Escribir manualmente)\n";
		}
		
		if (valorActual != "") cout << "0. Mantener actual\n";

		cout << "Elija una opcion: ";
		cin >> op;
		cin.ignore(256, '\n');

		if (valorActual != "" && op == 0) return valorActual;

		if (tipo == "Gasto") {
			switch(op) {
				case 1: seleccion = "Alimentacion"; break;
				case 2: seleccion = "Transporte"; break;
				case 3: seleccion = "Educacion"; break;
				case 4: seleccion = "Recreativo"; break;
				case 5: seleccion = "Salud"; break;
				case 6: seleccion = "Proyectos"; break;
				case 7: seleccion = inputTexto("Escriba la nueva categoria", "", true); break;
				default: cout << "Opcion invalida.\n"; continue;
			}
		} else {
			switch(op) {
				case 1: seleccion = "Trabajo"; break;
				case 2: seleccion = "Donacion"; break;
				case 3: seleccion = "Ventas"; break;
				case 4: seleccion = inputTexto("Escriba la nueva categoria", "", true); break;
				default: cout << "Opcion invalida.\n"; continue;
			}
		}
		break; 
	} while (true);

	return seleccion;
}

float inputMonto(string mensaje, float valorActual) {
	float dato;
	do {
		flag = false;
		if (valorActual >= 0) cout << mensaje << " (Actual: " << valorActual << " | Ingrese '-1' para mantener): ";
		else cout << mensaje << ": ";
		
		cin >> dato;
		cin.ignore(256, '\n'); 
		
		if (dato == -1 && valorActual >= 0) return valorActual; 
		
		if (dato < 0) {
			cout << "ERROR: Ingrese un numero positivo.\n";
			flag = true;
		}
	} while (flag);
	return dato;
}

string inputTexto(string mensaje, string valorActual, bool obligatorio) {
	string dato;
	while (true) {
		if (valorActual != "") cout << mensaje << " (Actual: " << valorActual << " | Presione Enter para mantener): ";
		else cout << mensaje << " (Presione Enter para omitir): ";
		
		getline(cin, dato); 
		
		if (dato.empty()) {
			if (valorActual != "") return valorActual; 
			if (obligatorio) {
				cout << "ERROR: Este campo es obligatorio.\n";
				continue;
			} else {
				return "Sin_asignar"; 
			}
		}
		return dato;
	}
}
