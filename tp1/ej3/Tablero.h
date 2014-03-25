#ifndef __TABLERO_H__
#define __TABLERO_H__

#include "Ficha.h"
#include <vector>

class Tablero {
	
	private:
		vector<vector<Ficha>> _tablero;
		int _ancho;
		int _alto;
		int _fichas_puestas;

	public:
		Tablero(int alto, int ancho);
		~Tablero();
		void agregarFicha(int x, int y, Ficha ficha);
		void quitarFicha(int x, int y);
		void imprimir();
};

#endif
