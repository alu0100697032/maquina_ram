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
	char fichero[size];
	int cintaEntrada[8] = { 1, 1, 1, 0, 0, 0, 0, 0 };
	cout << "Introduzca el fichero que desea abrir: " << endl;
	fgets(fichero, size, stdin);
	/* Buscar la captura del retorno de carro para convertirlo en el "final de cadena"
	 * Corrige el resultado de fgets.*/
	char *p;
	p = strchr(fichero, '\n');
	if (p)
		*p = '\0';
	cout << endl;

	RAM maquina(fichero);
	//maquina.mostrarCarga();
	cout << maquina.ejecutar(cintaEntrada) << endl;
	return 0;

}

