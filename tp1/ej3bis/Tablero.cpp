#include "Tablero.h"
#include "assert.h"
#include <iostream>

using namespace std;

Tablero::Tablero() {
	_filas = 0;
	_columnas = 0;
	_posiciones_ocupadas = 0;
	_posiciones_recorridas = 0;
	_proxima_posicion_libre = Coord(0,0);
	_posiciones_vacias = 0;
	_tablero = Matriz(_filas, vector<Ficha>(_columnas, Ficha()));

}

Tablero::Tablero(int alto, int ancho) {
	_filas = alto;
	_columnas = ancho;
	_posiciones_ocupadas = 0;
	_posiciones_recorridas = 0;
	_proxima_posicion_libre = Coord(0,0);
	_posiciones_vacias = alto * ancho;
	_tablero = Matriz(_filas, vector<Ficha>(_columnas, Ficha()));
}

Tablero & Tablero::operator=(const Tablero& otra) {
	
	_filas = otra._filas;
	_columnas = otra._columnas;
	_posiciones_ocupadas = otra._posiciones_ocupadas;
	_posiciones_recorridas = otra._posiciones_recorridas;
	_proxima_posicion_libre = otra._proxima_posicion_libre;
	_posiciones_vacias = otra._posiciones_vacias;
	_tablero = Matriz(otra._tablero);
	
	return *this;

}

Tablero::Tablero(const Tablero& otro) {
	_filas = otro._filas;
	_columnas = otro._columnas;
	_posiciones_ocupadas = otro._posiciones_ocupadas;
	_posiciones_vacias = otro._posiciones_vacias;
	_tablero = Matriz(_filas, vector<Ficha>(_columnas, Ficha()));
	Matriz otro_tablero = otro._tablero;
	for(int i=0; i<_filas; i++) {
		vector<Ficha> columna = otro_tablero[i];
		for(int j=0; j<_columnas; j++) {
			Ficha ficha = columna[j];
			_tablero[i][j] = Ficha(ficha);
		}
	}
}

Tablero::~Tablero() {

}

bool Tablero::reject() {
	if(_posiciones_recorridas == (_filas * _columnas)){
		return true;
	}
	
	return false;
}

bool Tablero::accept(Tablero& mejor_tablero) {
	/* Si el tablero esta completo encontre una solucion inmejorable */
	if(completo()) {
		return true;
	}
	
	if(getPosicionesOcupadas() > mejor_tablero.getPosicionesOcupadas()) { 
		mejor_tablero = *this;
	}
	
	return false;
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
void Tablero::agregarFicha(Ficha& ficha) {
	Coord coord = getPosicionLibre();
	_tablero[coord.first][coord.second] = Ficha(ficha);
	
	if (!ficha.isVacia()){ 
		_posiciones_ocupadas++;
		_posiciones_vacias--;
	}
	_posiciones_recorridas++;
	
	_proxima_posicion_libre = Coord(_posiciones_recorridas / _filas, _posiciones_recorridas % _columnas);
	
	//cout << _posiciones_recorridas << endl;
	//cout << _proxima_posicion_libre.first << " " << _proxima_posicion_libre.second << endl;

}


/* La funcion quitarFicha debe recibir una coordenada del tablero y quitar la ficha de la misma.
   En caso de que la ficha que se encontraba en dicha posicion no fuese vacia debera decrementar
   las posiciones ocupadas e incrementar las vacias
*/
void Tablero::quitarFicha(Coord coord) {
	Ficha ficha = _tablero[coord.first][coord.second];
	_tablero[coord.first][coord.second] = Ficha();
	if(!ficha.isVacia()) _posiciones_ocupadas--, _posiciones_vacias++;
}
		
/* La funcion getPosicionesOcupadas debe retornar la cantidad de fichas no vacias colocadas en el tablero */
int Tablero::getPosicionesOcupadas() {
	return _posiciones_ocupadas;
}

Coord Tablero::getPosicionLibre() {
	return _proxima_posicion_libre;
}

/* La funcion getFicha debe, dada una coordenada, retornar la ficha que se encuentra en dicha posicion */
Ficha Tablero::getFicha(Coord coord) {

	assert(coord.first < _filas && coord.first >= 0
		&& coord.second < _columnas && coord.second >= 0);
	
	return _tablero[coord.first][coord.second];
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
			_tablero[i][j].print();
			cout << " ";
		}
		cout << endl;
	}
	
	cout << endl;
}
