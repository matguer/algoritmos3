#include "Tablero.h"
#include "assert.h"
#include <iostream>

using namespace std;

Tablero::Tablero() {	// O(n*m)
	_filas = 0;								// O(1)
	_columnas = 0;								// O(1)
	_posiciones_ocupadas = 0;						// O(1)
	_posiciones_recorridas = 0;						// O(1)
	_proxima_posicion_libre = Coord(0,0);					// O(1)
	_posiciones_vacias = 0;							// O(1)
	_tablero = Matriz(_filas, vector<Ficha>(_columnas, Ficha()));		// O(n*m)

}

Tablero::Tablero(int alto, int ancho) {	// O(n*m)
	_filas = alto;								// O(1)
	_columnas = ancho;							// O(1)
	_posiciones_ocupadas = 0;						// O(1)
	_posiciones_recorridas = 0;						// O(1)
	_proxima_posicion_libre = Coord(0,0);					// O(1)
	_posiciones_vacias = alto * ancho;					// O(1)
	_tablero = Matriz(_filas, vector<Ficha>(_columnas, Ficha()));		// O(n*m)
}

Tablero & Tablero::operator=(const Tablero& otra) {	// O(n*m)
	
	_filas = otra._filas;							// O(1)
	_columnas = otra._columnas;						// O(1)
	_posiciones_ocupadas = otra._posiciones_ocupadas;			// O(1)
	_posiciones_recorridas = otra._posiciones_recorridas;			// O(1)
	_proxima_posicion_libre = otra._proxima_posicion_libre;			// O(1)
	_posiciones_vacias = otra._posiciones_vacias;				// O(1)
	_tablero = Matriz(otra._tablero);					// O(n*m)
	
	return *this;

}

Tablero::Tablero(const Tablero& otro) {		// O(n*m)
	_filas = otro._filas;							// O(1)
	_columnas = otro._columnas;						// O(1)
	_posiciones_recorridas = otro._posiciones_recorridas;			// O(1)
	_posiciones_ocupadas = otro._posiciones_ocupadas;			// O(1)
	_posiciones_vacias = otro._posiciones_vacias;				// O(1)
	_proxima_posicion_libre = otro._proxima_posicion_libre;			// O(1)
	_tablero = Matriz(_filas, vector<Ficha>(_columnas, Ficha()));		// O(n*m)
	Matriz otro_tablero = otro._tablero;					// O(n*m)
	for(int i=0; i<_filas; i++) {						// O(n)
		vector<Ficha> columna = otro_tablero[i];			// O(1)
		for(int j=0; j<_columnas; j++) {				// O(m)
			Ficha ficha = columna[j];				// O(1)
			_tablero[i][j] = Ficha(ficha);				// O(1)
		}
	}
}

Tablero::~Tablero() {

}

bool Tablero::reject(Tablero& mejor_tablero) {	// O(1)
		
	// PODA: Si en este tablero puedo poner menos fichas en el mejor de los casos que el mejor tablero, lo descarto
	if(_posiciones_ocupadas + getPosicionesPorRecorrer() <= mejor_tablero.getPosicionesOcupadas()){					// O(1)
		return true;														// O(1)
	}

	return false;															// O(1)
}

bool Tablero::accept(Tablero& mejor_tablero) {	// O(n*m)
	
	// Voy guardando el mejor tablero
	if(getPosicionesOcupadas() > mejor_tablero.getPosicionesOcupadas()){								// O(1)
		mejor_tablero = *this;													// O(n*m)
	}
	
	/* Si el tablero esta completo encontre una solucion inmejorable */
	if(completo()) {														// O(1)
		mejor_tablero = *this;													// O(n*m)
		return true;														// O(1)
	}
	
	return false;															// O(1)
}

pair<Color,Color> Tablero::restriccionFicha(Coord coord){
	
	pair<Color, Color> result(NO_COLOR,NO_COLOR);											// O(1)
	
	if(coord == Coord(0,0)){													// O(1)
		return result;														// O(1)
	}
	
	// Reviso la posicion a la izquierda
	if(coord.second > 0 && (_tablero[coord.first][coord.second-1]).getLado(DERECHA) != NO_COLOR){					// O(1)
		result.first = (_tablero[coord.first][coord.second-1]).getLado(DERECHA);						// O(1)
	}
	
	// Reviso la posicion de arriba
	if(coord.first > 0 && (_tablero[coord.first-1][coord.second]).getLado(INFERIOR) != NO_COLOR){					// O(1)
		result.second = (_tablero[coord.first-1][coord.second]).getLado(INFERIOR);						// O(1)
	}
	
	return result;															// O(1)
}

/* La funcion getFilas debe retornar la cantidad de filas del tablero */
int Tablero::getFilas() {	// O(1)
	return _filas;		// O(1)
}

/* La funcion getColumnas debe retornar la cantidad de columnas del tablero */
int Tablero::getColumnas() {	// O(1)
	return _columnas;	// O(1)
}

/* La funcion agregarFicha debe recibir una coordenada del tablero y una ficha y agregar
   la misma en la coordenada indicada. A su vez si la ficha agregada no es vacia debe 
   incrementar la cantidad de posiciones ocupadas y decrementar las vacias
*/
void Tablero::agregarFicha(Ficha ficha) {	// O(1)
	
	Coord coord = getPosicionLibre();			// O(1)
	
	_tablero[coord.first][coord.second] = Ficha(ficha);	// O(1)
	
	if (!ficha.isVacia()){ 					// O(1)
		_posiciones_ocupadas++;				// O(1)
		_posiciones_vacias--;				// O(1)
	}	
	
	coord.second++;						// O(1)
	_posiciones_recorridas++;				// O(1)
	
	if(coord.second==_columnas){				// O(1)
		coord.second = 0;				// O(1)
		coord.first++;					// O(1)
	}		

	_proxima_posicion_libre = coord;			// O(1)


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
int Tablero::getPosicionesOcupadas() {				// O(1)
	return _posiciones_ocupadas;				// O(1)
}

Coord Tablero::getPosicionLibre() {				// O(1)
	return _proxima_posicion_libre;				// O(1)
}

int Tablero::getPosicionesRecorridas() {			// O(1)
	return _posiciones_recorridas;				// O(1)
}

int Tablero::getPosicionesPorRecorrer(){			// O(1)
	return (_filas*_columnas - _posiciones_recorridas);	// O(1)
}

/* La funcion getFicha debe, dada una coordenada, retornar la ficha que se encuentra en dicha posicion */
Ficha Tablero::getFicha(Coord coord) {

	assert(coord.first < _filas && coord.first >= 0
		&& coord.second < _columnas && coord.second >= 0);
	
	return _tablero[coord.first][coord.second];
}


/* La funcion completo debe retornar un booleano indicando si el tablero se encuentra o no completo */
bool Tablero::completo() {														// O(1)
	return (_posiciones_ocupadas == (_filas * _columnas));										// O(1)
}


/* La funcion print debe imprimir el contenido del tablero */
void Tablero::print() {
	for(int i=0; i<_filas; i++) {
		for(int j=0; j<_columnas; j++) {
			_tablero[i][j].print();
			cout << " ";
		}
		cout << endl;
	}
}

void Tablero::printDetailed() {
	for(int i=0; i<_filas; i++) {
		for(int j=0; j<_columnas; j++) {
			cout << " " << _tablero[i][j].getLado(SUPERIOR) << " |";
		}
		cout << endl;
		for(int j=0; j<_columnas; j++) {
			cout << _tablero[i][j].getLado(IZQUIERDA) << " ";
			cout << _tablero[i][j].getLado(DERECHA) << "|";
		}
		cout << endl;
		for(int j=0; j<_columnas; j++) {
			cout << " " << _tablero[i][j].getLado(INFERIOR) << " |";
		}
		cout << endl;
		for(int j=0; j<_columnas; j++) {
			cout << "";
		}
		cout << endl;
	}
	
	cout << endl;
}

void Tablero::llenarTableroConDiagonales(list<Ficha> & fichas) {
	
	Ficha fvacia = Ficha();
	
	for(list<Ficha>::iterator f = fichas.begin(); f != fichas.end(); f++){
		
		if(getPosicionesRecorridas() == getFilas()*getColumnas()){
			break;
		}
		
		if(_proxima_posicion_libre.first % 2 == 0){
		
			if(_proxima_posicion_libre.second % 2 == 0){
				agregarFicha(*f);
			}else{
				agregarFicha(fvacia);
			}
		
		}else{
			
			if(_proxima_posicion_libre.second % 2 == 1){
				agregarFicha(*f);
			}else{
				agregarFicha(fvacia);
			}
			
		}

	}
}
