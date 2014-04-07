#ifndef __DICCIONARIO_H__
#define __DICCIONARIO_H__

#include <map>
#include <list>
#include <iostream>
#include "Ficha.h"

using namespace std;

class DiccionarioFichas {

	private:
		map<pair<Color,Color>, list<Ficha> > _delegate;

	public:
		DiccionarioFichas();
		~DiccionarioFichas();
		DiccionarioFichas(list<Ficha> fichas);
		DiccionarioFichas operator=(const DiccionarioFichas& otra);
		void imprimirDiccionarioFichas(DiccionarioFichas dic);
		void imprimirListaFichas(list<Ficha> valor);

};

#endif
