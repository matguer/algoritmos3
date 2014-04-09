#ifndef __TABLERO_H__
#define __TABLERO_H__

#include "Ficha.h"
#include "DiccionarioFichas.h"
#include <vector>

using namespace std;

typedef pair<int, int> Coord;
typedef vector<vector<Ficha> > Matriz;

class Tablero {
	
	private:
		Matriz _tablero;
		int _columnas;
		int _filas;
		int _posiciones_ocupadas;
		int _posiciones_vacias;
		int _posiciones_recorridas;
		Coord _proxima_posicion_libre;

	public:
		Tablero();
		Tablero(int alto, int ancho);
		Tablero(const Tablero& otro);
		~Tablero();
		
		int getFilas();
		int getColumnas();
		int getPosicionesOcupadas();
		Ficha getFicha(Coord coord);
		Coord getPosicionLibre();
		int getPosicionesRecorridas();
		int getPosicionesPorRecorrer();
		
		void agregarFicha(Ficha ficha);
		void quitarFicha(Coord coord);
		bool completo();
		void print();
		void printDetailed();
		void llenarTableroConDiagonales(list<Ficha> & fichas);
		Tablero& operator=(const Tablero& otra);
		
		//Funciones para backtracking
		bool reject(Tablero& mejor_tablero);
		bool accept(Tablero& mejor_tablero);
		pair<Color,Color> restriccionFicha(Coord coord);
};

#endif
