#include "Tablero.h"
#include "assert.h"
#include <iostream>

using namespace std;

Tablero::Tablero() {
}

Tablero::Tablero(int alto, int ancho) {
	_filas = alto;
	_columnas = ancho;
	_posiciones_ocupadas = 0;
	_posiciones_vacias = alto * ancho;
	_tablero = new Matriz(_filas, Vec(_columnas, new Ficha()));
}

Tablero::Tablero(const Tablero& otro) {
	_filas = otro._filas;
	_columnas = otro._columnas;
	_posiciones_ocupadas = otro._posiciones_ocupadas;
	_posiciones_vacias = otro._posiciones_vacias;
	_tablero = new Matriz(_filas, Vec(_columnas, new Ficha()));
	Matriz* otro_tablero = otro._tablero;
	for(int i=0; i<_filas; i++) {
		Vec columna = (*otro_tablero)[i];
		for(int j=0; j<_columnas; j++) {
			Ficha* ficha = columna[j];
			(*_tablero)[i][j] = new Ficha(*ficha);
		}
	}
}

Tablero::~Tablero() {
	//to do
	//for(int i=0; i<_filas; i++) {
	//	Vec fila = (*_tablero)[i];
	//	cout << "paso 1" << endl;
	//	Ficha* ficha_actual;
	//	while(!fila.empty()) { 
	//	cout << "paso 2" << endl;
	//		ficha_actual = fila.back();
	//		if (ficha_actual != NULL) {
	//			cout << "paso 3" << endl;
	//			ficha_actual->print();
	//			delete ficha_actual;
	//		}
	//		fila.pop_back();
	//	}
	//}
}


/* La funcion getFilas debe retornar la cantidad de filas del tablero */
int Tablero::getFilas() {
	return _filas;
}

/* La funcion getColumnas debe retornar la cantidad de columnas del tablero */
int Tablero::getColumnas() {
	return _columnas;
}

/* La funcion agregarFicha debe recibir una coordenada del tablero y una ficha y agregar
   la misma en la coordenada indicada. A su vez si la ficha agregada no es vacia debe 
   incrementar la cantidad de posiciones ocupadas y decrementar las vacias
*/
void Tablero::agregarFicha(Coord coord, Ficha& ficha) {
	(*_tablero)[coord.first][coord.second] = new Ficha(ficha);
	if (!ficha.isVacia()) _posiciones_ocupadas++, _posiciones_vacias--;
}


/* La funcion quitarFicha debe recibir una coordenada del tablero y quitar la ficha de la misma.
   En caso de que la ficha que se encontraba en dicha posicion no fuese vacia debera decrementar
   las posiciones ocupadas e incrementar las vacias
*/
void Tablero::quitarFicha(Coord coord) {
	Ficha ficha = *((*_tablero)[coord.first][coord.second]);
	(*_tablero)[coord.first][coord.second] = new Ficha();
	if(!ficha.isVacia()) _posiciones_ocupadas--, _posiciones_vacias++;
}
		
/* La funcion getCantidadFichas debe retornar la cantidad de fichas no vacias colocadas en el tablero */
int Tablero::getCantidadFichas() {
	return _posiciones_ocupadas;
}


/* La funcion getFicha debe, dada una coordenada, retornar la ficha que se encuentra en dicha posicion */
Ficha Tablero::getFicha(Coord coord) {

	assert(coord.first < _filas && coord.first >= 0
		&& coord.second < _columnas && coord.second >= 0);
	
	return *(*_tablero)[coord.first][coord.second];
}


/* La funcion siguientePosicion debe, dada una coordenada, retornar la siguiente posicion del tablero
   siguiendo un recorrido de izquierda a derecha y de arriba hacia abajo
*/
Coord Tablero::siguientePosicion(Coord coord) {
	
	assert(coord.first < _filas && coord.first >= -1
		&& coord.second < _columnas && coord.second >= -1);

	if(coord.first == -1 && coord.second == -1) return Coord(0,0);
	if((coord.first == _filas - 1) && (coord.second == _columnas - 1)) return Coord(-1,-1);
	else {
		coord.second++;
		if(coord.second == _columnas) coord.first++;
		return Coord((coord.first) % _filas, (coord.second) % _columnas);
	}
}		


/* La funcion posicionesRecorridas debe, dada una coordenada, retornar la cantidad de posiciones recorridas
   en el tablero hasta llegar a dicha posicion
*/
int Tablero::posicionesRecorridas(Coord coord) {

	assert(coord.first < _filas && coord.first >= -1
		&& coord.second < _columnas && coord.second >= -1);

	if(coord.first == -1 && coord.second == -1) return 0;
	return coord.first * _columnas + coord.second + 1;

}


/* La funcion completo debe retornar un booleano indicando si el tablero se encuentra o no completo */
bool Tablero::completo() {
	return (_posiciones_ocupadas == (_filas * _columnas));
}


/* La funcion print debe imprimir el contenido del tablero */
void Tablero::print() {
	for(int i=0; i<_filas; i++) {
		for(int j=0; j<_columnas; j++) {
			//cout << (*_tablero)[i][j];
			(*_tablero)[i][j]->print();
			cout << " ";
		}
		cout << endl;
	}
}
