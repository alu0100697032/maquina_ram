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

	/*if (n.empty() == true && e.empty() == true) {
	 preEtiqueta.clear();
	 expresion.clear();
	 nombre = p;
	 } */
	if (e.empty() == true) { //si no tiene etiqueta...
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
RAM::RAM(const char* fichero, const char* c_e, string c_s) {

	nombre_fichero_salida = c_s;
	ifstream fin(fichero);
	ifstream fin2(c_e);
	string linea;					  	// Línea leida.
	int contador = 0;    		// Némero de instrucción leída. (1º,2º...)
	//programa = new instruccion[40]; // Buscar forma dinámica para reservar memoria. Esto no es lo más eficiente.
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
						//etiquetas[aux1] = contador;
						etiquetas.insert(pair<string, int>(aux1, contador));
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
				instruccion aux(aux1, aux2, aux3);
				programa.push_back(aux);
				//programa[contador] = new instruccion(aux1, aux2, aux3);
				contador++;
			} 		// end else (si lee otra cosa que no es comentario)
		} 		//fin de fichero

	} else { 		//Si no encuentra fichero:
		cout << "Error, no se pudo cargar el archivo o no existe." << endl;
		exit(0);
	}
	if (fin2.is_open()) {
		int aux;
		while (!fin2.eof()) {
			fin2 >> aux;
			cinta_entrada.push_back(aux);
		}
	} else {
		cout << "Error, no se pudo cargar el archivo o no existe." << endl;
		exit(0);
	}
	rellenarMapaInstrucciones();
	mostrarEtiquetas();
}
/*
 * DESTRUCTOR MAQUINA RAM
 */
RAM::~RAM() {

	programa.clear();

}

void RAM::ejecutar() {
	bool parar = false;
	int contador = 0;
	int acumulador = 0;
	int cabezal = 0;
	string aux;
	while (parar == false) {
		if (programa[contador].GetpreEtiqueta().empty()) {
			switch (instrucciones[programa[contador].Getnombre()]) {
			case 1: { //LOAD
				aux = programa[contador].Getexpresion();
				if (programa[contador].Getexpresion()[0] == '=') {
					aux.erase(0, 1);
					acumulador = atoi(aux.c_str());
				} else if (programa[contador].Getexpresion()[0] == '*') {
					aux.erase(0, 1);
					acumulador = cinta_entrada[cinta_entrada[atoi(aux.c_str())
							- 1]];
				} else {
					acumulador = cinta_entrada[atoi(aux.c_str()) - 1];
				}
				contador++;
			}
				break;
			case 2: { //STORE
				aux = programa[contador].Getexpresion();
				if (programa[contador].Getexpresion()[0] == '*') {
					aux.erase(0, 1);
					cinta_entrada[cinta_entrada[atoi(aux.c_str()) - 1]] =
							acumulador;
				} else {
					cinta_entrada[atoi(aux.c_str()) - 1] = acumulador;
				}
				contador++;
			}
				break;
			case 3: { //ADD
				aux = programa[contador].Getexpresion();
				if (programa[contador].Getexpresion()[0] == '=') {
					aux.erase(0, 1);
					acumulador += atoi(aux.c_str());
				} else if (programa[contador].Getexpresion()[0] == '*') {
					aux.erase(0, 1);
					acumulador += cinta_entrada[cinta_entrada[atoi(aux.c_str())
							- 1]];
				} else {
					acumulador += cinta_entrada[atoi(aux.c_str()) - 1];
				}
				contador++;
			}
				break;
			case 4: { //SUB
				aux = programa[contador].Getexpresion();
				if (programa[contador].Getexpresion()[0] == '=') {
					aux.erase(0, 1);
					acumulador = acumulador - atoi(aux.c_str());
				} else if (programa[contador].Getexpresion()[0] == '*') {
					aux.erase(0, 1);
					acumulador =
							acumulador
									- cinta_entrada[cinta_entrada[atoi(
											aux.c_str()) - 1]];
				} else {
					acumulador = acumulador
							- cinta_entrada[atoi(aux.c_str()) - 1];
				}
				contador++;
			}
				break;
			case 5: { //MULT
				aux = programa[contador].Getexpresion();
				if (programa[contador].Getexpresion()[0] == '=') {
					aux.erase(0, 1);
					acumulador = acumulador * atoi(aux.c_str());
				} else if (programa[contador].Getexpresion()[0] == '*') {
					aux.erase(0, 1);
					acumulador =
							acumulador
									* cinta_entrada[cinta_entrada[atoi(
											aux.c_str()) - 1]];
				} else {
					acumulador = acumulador
							* cinta_entrada[atoi(aux.c_str()) - 1];
				}
				contador++;
			}
				break;
			case 6: { //DIV
				aux = programa[contador].Getexpresion();
				if (programa[contador].Getexpresion()[0] == '=') {
					aux.erase(0, 1);
					if (atoi(aux.c_str()) != 0)
						acumulador = acumulador / atoi(aux.c_str());
					else {
						cout << "División entre 0. Error" << endl;
						parar = true;
					}
				} else if (programa[contador].Getexpresion()[0] == '*') {
					aux.erase(0, 1);
					if (atoi(aux.c_str()) != 0)
						acumulador = acumulador
								/ cinta_entrada[cinta_entrada[atoi(aux.c_str())
										- 1]];
					else {
						cout << "División entre 0. Error" << endl;
						parar = true;
					}

				} else {
					if (atoi(aux.c_str()) != 0)
						acumulador = acumulador
								/ cinta_entrada[atoi(aux.c_str()) - 1];
					else {
						cout << "División entre 0. Error" << endl;
						parar = true;
					}

				}
				contador++;
			}
				break;
			case 7: { //READ
				aux = programa[contador].Getexpresion();
				if (programa[contador].Getexpresion()[0] == '*') {
					aux.erase(0, 1);
					cinta_entrada[cabezal + 1] =
							cinta_entrada[cinta_entrada[atoi(aux.c_str()) - 1]];
					cabezal++;
				} else {
					cinta_entrada[cabezal + 1] = cinta_entrada[atoi(aux.c_str())
							- 1];
					cabezal++;
				}
				contador++;
			}
				break;
			case 8: { //WRITE

			}
				break;
			case 9: { //JUMP
				/*aux = programa[contador].Getexpresion();
				contador = etiquetas.find(aux)->second;*/
				contador++;
			}
				break;
			case 10: { //JGTZ
				if (acumulador > 0) {
					aux = programa[contador].Getexpresion();
					contador = etiquetas.find(aux)->second;
				}
			}
				break;
			case 11: { //JZERO
				if (acumulador == 0) {
					aux = programa[contador].Getexpresion();
					contador = etiquetas.find(aux)->second;
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
		mostrar_cinta_entrada();
	}
	cout << acumulador << endl;
}
void RAM::rellenarMapaInstrucciones() {
	instrucciones.insert(pair<string, int>("LOAD", 1));
	instrucciones.insert(pair<string, int>("STORE", 2));
	instrucciones.insert(pair<string, int>("ADD", 3));
	instrucciones.insert(pair<string, int>("SUB", 4));
	instrucciones.insert(pair<string, int>("MULT", 5));
	instrucciones.insert(pair<string, int>("DIV", 6));
	instrucciones.insert(pair<string, int>("READ", 7));
	instrucciones.insert(pair<string, int>("WRITE", 8));
	instrucciones.insert(pair<string, int>("JUMP", 9));
	instrucciones.insert(pair<string, int>("JGTZ", 10));
	instrucciones.insert(pair<string, int>("JZERO", 11));
	instrucciones.insert(pair<string, int>("HALT", 12));

	/*instrucciones["STORE"] = 2;
	instrucciones["ADD"] = 3;
	instrucciones["SUB"] = 4;
	instrucciones["MULT"] = 5;
	instrucciones["DIV"] = 6;
	instrucciones["READ"] = 7;
	instrucciones["WRITE"] = 8;
	instrucciones["JUMP"] = 9;
	instrucciones["JGTZ"] = 10;
	instrucciones["JZERO"] = 11;
	instrucciones["HALT"] = 12;*/

}
/*
 * MUESTRA EL PROGRAMA
 */
void RAM::mostrarCarga() {

	for (int i = 0; i < programa.size(); i++)
		programa[i].mostrar();

}

void RAM::mostrar_cinta_entrada() {
	cout << "Cinta entrada: " << endl;
	for (int i = 0; i < cinta_entrada.size(); i++) {
		cout << cinta_entrada[i] << " ";
	}
}

void RAM::mostrar_cinta_salida() {
	cout << "Cinta salida: " << endl;
	for (int i = 0; i < cinta_salida.size(); i++) {
		cout << cinta_salida[i] << " ";
	}
}

void RAM::mostrarEtiquetas() {

	map<string,int>::iterator it = etiquetas.begin();
	for (it = etiquetas.begin(); it != etiquetas.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
}
