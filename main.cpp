/*
 * Victor Hernández Pérez
 * alu0100697032@ull.edu.es
 * Grado en Ingeniería Informática
 * Curso: Tercero
 * Itinerario: Computación
 * Diseño y Análisis de Algoritmos
 */

#include "RAM.h"

int main() {

	int size = 30;
	char programa[size];
	char cinta_entrada[size];
	string cinta_salida = "c_s.txt";
	/*cout << "Introduzca el nombre del programa que desea abrir: " << endl;
	fgets(programa, size, stdin);
	char *p;
	p = strchr(programa, '\n');
	if (p)
		*p = '\0';
	cout << endl;

	cout << "Introduzca el nombe del fichero de la cinta de entrada: " << endl;
	fgets(cinta_entrada, size, stdin);
	p = strchr(cinta_entrada, '\n');
	if (p)
		*p = '\0';
	cout << endl;

	cout << "Introduzca el nombre del fichero de la cinta de salida: " << endl;
	cin >> cinta_salida;
	cout << endl;*/

	//RAM maquina(programa, cinta_entrada, cinta_salida);
	RAM maquina("test2.ram", "c_e.txt", cinta_salida);

	bool parar_programa = false;
	char opcion;
	cout << "Menú:" << endl;
	cout << "r: ver los registros" << endl << "t: traza" << endl << "g: go"
			<< endl << "s: desensamblador" << endl << "i: ver cinta entrada"
			<< endl << "o: ver cinta salida" << endl << "h: ayuda" << endl
			<< "x: salir" << endl;

	while (parar_programa == false) {
		cin >> opcion;
		switch (opcion) {
		case 'r': {
			maquina.mostrarCarga();
		}
			break;
		case 't': {
			maquina.mostrarCarga();
		}
			break;
		case 'g': {
			maquina.ejecutar();
		}
			break;
		case 's': {

		}
			break;
		case 'i': {
			maquina.mostrar_cinta_entrada();
		}
			break;
		case 'o': {
			maquina.mostrar_cinta_salida();
		}
			break;
		case 'h': {
			cout << "Menú:" << endl;
			cout << "r: ver los registros" << endl << "t: traza" << endl
					<< "g: go" << endl << "s: desensamblador" << endl
					<< "i: ver cinta entrada" << endl << "o: ver cinta salida"
					<< endl << "h: ayuda" << endl << "x: salir" << endl;
		}
			break;
		case 'x': {
			parar_programa = true;
		}
			break;
		default:
			break;
		}
	}
	return 0;

}

