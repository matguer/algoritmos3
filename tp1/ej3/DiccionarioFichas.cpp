#include "DiccionarioFichas.h"
#include <iostream>

using namespace std;

DiccionarioFichas::DiccionarioFichas() {
	_delegate = map<pair<Color,Color>, list<Ficha> >();
}

DiccionarioFichas::DiccionarioFichas(const DiccionarioFichas& otro) {
	_delegate = otro._delegate;
}

// Esta funcion clasifica las fichas por sus colores sup e izq
DiccionarioFichas::DiccionarioFichas(list<Ficha> fichas) {
	
	for(list<Ficha>::iterator f = fichas.begin(); f != fichas.end(); f++){
		
		pair<Color,Color> clave(f->getLado(IZQUIERDA), f->getLado(SUPERIOR));

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

void DiccionarioFichas::sacarFicha(Ficha & ficha) {
	pair<Color, Color> key(ficha.getLado(IZQUIERDA), ficha.getLado(SUPERIOR));
	(_delegate[key]).remove(ficha);
}

list<Ficha> * DiccionarioFichas::dameFichas(pair<Color, Color> & restriccion){
	
	list<Ficha> * fichas_posibles = new list<Ficha>();
	
	typedef std::map<pair<Color, Color>, list<Ficha> >::iterator it_type;
	
	// Indexo directo por la restriccion
	if(restriccion.first != NO_COLOR && restriccion.second != NO_COLOR){
		delete fichas_posibles;
		fichas_posibles = new list<Ficha>(_delegate[restriccion]);
	// No hay restriccion, son todas
	}else if(restriccion.first == NO_COLOR && restriccion.second == NO_COLOR){
		
		for(it_type iterator = _delegate.begin(); iterator != _delegate.end(); iterator++) {
			fichas_posibles->insert(fichas_posibles->end(), iterator->second.begin(), iterator->second.end());
		}
		
	// Acumulo todas las fichas que cumplen la unica restriccion
	}else{
	
		if(restriccion.first == NO_COLOR && restriccion.second != NO_COLOR){
			
			for(it_type iterator = _delegate.begin(); iterator != _delegate.end(); iterator++) {
				// Si la clave del diccionario coincide con <___, COLOR> las agrego
				if(iterator->first.second == restriccion.second){
					fichas_posibles->insert(fichas_posibles->end(), iterator->second.begin(), iterator->second.end());
				}
			}
			
		}
		
		if(restriccion.first != NO_COLOR && restriccion.second == NO_COLOR){
			
			typedef std::map<pair<Color, Color>, list<Ficha> >::iterator it_type;
			for(it_type iterator = _delegate.begin(); iterator != _delegate.end(); iterator++) {
				// Si la clave del diccionario coincide con <___, COLOR> las agrego
				if(iterator->first.first == restriccion.first){
					fichas_posibles->insert(fichas_posibles->end(), iterator->second.begin(), iterator->second.end());
				}
			}
			
		}
	
	}
	
	return fichas_posibles;
	
}

DiccionarioFichas::~DiccionarioFichas() {
}

void DiccionarioFichas::imprimirDiccionarioFichas(){

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
