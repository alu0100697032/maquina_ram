/*
 * Victor Hernández Pérez
 * alu0100697032@ull.edu.es
 * Grado en Ingeniería Informática
 * Curso: Tercero
 * Itinerario: Computación
 * Diseño y Análisis de Algoritmos
 */

#include "RAM.h"
/*
 * CONSTRUCTOR INSTRUCCION
 */
instruccion::instruccion(string p, string n, string e) {

	if (n.empty() == true && e.empty() == true) {
		preEtiqueta.clear();
		expresion.clear();
		nombre = p;
	} else if (e.empty() == true) { //si no tiene etiqueta...
		preEtiqueta.clear();
		nombre = p;
		expresion = n;
	} else {				//si tiene etiqueta...
		preEtiqueta = p;
		nombre = n;
		expresion = e;
	}

}
/*
 * DESTRUCTOR INSTRUCCION
 */
instruccion::~instruccion() {

	preEtiqueta.clear();
	nombre.clear();
	expresion.clear();

}
/*
 * SOBRECARGA DEL OPERADOR =
 */
instruccion& instruccion::operator =(instruccion *p1) {

	this->preEtiqueta = p1->preEtiqueta;
	this->nombre = p1->nombre;
	this->expresion = p1->expresion;

	return *this;
}
/*
 * MUESTRA INSTRUCCION
 */
void instruccion::mostrar() {

	if (preEtiqueta.empty() == false)
		cout << preEtiqueta << " " << nombre << " " << expresion << endl;
	else
		cout << nombre << " " << expresion << endl;
}
/*
 * CONSTRUCTOR MAQUINA RAM
 */
RAM::RAM(const char* fichero) {

	ifstream fin(fichero);

	string linea;					  	// Línea leida.
	int contador = 0;    		// Némero de instrucción leída. (1º,2º...)
	programa = new instruccion[40]; // Buscar forma dinámica para reservar memoria. Esto no es lo más eficiente.

	if (fin.is_open()) {

		getline(fin, linea);

		while (!fin.eof()) {
			getline(fin, linea);

			if (linea.length() == 0 || linea[0] == ';') // Ignoramos comentarios
				continue;
			else { 		// si la línea no es un comentario o no está vacía:

				int i = 0; // Indicará por cual caracter del string "linea" va leyendo.
				string aux1;			//almacena primer elemento
				string aux2;			//almacena segundo elemento
				string aux3;		//almacena tercer elemento (si es que hay)
				//(Etiqueta, nombre, expreseión)

				while (linea[i] == ' ') //ignora espacios
					i++;

				while (linea[i] != ' ') {
					if (linea[i] == ':') { // si encuentra ':' encontró etiqueta
						i++;
						etiquetas[aux1] = contador;
						break;
					}

					aux1 = aux1 + linea[i];
					i++;
					if (linea[i] == '\0') // puede ocurrir que no haya mas que leer en la cadena.
						break;
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

				if (linea[i] != '\0') { 	//Si todavía hay más por leer...
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
			} 		// end else (si lee otra cosa que no es comentario)

		} 		//fin de fichero

	} else { 		//Si no encuentra fichero:
		cout << "Error, no se pudo cargar el archivo o no existe." << endl;
		exit(0);
	}
	rellenarMapaInstrucciones();
}
/*
 * DESTRUCTOR MAQUINA RAM
 */
RAM::~RAM() {

	delete[] programa;

}

int RAM::ejecutar(int* cinta_entrada) {
	bool parar = false;
	int contador = 0;
	int acumulador = 0;
	int cabezal = 0;
	while (parar == false) {
		if (programa[contador].GetpreEtiqueta().empty()) {
			switch (instrucciones[programa[contador].Getnombre()]) {
			case 1: { //LOAD
				if (programa[contador].Getexpresion()[0] == '=') {
					acumulador = int(programa[contador].Getexpresion()[1]);
				} else if (programa[contador].Getexpresion()[0] == '*') {
					acumulador = cinta_entrada[cinta_entrada[int(
							programa[contador].Getexpresion()[1])]];
				} else {
					acumulador = cinta_entrada[int(
							programa[contador].Getexpresion()[0])];
				}
				contador++;
			}
				break;
			case 2: { //STORE
				if (programa[contador].Getexpresion()[0] == '*') {
					cinta_entrada[cinta_entrada[cinta_entrada[int(
							programa[contador].Getexpresion()[1])]]] =
							acumulador;
				} else {
					cinta_entrada[cinta_entrada[int(
							programa[contador].Getexpresion()[1])]] =
							acumulador;
				}
				contador++;
			}
				break;
			case 3: { //ADD

			}
				break;
			case 4: { //SUB

			}
				break;
			case 5: { //MULT

			}
				break;
			case 6: { //DIV

			}
				break;
			case 7: { //READ
				if (programa[contador].Getexpresion()[0] == '*') {
					cinta_entrada[cabezal + 1] =
							cinta_entrada[cinta_entrada[int(
									programa[contador].Getexpresion()[1])]];
					cabezal++;
				} else {
					cinta_entrada[cabezal + 1] = cinta_entrada[int(
							programa[contador].Getexpresion()[1])];
					cabezal++;
				}
				contador++;
			}
				break;
			case 8: { //WRITE

			}
				break;
			case 9: { //JUMP
				if (programa[contador].Getexpresion()[0] == '=') {
					acumulador = int(programa[contador].Getexpresion()[1]);
				} else if (programa[contador].Getexpresion()[0] == '*') {
					acumulador = int(programa[contador].Getexpresion()[1]);
				} else if (int(programa[contador].Getexpresion()[0]) >= 0) {

				}
			}
				break;
			case 10: { //JGTZ
				if (programa[contador].Getexpresion()[0] == '=') {
					acumulador = int(programa[contador].Getexpresion()[1]);
				} else if (programa[contador].Getexpresion()[0] == '*') {
					acumulador = int(programa[contador].Getexpresion()[1]);
				} else if (int(programa[contador].Getexpresion()[0]) >= 0) {

				}
			}
				break;
			case 11: { //JZERO
				if (programa[contador].Getexpresion()[0] == '=') {
					acumulador = int(programa[contador].Getexpresion()[1]);
				} else if (programa[contador].Getexpresion()[0] == '*') {
					acumulador = int(programa[contador].Getexpresion()[1]);
				} else if (int(programa[contador].Getexpresion()[0]) >= 0) {

				}
			}
				break;
			case 12: //HALT
				parar = true;
				break;
			default:
				parar = true;
				break;
			}
		} else
			contador = etiquetas[programa[contador].GetpreEtiqueta()];
	}
	return acumulador;
}
void RAM::rellenarMapaInstrucciones() {
	instrucciones["LOAD"] = 1;
	instrucciones["STORE"] = 2;
	instrucciones["ADD"] = 3;
	instrucciones["SUB"] = 4;
	instrucciones["MULT"] = 5;
	instrucciones["DIV"] = 6;
	instrucciones["READ"] = 7;
	instrucciones["WRITE"] = 8;
	instrucciones["JUMP"] = 9;
	instrucciones["JGTZ"] = 10;
	instrucciones["JZERO"] = 11;
	instrucciones["HALT"] = 12;
}
/*
 * MUESTRA EL PROGRAMA
 */
void RAM::mostrarCarga() {

	for (int i = 0; i < 40; i++)
		programa[i].mostrar();

}
