#include "RAM.h"

instruccion::instruccion(string p, string n, string e) {

	if (e.empty() == true) {
		preEtiqueta.clear();
		nombre = p;
		expresion = n;
	} else {
		preEtiqueta = p;
		nombre = n;
		expresion = e;
	}

}

instruccion::~instruccion() {

	preEtiqueta.clear();
	nombre.clear();
	expresion.clear();

}

instruccion& instruccion::operator =(instruccion *p1) {

	this->preEtiqueta = p1->preEtiqueta;
	this->nombre = p1->nombre;
	this->expresion = p1->expresion;

	return *this;
}

void instruccion::mostrar() {

	if (preEtiqueta.empty() == false)
		cout << preEtiqueta << " " << nombre << " " << expresion << endl;
	else
		cout << nombre << " " << expresion << endl;
}

RAM::RAM(const char* fichero) {

	ifstream fin(fichero);

	string linea;					  	// Línea leida.
	int contador = 0;    				// Némero de instrucción leída. (1º,2º...)
	programa = new instruccion[40]; 	// Buscar forma dinámica para reservar memoria. Esto no es lo más eficiente.

	if (fin.is_open()) {

		getline(fin, linea);

		while (!fin.eof()) {
			getline(fin, linea);

			if (linea.length() == 0 || linea[0] == ';') // Ignoramos comentarios
				continue;
			else { 			// si la línea no es un comentario o no está vacía:

				int i = 0;// Indicará por cual caracter del string "linea" va leyendo.
				string aux1;			//almacena primer elemento
				string aux2;			//almacena segundo elemento
				string aux3;		//almacena tercer elemento (si es que hay)
				//(Etiqueta, nombre, expreseión)

				while (linea[i] == ' ')
					i++;

				while (linea[i] != ' ') {
					if (linea[i] == ':') { // si encuentra los':' sale del bucle (encontro etiqueta).
						i++;
						break;
					}

					aux1 = aux1 + linea[i];
					i++;
				}

				while (linea[i] == ' ') { // bucle para buscar la 2ª entrada, ignorando los espacios y los ':'
					i++;
					if (linea[i] == ':')
						i++;
				}

				while (linea[i] != ' ') {

					aux2 = aux2 + linea[i];
					i++;
					if (linea[i] == '\0') // puede ocurrir que no haya mas que leer en la cadena.
						break;

				}

				if (linea[i] != '\0') { 		//Si todavía hay más por leer...
					i++;
					while (linea[i] != ' ') {
						aux3 = aux3 + linea[i];
						i++;
						if (linea[i] == '\0')
							break;
					}
				}
				//se almacena la instruccion
				programa[contador] = new instruccion(aux1, aux2, aux3);
				contador++;
			}// end else (si lee otra cosa que no es comentario)

		}//fin de fichero

	} else {//Si no encuentra fichero:
		cout << "Error, no se pudo cargar el archivo o no existe." << endl;
		exit(0);
	}

}
RAM::~RAM() {

	delete[] programa;

}

void RAM::mostrarCarga() {

	for (int i = 0; i < 40; i++)
		programa[i].mostrar();

}
