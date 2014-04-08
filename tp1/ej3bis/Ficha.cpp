#include "Ficha.h"
#include "assert.h"
#include <iostream>

using namespace std;

Ficha::Ficha() {
	_numero = 0;
	_colores[SUPERIOR] = NO_COLOR;
	_colores[IZQUIERDA] = NO_COLOR;
	_colores[DERECHA] = NO_COLOR;
	_colores[INFERIOR] = NO_COLOR;
}

Ficha::Ficha(const Ficha& otra) {
	_numero = otra._numero;
	_colores[SUPERIOR] = otra._colores[SUPERIOR];
	_colores[IZQUIERDA] = otra._colores[IZQUIERDA];
	_colores[DERECHA] = otra._colores[DERECHA];
	_colores[INFERIOR] = otra._colores[INFERIOR];
}

Ficha::Ficha(int numero, Color superior, Color izquierda, Color derecha, Color inferior) {
	_numero = numero;
	_colores[SUPERIOR] = superior;
	_colores[IZQUIERDA] = izquierda;
	_colores[DERECHA] = derecha;
	_colores[INFERIOR] = inferior;

	/* validacion:
		Se corrobora que todos sean de un color o ninguno.
	*/
	int cant_no_color = 0;
	for(int i=0; i<4; i++) {
		if(_colores[i] == NO_COLOR) cant_no_color++;
	}
	assert((cant_no_color == 0) || (cant_no_color == 4));
	/* ! validacion */

}

bool Ficha::operator==(const Ficha& otra) {
	return (otra._numero == _numero);
}

Ficha & Ficha::operator=(const Ficha& otra) {

	_numero = otra._numero;
	_colores[SUPERIOR] = otra._colores[SUPERIOR];
	_colores[IZQUIERDA] = otra._colores[IZQUIERDA];
	_colores[DERECHA] = otra._colores[DERECHA];
	_colores[INFERIOR] = otra._colores[INFERIOR];
	
	return *this; 
}

Ficha::~Ficha() {
}

/* La funcion print debe imprimir el numero de ficha */
void Ficha::print() {
	cout << _numero;
}

void Ficha::printDetailed() {
	cout << " " << _colores[SUPERIOR] << endl;
	cout << _colores[IZQUIERDA] << " " << _colores[DERECHA] << endl;
	cout << " " << _colores[INFERIOR] << endl;
}

/* La funcion getLado debe recibir uno de los cuatros lados de la ficha
   y retornar el color del lado correspondiente
*/
Color Ficha::getLado(Lado lado) {
	return _colores[lado];
}

/* La funcion getNumero debe retornar el numero de la ficha */
int Ficha::getNumero() {
	return _numero;
}

/* La funcion isVacia debe retornar un booleano indicando si la ficha es vacia o no */
bool Ficha::isVacia() {
	return _colores[SUPERIOR] == NO_COLOR;
}
