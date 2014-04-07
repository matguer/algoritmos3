#include "DiccionarioFichas.h"
#include <iostream>

using namespace std;

DiccionarioFichas::DiccionarioFichas() {
	_delegate = map<pair<Color,Color>, list<Ficha> >();
}

DiccionarioFichas::DiccionarioFichas(const DiccionarioFichas& otra) {
	_delegate = otra._delegate;
}

DiccionarioFichas::DiccionarioFichas(Ficha** fichas, int cant_fichas) {
	
	DiccionarioFichas::iterator it_dic;
	for(int i=0; i<cant_fichas; i++) {
		pair<Color,Color> clave(fichas[i]->getLado(SUPERIOR),fichas[i]->getLado(IZQUIERDA));
		list<Ficha> lista;
		it_dic = _delegate.find(clave);
		if(it_dic != _delegate.end()) lista = it_dic->second;
		lista.push_back(*fichas[i]);
		_delegate[clave] = lista; 
	}
	
	_delegate = d;
}

DiccionarioFichas DiccionarioFichas::operator=(const DiccionarioFichas& otra) {
	nueva._delegate = otra._delegate;
	
	return nueva; 
}

DiccionarioFichas::~DiccionarioFichas() {
}

void DiccionarioFichas::imprimirDiccionarioFichas(DiccionarioFichas dic){
	
	cout << endl << "DICCIONARIO" << endl;

	DiccionarioFichas::iterator it_clave;
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
