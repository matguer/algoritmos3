#ifndef __DICCIONARIO_H__
#define __DICCIONARIO_H__

#include <map>
#include <list>
#include <iostream>
#include "Ficha.h"

using namespace std;

class Diccionario {

	private:
		map<pair<Color,Color>, list<Ficha> > _delegate;

	public:
		Diccionario();
		~Diccionario();

};

#endif
