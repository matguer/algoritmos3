#include "Region.h"
#include "Pueblo.h"
#include <iostream>
#include <vector>

using namespace std;

Region::Region(){
	
	_centralitas = 0;
	_centrales_instaladas = 0;
	_tuberias_instaladas = 0;
	_pueblos = new list<Pueblo*>();
	_distancia_entre_pueblos = new list<pair<pair<Pueblo*,Pueblo*>, double> >();
	_pueblos_conectados_ady = new vector< vector<bool> >(0, vector<bool>(0, false) );
	_pueblos_agrupados = 0;
	
}

Region::~Region(){
	
	for(list<Pueblo*>::iterator p = _pueblos->begin(); p != _pueblos->end(); p++){
		delete *p;
	}
	
	delete _distancia_entre_pueblos;
	delete _pueblos_conectados_ady;
	
}

bool pairCompare(pair< pair<Pueblo*, Pueblo*>, double> & firstElem, pair< pair<Pueblo*, Pueblo*>, double> & secondElem) {
	return firstElem.second < secondElem.second;
}

Region::Region(list<Pueblo*> * lista_pueblos, int centralitas){
	
	_centralitas = centralitas;
	_centrales_instaladas = 0;
	_tuberias_instaladas = 0;
	_pueblos = lista_pueblos;
	_pueblos_conectados_ady = new vector< vector<bool> >(_pueblos->size(), vector<bool>(_pueblos->size(), false) );
	_pueblos_agrupados = _pueblos->size();
	_distancia_entre_pueblos = new list< pair<pair<Pueblo*,Pueblo*>, double> >();
	
	int i = 1;
	for(list<Pueblo*>::iterator p = _pueblos->begin(); p != _pueblos->end(); p++){
		
		int j = 1;
		for(list<Pueblo*>::iterator p2 = _pueblos->begin(); p2 != _pueblos->end(); p2++){
			
			// Para evitar guardar la distancia simetrica
			if(i > j){
				pair<Pueblo*, Pueblo*> pueblos = pair<Pueblo*, Pueblo*>(*p,*p2);
				pair< pair<Pueblo*, Pueblo*>, double> data = pair<pair<Pueblo*, Pueblo*>, double>(pueblos,(**(p)).distancia(**p2));
				_distancia_entre_pueblos->push_back(data);
			}
			
			j++;
			
		}
		i++;
	}
	
	// Dejo ordenada la lista de distancias
	_distancia_entre_pueblos->sort(pairCompare);
	
}

void Region::print(){
	
	cout << "#Pueblos: " << _pueblos->size() << endl;
	cout << "Centralitas: " << _centralitas << endl;
	cout << "Distancias entre pueblos: " << endl;
	
	for(list<pair< pair<Pueblo*, Pueblo*>, double> >::iterator i = _distancia_entre_pueblos->begin(); i != _distancia_entre_pueblos->end(); i++){
		cout << *(i->first.first) << " y " << *(i->first.second) << ": " << i->second << endl;
	}
	
	cout << endl;	
	cout << "[";
	
	for(list<Pueblo*>::iterator p = _pueblos->begin(); p != _pueblos->end(); p++){
		cout << **p;
	}
	
	cout << "]" << endl;
	
}

void Region::resolver(){
	/*
	if(_centralitas >= _pueblos->size()){
		
		_centrales_instaladas = _pueblos->size();
		
		for(list<Pueblo>::iterator p = _pueblos->begin(); p != _pueblos->end(); p++){
			p->instalarCentral();
		}
		
	}else{
		
		// Mientras no logre k componentes conexas para alimentar a todos los pueblos sigo conectando
		while(_centrales_instaladas < _pueblos_agrupados){
			
			// Conecto los pueblos mas cercanos disponibles
			pair< pair<Pueblo, Pueblo>, double> data = _distancia_entre_pueblos.front();
			Pueblo p1 = data.first.first;
			Pueblo p2 = data.first.second;
			
			_pueblos_conectados_ady[p1.getId()][p2.getId()] = true;
			_pueblos_agrupados--; // La cantidad de componentes conexas siempre disminuye ya que conecto pueblos sueltos a cada paso
			_tuberias_instaladas++;
			
			
		}
		
	}
	*/
	
}

