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

bool compararDistancia(const pair<Pueblo*, Pueblo*> & firstElem,const pair<Pueblo*, Pueblo*> & secondElem){
	double distanciaFirst = (*firstElem.first).distancia(*firstElem.second);
	double distanciaSecond = (*secondElem.first).distancia(*secondElem.second);
	return (distanciaFirst > distanciaSecond);

}

Region::Region(list<Pueblo*> * lista_pueblos, int centralitas){
	
	_centralitas = centralitas;
	_centrales_instaladas = 0;
	_tuberias_instaladas = 0;
	_pueblos = lista_pueblos;

	/*_pueblos_conectados_ady = new vector< vector<bool> >(_pueblos->size()+1, vector<bool>(_pueblos->size()+1, false) );
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
	}*/
	
}

void Region::print(){
	
	cout << "#Pueblos: " << _pueblos->size() << endl;
	cout << "Centralitas: " << _centralitas << endl;
	cout << "Distancias entre pueblos: " << endl;
	
	
	/*for(unsigned int j = 0; j < _pueblos_por_distancia->size(); j++){
		cout << *((*_pueblos_por_distancia)[j].first.first) << " y " << *((*_pueblos_por_distancia)[j].first.second) << ": " << (*_pueblos_por_distancia)[j].second << endl;
	}
	
	
	cout << endl;	
	cout << "[";
	
	for(list<Pueblo*>::iterator p = _pueblos->begin(); p != _pueblos->end(); p++){
		cout << **p;
	}
	
	cout << "]" << endl;*/
	
}

void Region::resolver(){

	int cantPueblos = _pueblos->size();

	// Arbol de pueblos
	list<pair<Pueblo*, Pueblo*> > * arbolPueblos = new list<pair<Pueblo*, Pueblo*> >();
	
	// Uso Prim para agregar pueblos al arbol

	// Elijo la primera ciudad de la lista como root
	Pueblo* puebloNuevo = *_pueblos->begin();
	pair<Pueblo*, Pueblo*> parPueblos = pair<Pueblo*, Pueblo*>(puebloNuevo, puebloNuevo);
	arbolPueblos->push_back(parPueblos);
	// Inicialmente solo el pueblo root tiene una central instalada
	puebloNuevo->instalarCentral();
	_centrales_instaladas = 1;

	// Pueblo mas cercano actual
	Pueblo * masCercano = puebloNuevo;

	// Agrego ciudades al arbol de a una - O(n)
	for(int i=0; i<cantPueblos-1 ; i++){
		
		// Actualizo las distancias al arbol y me quedo con la menor
		//cout << "nuevo_id: " << puebloNuevo->getId() << endl;
		masCercano = actualizarDistancias(puebloNuevo);

		// Agrego masCercano al arbol
		// En la proxima iteracion la distancia va a quedar en 0
		parPueblos = pair<Pueblo*, Pueblo*>(masCercano->getPuebloCercano(), masCercano);
		arbolPueblos->push_back(parPueblos);
		puebloNuevo = masCercano;

		//cout << "id: " << masCercano->getId() << " dist: " << masCercano->getDistanciaArbol() << endl;
	}


	/*for(list<pair<Pueblo*,Pueblo*> >::iterator p = arbolPueblos->begin(); p != arbolPueblos->end(); p++){
			cout << "pueblo " << ((*p).first)->getId() << " unido con pueblo " << ((*p).second)->getId() << ", distancia: " << (*((*p).first)).distancia(*((*p).second)) << endl;
	}

	cout << "luego del sort" << endl;*/

	// Ordeno los pares de ciudades segun distancia (de mayor a menor)
	arbolPueblos->sort(compararDistancia);

	/*for(list<pair<Pueblo*,Pueblo*> >::iterator p = arbolPueblos->begin(); p != arbolPueblos->end(); p++){
			cout << "pueblo " << ((*p).first)->getId() << " unido con pueblo " << ((*p).second)->getId() << ", distancia: " << (*((*p).first)).distancia(*((*p).second)) << endl;
	}*/

	// Mientras que pueda instalar centrales achico el tam maximo de las tuberias
	// Es decir, genero k componentes conexas, cada una con una central

	for(list<pair<Pueblo*,Pueblo*> >::iterator p = arbolPueblos->begin(); p != arbolPueblos->end(); p++){
		if(_centrales_instaladas<_centralitas){
			// p representa la tuberia mas larga, la elimino e instalo una nueva central
			((*p).second)->instalarCentral();
			_centrales_instaladas++;
			arbolPueblos->erase(p++);
		}	
	}

	// TODO: mover esto a una funcion

	// q = centrales instaladas, p = pueblos
	cout << _centrales_instaladas << " " << arbolPueblos->size() - 1 << endl;
	// pueblos con central
	for(list<Pueblo*>::iterator p = _pueblos->begin(); p != _pueblos->end(); p++){
		if((*p)->tieneCentral()){
			cout << (*p)->getId() << endl;
		}
	}

	for(list<pair<Pueblo*,Pueblo*> >::iterator p = arbolPueblos->begin(); p != arbolPueblos->end()--; p++){
			cout << ((*p).first)->getId() << " " << ((*p).second)->getId() << endl;
	}
	
	delete arbolPueblos;
	/*delete puebloNuevo;
	delete masCercano;*/
}

int Region::getCentralesInstaladas(){
	return _centrales_instaladas;
}

int Region::getTuberiasInstaladas(){
	return _tuberias_instaladas;
}

bool Region::hayTuberia(Pueblo & p1, Pueblo & p2){
	return false;
	return (*_pueblos_conectados_ady)[p1.getId()][p2.getId()];
}

void Region::printPueblosConectados(){
	
	// TODO: ver de pasarle arbolPueblos e imprimir eso
	/*for(unsigned int j = 1; j <= _pueblos->size(); j++){
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
	}*/
	
}

Pueblo* Region::actualizarDistancias(Pueblo* puebloNuevo){

	double distActual;
	double distNueva;
	double min = std::numeric_limits<double>::infinity();
	Pueblo* masCercano = puebloNuevo;

	// Antes de empezar actualizo la distancia del nuevo pueblo
	puebloNuevo->setDistanciaArbol(0.0);

	// Recorro todos los pueblos y actualizo sus distancias al arbol comparando con el ultimo p agregado
	for(list<Pueblo*>::iterator p = _pueblos->begin(); p != _pueblos->end(); p++){

		distActual = (**p).getDistanciaArbol();

		// Si no pertenece al arbol actualizo
		if(distActual > 0.0){

			cout << "id: " << (**p).getId() << "no esta en arbol" << endl;

			distNueva = (**p).distancia(*puebloNuevo);
			
			if(distNueva < distActual){
				(**p).setPuebloCercano(puebloNuevo);
				(**p).setDistanciaArbol(distNueva);
			}

			distActual = (**p).getDistanciaArbol();

			// Si es el menor hasta el momento guardo la ciudad
			if(distActual < min){
				masCercano = *p;
			}
		}
	
	}

	return masCercano;
}