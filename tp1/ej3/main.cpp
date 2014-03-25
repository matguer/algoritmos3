#include "Ficha.h"
#include "Tablero.h"
#include <vector>


int main() {

	Ficha ficha;
	ficha.print();

	Ficha* ficha2 = new Ficha(1,2,3,4);
	ficha2->print();
	ficha2->setIzquierda(3);
	ficha2->print();
	ficha2->setIzquierda(NO_COLOR);
	ficha2->print();

	Tablero tablero(10, 5);
}
