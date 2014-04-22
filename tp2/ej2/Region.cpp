#include "Region.h"
#include "Pueblo.h"
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

Region::Region(){
	
	_centralitas = 0;
	_centrales_instaladas = 0;
	_tuberias_instaladas = 0;
	_pueblos = new list<Pueblo*>();
	_pueblos_por_distancia = new vector< pair<pair<Pueblo*,Pueblo*>, double> >(_pueblos->size());
	_pueblos_conectados_ady = new vector< vector<bool> >(0, vector<bool>(0, false) );
	_cant_grupos_pueblos = 0;
	
}

Region::~Region(){
	
	for(list<Pueblo*>::iterator p = _pueblos->begin(); p != _pueblos->end(); p++){
		delete *p;
	}
	
	delete _pueblos_por_distancia;
	delete _pueblos_conectados_ady;
	
}

bool pairCompare(pair< pair<Pueblo*, Pueblo*>, double> & firstElem, pair< pair<Pueblo*, Pueblo*>, double> & secondElem) {
	return firstElem.second > secondElem.second;
}

Region::Region(list<Pueblo*> * lista_pueblos, int centralitas){
	
	_centralitas = centralitas;
	_centrales_instaladas = 0;
	_tuberias_instaladas = 0;
	_pueblos = lista_pueblos;
	_pueblos_conectados_ady = new vector< vector<bool> >(_pueblos->size()+1, vector<bool>(_pueblos->size()+1, false) );
	_cant_grupos_pueblos = _pueblos->size();
	_pueblos_por_distancia = new vector< pair<pair<Pueblo*,Pueblo*>, double> >();
	
	int i = 1;
	for(list<Pueblo*>::iterator p = _pueblos->begin(); p != _pueblos->end(); p++){
		
		int j = 1;
		for(list<Pueblo*>::iterator p2 = _pueblos->begin(); p2 != _pueblos->end(); p2++){
			
			// Para evitar guardar la distancia simetrica
			if(i > j){
				pair<Pueblo*, Pueblo*> pueblos = pair<Pueblo*, Pueblo*>(*p,*p2);
				pair< pair<Pueblo*, Pueblo*>, double> data = pair<pair<Pueblo*, Pueblo*>, double>(pueblos,(**(p)).distancia(**p2));
				_pueblos_por_distancia->push_back(data);
			}
			
			j++;
			
		}
		i++;
	}
	
	// Armo el heap con prioridad de distancia
	make_heap(_pueblos_por_distancia->begin(),_pueblos_por_distancia->end(), pairCompare);
	
}

void Region::print(){
	
	cout << "#Pueblos: " << _pueblos->size() << endl;
	cout << "Centralitas: " << _centralitas << endl;
	cout << "Distancias entre pueblos: " << endl;
	
	
	for(unsigned int j = 0; j < _pueblos_por_distancia->size(); j++){
		cout << *((*_pueblos_por_distancia)[j].first.first) << " y " << *((*_pueblos_por_distancia)[j].first.second) << ": " << (*_pueblos_por_distancia)[j].second << endl;
	}
	
	
	cout << endl;	
	cout << "[";
	
	for(list<Pueblo*>::iterator p = _pueblos->begin(); p != _pueblos->end(); p++){
		cout << **p;
	}
	
	cout << "]" << endl;
	
}

void Region::resolver(){
	
	// Mientras no logre k componentes conexas para alimentar a todos los pueblos sigo conectando
	while(_centralitas < _cant_grupos_pueblos){

		// Conecto los pueblos mas cercanos disponibles
		pair< pair<Pueblo*, Pueblo*>, double> data = _pueblos_por_distancia->front();
		pop_heap(_pueblos_por_distancia->begin(), _pueblos_por_distancia->end(), pairCompare);
		_pueblos_por_distancia->pop_back();

		Pueblo * p1 = data.first.first;
		Pueblo * p2 = data.first.second;

		// Si estan en componentenes conexas distintas las uno
		if(p1->getIdGrupoPueblo() != p2->getIdGrupoPueblo()){

			(*_pueblos_conectados_ady)[p1->getId()][p2->getId()] = true;
			(*_pueblos_conectados_ady)[p2->getId()][p1->getId()] = true;
			
			// Junto las clases de equivalencia
			int id_grupo_viejo = p2->getIdGrupoPueblo();
			
			for(list<Pueblo*>::iterator p = _pueblos->begin(); p != _pueblos->end(); p++){
				if((**p).getIdGrupoPueblo() == id_grupo_viejo){
					(**p).setIdGrupoPueblo(p1->getIdGrupoPueblo());
				}
			}
			
			_cant_grupos_pueblos--; // La cantidad de componentes conexas siempre disminuye ya que conecto pueblos sueltos a cada paso
			_tuberias_instaladas++;
		
		}

		
		
	}

	// Dicc para saber en que componentes conexas ya instale una central
	map<int, bool> * grupos_instalados = new map<int, bool>();
	
	for(list<Pueblo*>::iterator p = _pueblos->begin(); p != _pueblos->end(); p++){
		
		if(grupos_instalados->find((*p)->getIdGrupoPueblo()) == grupos_instalados->end()){
			(*p)->instalarCentral();
			(*grupos_instalados)[(*p)->getIdGrupoPueblo()] = true;
			_centrales_instaladas++;
		}
		
	}
	
	delete grupos_instalados;
		
	
}

int Region::getCentralesInstaladas(){
	return _centrales_instaladas;
}

int Region::getTuberiasInstaladas(){
	return _tuberias_instaladas;
}

bool Region::hayTuberia(Pueblo & p1, Pueblo & p2){
	return (*_pueblos_conectados_ady)[p1.getId()][p2.getId()];
}

void Region::printPueblosConectados(){
	
	for(unsigned int j = 1; j <= _pueblos->size(); j++){
		cout << j << " ";
	}

	cout << endl;
	
	for(unsigned int j = 1; j <= _pueblos->size(); j++){
		cout << "--";
	}
	
	cout << endl;
	
	for(unsigned int i = 1; i <= _pueblos->size(); i++){

		for(unsigned int j = 1; j <= _pueblos->size(); j++){
			cout << (*_pueblos_conectados_ady)[i][j] << " ";
		}
		cout << "|" << i << endl;
	}
	
}

