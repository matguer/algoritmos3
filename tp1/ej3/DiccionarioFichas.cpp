#include "DiccionarioFichas.h"
#include <iostream>

using namespace std;

DiccionarioFichas::DiccionarioFichas(int cant_colores) {	// O(1)
	_delegate = map<pair<Color,Color>, list<Ficha> >();	// O(1)
	_cant_colores = cant_colores;				// O(1)
}

DiccionarioFichas::DiccionarioFichas(const DiccionarioFichas& otro) {	// O(n*m)
	_delegate = otro._delegate;					// O(n*m) si el mapa contiene todas las fichas
	_cant_colores = otro._cant_colores;				// O(1)
}

// Esta funcion clasifica las fichas por sus colores sup e izq
DiccionarioFichas::DiccionarioFichas(list<Ficha> fichas, int cant_colores) {
	
	for(list<Ficha>::iterator f = fichas.begin(); f != fichas.end(); f++){
		
		pair<Color,Color> clave(f->getLado(IZQUIERDA), f->getLado(SUPERIOR));

		if(_delegate.count(clave)==0){
			_delegate[clave] = list<Ficha>();
		}		
		_delegate[clave].push_back(*f);
	}

	_cant_colores = cant_colores;
}

DiccionarioFichas DiccionarioFichas::operator=(const DiccionarioFichas& otra) {
	
	DiccionarioFichas nueva = DiccionarioFichas(otra._cant_colores);
	nueva._delegate = otra._delegate;
	
	return nueva; 
}

void DiccionarioFichas::sacarFicha(Ficha & ficha) {	// O(log (#colores * #colores)) + O(n*m)
	pair<Color, Color> key(ficha.getLado(IZQUIERDA), ficha.getLado(SUPERIOR));	// O(1)
	(_delegate[key]).remove(ficha);		// _delegate[key] -> O(log(_delegate.size())) = O(log (#colores * #colores)) 
						// list.remove -> O(list.size()) = O(n*m) si estaban todas las fichas
						// total instruccion = O(log (#colores * #colores)) + O(n*m)
}

list<Ficha> * DiccionarioFichas::dameFichas(pair<Color, Color> & restriccion){ // O(n*m) * O(#colores * #colores) + O(n*m) = O(n * m * #colores * #colores)

	// Las complejidades de los mapas fueron obtenidas de: http://www.cplusplus.com/reference/map/map/
	// Las complejidades de las list fueron obtenidas de: http://www.cplusplus.com/reference/list/list/
	
	list<Ficha> * fichas_posibles = new list<Ficha>();										// O(1)

	typedef std::map<pair<Color, Color>, list<Ficha> >::iterator it_type;								// O(1)
	
	// Indexo directo por la restriccion
	if(restriccion.first != NO_COLOR && restriccion.second != NO_COLOR){								// O(1)
		delete fichas_posibles;													// O(1)
		fichas_posibles = new list<Ficha>(_delegate[restriccion]);	
						// _delegate.size() <= #colores * #colores (caso que existen claves(pair) con todas las combinaciones de colores)
						// _delegate[restriccion] => O(log (_delegate.size())) => O(log (#colores * #colores))
						// new list => O(n*m) (caso en el que todas las fichas tienen igual lado izquierdo y superior)
						// total instruccion = O(log #colores * #colores) + O(n*m)
						
	// No hay restriccion, son todas
	}else if(restriccion.first == NO_COLOR && restriccion.second == NO_COLOR){							// O(1)
		
		for(it_type iterator = _delegate.begin(); iterator != _delegate.end(); iterator++) {		// O(delegate.size()) => O(#colores * #colores)
			fichas_posibles->insert(fichas_posibles->end(), iterator->second.begin(), iterator->second.end());	
										// O(n*m) en el peor caso copio todas las fichas a la lista
		}								// total del loop = O(n*m) * O(#colores * #colores)
		
	// Acumulo todas las fichas que cumplen la unica restriccion
	}else{
	
		if(restriccion.first == NO_COLOR && restriccion.second != NO_COLOR){							// O(1)
			
			for(it_type iterator = _delegate.begin(); iterator != _delegate.end(); iterator++) {	// O(delegate.size()) => O(#colores * #colores)
				// Si la clave del diccionario coincide con <___, COLOR> las agrego
				if(iterator->first.second == restriccion.second){							// O(1)
					fichas_posibles->insert(fichas_posibles->end(), iterator->second.begin(), iterator->second.end());
										// O(n*m) en el peor caso copio todas las fichas a la lista
				}						// total del loop = O(n*m) * O(#colores * #colores)
			}
			
		}
		
		if(restriccion.first != NO_COLOR && restriccion.second == NO_COLOR){							// O(1)
			
			typedef std::map<pair<Color, Color>, list<Ficha> >::iterator it_type;
			for(it_type iterator = _delegate.begin(); iterator != _delegate.end(); iterator++) { 	// O(delegate.size()) => O(#colores * #colores)
				// Si la clave del diccionario coincide con <COLOR, ___> las agrego
				if(iterator->first.first == restriccion.first){
					fichas_posibles->insert(fichas_posibles->end(), iterator->second.begin(), iterator->second.end());
										// O(n*m) en el peor caso copio todas las fichas a la lista
				}						// total del loop = O(n*m) * O(#colores * #colores)
			}
			
		}
	
	}
	
	eliminarRepeticiones(*fichas_posibles);												// O(n*m)
	return fichas_posibles;														// O(1)
	
}

void DiccionarioFichas::eliminarRepeticiones(list<Ficha>& fichas) {	// O(2*n*m) + O(#colores) + c  = O(n*m) 
	
	bool superior[_cant_colores];									// O(1)
	bool izquierda[_cant_colores];									// O(1)
	bool derecha[_cant_colores];									// O(1)
	bool inferior[_cant_colores];									// O(1)

	for(int i=0; i<_cant_colores; i++) {								// O(#colores)
		superior[i] = false;									// O(1)
		izquierda[i] = false;									// O(1)
		derecha[i] = false;									// O(1)
		inferior[i] = false;									// O(1)
	}

	list<Ficha> lista_sin_repeticiones = list<Ficha>();						// O(1)

	list<Ficha>::iterator it;
	for(it = fichas.begin(); it != fichas.end(); ++it) {						// O(n*m) si la lista son todas las fichas
		Ficha ficha = *it;									// O(1)
		bool existe = superior[ficha.getLado(SUPERIOR)] && izquierda[ficha.getLado(IZQUIERDA)]\
			&& derecha[ficha.getLado(DERECHA)] && inferior[ficha.getLado(INFERIOR)];	// O(1)

		if(!existe) {										// O(1)
			lista_sin_repeticiones.push_back(ficha);					// O(1)
		}

		superior[ficha.getLado(SUPERIOR)] = izquierda[ficha.getLado(IZQUIERDA)] = \
			derecha[ficha.getLado(DERECHA)] = inferior[ficha.getLado(INFERIOR)] = true;	// O(1)
		
	}

	fichas = lista_sin_repeticiones;								// O(n*m) si la lista son todas las fichas

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
