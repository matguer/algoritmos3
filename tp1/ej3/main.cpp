#include "Ficha.h"
#include "Tablero.h"
#include <vector>


int main() {

	Ficha* ficha2 = new Ficha(15,1,2,3,4);
	ficha2->setIzquierda(3);
	ficha2->setIzquierda(NO_COLOR);

	Tablero tablero(10, 5);
	Coord coord(0,0);
	tablero.agregarFicha(coord, *ficha2);
	tablero.print();
}
