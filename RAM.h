/*
 * Victor Hernández Pérez
 * alu0100697032@ull.edu.es
 * Grado en Ingeniería Informática
 * Curso: Tercero
 * Itinerario: Computación
 * Diseño y Análisis de Algoritmos
 */

#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream> 
#include <cstring>
#include <map>
using namespace std;

class instruccion {

private:
	string preEtiqueta;
	string nombre;
	string expresion;
public:

	instruccion() {
	}
	instruccion(string p, string n, string e);//etiqueta, nombre instruccion, expresion
	~instruccion();
	instruccion& operator =(instruccion *p1); //ASIGNAR VALORES AL VECTOR.
	void mostrar();

	//Getters
	string GetpreEtiqueta() {
		return preEtiqueta;
	}
	string Getnombre() {
		return nombre;
	}
	string Getexpresion() {
		return expresion;
	}
};

class RAM {

private:

	instruccion* programa;
	map<string, int> etiquetas;
	map<string, int> instrucciones;

public:

	RAM(const char* fichero);
	~RAM();
	void mostrarCarga();
	int ejecutar(int* cinta_entrada);
	void rellenarMapaInstrucciones();
};
