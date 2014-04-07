#include "DiccionarioFichas.h"
#include <iostream>

using namespace std;

DiccionarioFichas::DiccionarioFichas() {
	_delegate = map<pair<Color,Color>, list<Ficha> >();
}

// Esta funcion clasifica las fichas por sus colores sup e izq
DiccionarioFichas::DiccionarioFichas(list<Ficha> fichas) {
	
	for(list<Ficha>::iterator f = fichas.begin(); f != fichas.end(); f++){
		
		pair<Color,Color> clave(f->getLado(SUPERIOR),f->getLado(IZQUIERDA));

		if(_delegate.count(clave)==0){
			_delegate[clave] = list<Ficha>();
		}		
		_delegate[clave].push_back(*f);
	}
}

DiccionarioFichas DiccionarioFichas::operator=(const DiccionarioFichas& otra) {
	
	DiccionarioFichas nueva = DiccionarioFichas();
	nueva._delegate = otra._delegate;
	
	return nueva; 
}

DiccionarioFichas::~DiccionarioFichas() {
}

void DiccionarioFichas::imprimirDiccionarioFichas(DiccionarioFichas dic){

	map<pair<Color,Color>, list<Ficha> >::iterator it_clave;
	for(it_clave = _delegate.begin(); it_clave != _delegate.end(); ++it_clave) {
		list<Ficha> valor = (*it_clave).second;
		imprimirListaFichas(valor);
		cout << endl;
	}
	
}

/* La funcion auxiliar imprimirLista debe imprimir el listado de fichas pasado por parametro */
void DiccionarioFichas::imprimirListaFichas(list<Ficha> valor) {
	list<Ficha>::iterator it_valor;
	for(it_valor = valor.begin(); it_valor != valor.end(); ++it_valor) {
		(*it_valor).print();
		cout << " - ";
	}
	cout << endl;
}
