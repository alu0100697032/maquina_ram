#include "RAM.h"

int main() {

	int size = 30;
	char fichero[size];

	cout << "Introduzca el fichero que desea abrir: ";
	fgets(fichero, size, stdin);
	/* Buscar la captura del retorno de carro para convertirlo en el "final de cadena"
	 * Corrige el resultado de fgets.*/
	char *p;
	p = strchr(fichero, '\n');
	if (p)
		*p = '\0';
	cout << endl;

	RAM maquina(fichero);
	maquina.mostrarCarga();
	return 0;

}

