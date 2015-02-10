#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream> 
#include <cstring>

using namespace std;

class instruccion {

private:
	string preEtiqueta;
	string nombre;
	string expresion;
public:

	instruccion() {}             // Constructor por defecto
	instruccion(string p, string n, string e); // En el caso de que la instruccion tenga etiqueta.
	~instruccion();
	instruccion& operator =(instruccion *p1); // MUY IMPORTANTE PARA PODER ASIGNAR VALORES AL VECTOR.
	string GetpreEtiqueta() {
		return preEtiqueta;
	}
	string Getnombre() {
		return nombre;
	}
	string Getexpresion() {
		return expresion;
	}
	void mostrar();

};

class RAM {

private:

	instruccion* programa;

public:

	RAM(const char* fichero);
	~RAM();
	void mostrarCarga();
};
