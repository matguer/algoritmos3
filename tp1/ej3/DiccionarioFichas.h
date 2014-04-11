#ifndef __DICCIONARIO_H__
#define __DICCIONARIO_H__

#include <map>
#include <list>
#include <iostream>
#include "Ficha.h"
#include <stdlib.h>

using namespace std;

class DiccionarioFichas {

	private:
		map<pair<Color,Color>, list<Ficha> > _delegate;
		int _cant_colores;
		void eliminarRepeticiones(list<Ficha>& fichas);

	public:
		DiccionarioFichas(int cant_colores);
		~DiccionarioFichas();
		DiccionarioFichas(list<Ficha> fichas, int cant_colores);
		DiccionarioFichas(const DiccionarioFichas& otro);
		DiccionarioFichas operator=(const DiccionarioFichas& otra);
		void imprimirDiccionarioFichas();
		void imprimirListaFichas(list<Ficha> valor);
		list<Ficha> * dameFichas(pair<Color, Color> & restriccion);
		void sacarFicha(Ficha & ficha);
};

#endif
