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
	_posiciones_recorridas = otro._posiciones_recorridas;
	_posiciones_ocupadas = otro._posiciones_ocupadas;
	_posiciones_vacias = otro._posiciones_vacias;
	_proxima_posicion_libre = otro._proxima_posicion_libre;
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

bool Tablero::reject(Tablero& mejor_tablero) {
		
	// PODA: Si en este tablero puedo poner menos fichas en el mejor de los casos que el mejor tablero, lo descarto
	if(_posiciones_ocupadas + getPosicionesPorRecorrer() <= mejor_tablero.getPosicionesOcupadas()){
		return true;
	}

	return false;
}

bool Tablero::accept(Tablero& mejor_tablero) {
	
	// Voy guardando el mejor tablero
	if(getPosicionesOcupadas() > mejor_tablero.getPosicionesOcupadas()){
		mejor_tablero = *this;
	}
	
	/* Si el tablero esta completo encontre una solucion inmejorable */
	if(completo()) {
		mejor_tablero = *this;
		return true;
	}
	
	return false;
}

pair<Color,Color> Tablero::restriccionFicha(Coord coord){
	
	pair<Color, Color> result(NO_COLOR,NO_COLOR);
	
	if(coord == Coord(0,0)){
		return result;
	}
	
	// Reviso la posicion a la izquierda
	if(coord.second > 0 && (_tablero[coord.first][coord.second-1]).getLado(DERECHA) != NO_COLOR){
		result.first = (_tablero[coord.first][coord.second-1]).getLado(DERECHA);
	}
	
	// Reviso la posicion de arriba
	if(coord.first > 0 && (_tablero[coord.first-1][coord.second]).getLado(INFERIOR) != NO_COLOR){
		result.second = (_tablero[coord.first-1][coord.second]).getLado(INFERIOR);
	}
	
	return result;
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
void Tablero::agregarFicha(Ficha ficha) {
	
	Coord coord = getPosicionLibre();
	
	_tablero[coord.first][coord.second] = Ficha(ficha);
	
	if (!ficha.isVacia()){ 
		_posiciones_ocupadas++;
		_posiciones_vacias--;
	}	
	
	coord.second++;
	_posiciones_recorridas++;
	
	if(coord.second==_columnas){
		coord.second = 0;
		coord.first++;
	}		

	_proxima_posicion_libre = coord;


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

int Tablero::getPosicionesRecorridas() {
	return _posiciones_recorridas;
}

int Tablero::getPosicionesPorRecorrer(){
	return (_filas*_columnas - _posiciones_recorridas);
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
