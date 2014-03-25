#include "Tablero.h"

using namespace std;

Tablero::Tablero(int alto, int ancho) {
	_alto = alto;
	_ancho = ancho;
	Matriz _tablero(_alto, Vec(_ancho, Ficha()));
}

Tablero::~Tablero() {

}

void Tablero::agregarFicha(Coord coord, Ficha ficha) {
	_tablero[coord.first][coord.second] = ficha;
}

void Tablero::quitarFicha(Coord coord) {
	_tablero[coord.first][coord.second] = Ficha();
}

void Tablero::imprimir() {

}
