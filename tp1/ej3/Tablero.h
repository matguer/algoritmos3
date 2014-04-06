#ifndef __TABLERO_H__
#define __TABLERO_H__

#include "Ficha.h"
#include <vector>

using namespace std;

typedef pair<int, int> Coord;
typedef vector<Ficha*> Vec;
typedef vector<Vec> Matriz;

class Tablero {
	
	private:
		Matriz* _tablero;
		int _columnas;
		int _filas;
		int _posiciones_ocupadas;
		int _posiciones_vacias;

	public:
		Tablero(int alto, int ancho);
		~Tablero();
		int getFilas();
		int getColumnas();
		void agregarFicha(Coord coord, Ficha& ficha);
		void quitarFicha(Coord coord);
		int posicionesRecorridas(Coord coord);
		Coord siguientePosicion(Coord coord);
		int getCantidadFichas();
		Ficha getFicha(Coord coord);
		bool completo();
		void print();
};

#endif
