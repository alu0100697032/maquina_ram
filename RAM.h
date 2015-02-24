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
#include <vector>
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

	vector<instruccion> programa;
	vector<int> cinta_entrada;
	vector<int> cinta_salida;
	string nombre_fichero_salida;
	map<string, int> etiquetas;
	map<string, int> instrucciones;

public:

	RAM(const char* fichero, const char* c_e, string c_s);
	~RAM();
	void mostrarCarga();
	void mostrar_cinta_entrada();
	void mostrar_cinta_salida();
	void ejecutar();
	void rellenarMapaInstrucciones();
	void mostrarEtiquetas();
};
