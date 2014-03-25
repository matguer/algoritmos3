#ifndef __TABLERO_H__
#define __TABLERO_H__

#include "Ficha.h"
#include <vector>

using namespace std;

typedef pair<int, int> Coord;
typedef vector<Ficha> Vec;
typedef vector<Vec> Matriz;

class Tablero {
	
	private:
		Matriz _tablero;
		int _ancho;
		int _alto;
		int _fichas_puestas;

	public:
		Tablero(int alto, int ancho);
		~Tablero();
		void agregarFicha(Coord coord, Ficha ficha);
		void quitarFicha(Coord coord);
		void imprimir();
};

#endif
