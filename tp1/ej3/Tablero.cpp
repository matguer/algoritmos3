#include "Tablero.h"
#include <iostream>

using namespace std;

Tablero::Tablero(int alto, int ancho) {
	_alto = alto;
	_ancho = ancho;
	_tablero = new Matriz(_alto, Vec(_ancho, new Ficha()));
}

Tablero::~Tablero() {

}

void Tablero::agregarFicha(Coord coord, Ficha& ficha) {
	(*_tablero)[coord.first][coord.second] = new Ficha(ficha);
}

void Tablero::quitarFicha(Coord coord) {
	(*_tablero)[coord.first][coord.second] = new Ficha();
}

void Tablero::print() {
	for(int i=0; i<_alto; i++) {
		for(int j=0; j<_ancho; j++) {
			(*_tablero)[i][j]->print();
			cout << " ";
		}
		cout << endl;
	}
}
