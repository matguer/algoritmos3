#include "Algoritmos.h"
#include <assert.h>

Algoritmos::Algoritmos(){}

Algoritmos::~Algoritmos(){}

vector<vector<int> > Algoritmos::floyd(vector<vector<double> >& matrizWeight) {

	int cant_nodos = matrizWeight.size();

	vector<vector<int> > matrizNext = vector<vector<int> >(cant_nodos,vector<int>(cant_nodos,-1));
	
	//Inicializo la matrizNext con los nodos siguientes
	for(int i = 0; i < cant_nodos; i++){
		for(int j = 0; j< cant_nodos; j++){
			if (i != j) (matrizNext)[i][j] = j;
		}
	}
	
	
	for(int k = 0; k < cant_nodos; k++){
		for(int i = 0; i < cant_nodos; i++){
			for(int j = 0; j< cant_nodos; j++){
				if (i != j){
					if ((matrizWeight)[i][j] > (matrizWeight)[i][k] + (matrizWeight)[k][j]){
						(matrizWeight)[i][j] = (matrizWeight)[i][k] + (matrizWeight)[k][j];
						(matrizNext)[i][j] = (matrizNext)[i][k];
					}
				}
			}
		}
	}

	return matrizNext;
}


vector<int> Algoritmos::reconstruirPathFloyd(int u, int v, vector<vector<int> > matrizNext){
	
	vector<int> path = vector<int>();
	
	while(u != v){
		path.push_back(u);
		u = (matrizNext)[u][v];
	}
	path.push_back(v);
	return path;
}


int minimo(const list<int>* nodos) {
	assert(nodos->size() > 0);
	int min = nodos->back();
	for(list<int>::const_iterator it_nodos = nodos->begin(); it_nodos != nodos->end(); ++it_nodos)
		if(*it_nodos < min) min = *it_nodos;
	return min;
}

vector<int> Algoritmos::dijkstra(graph* grafo, vector<vector<double> >& pesos, int source, int target) {

	int cant_nodos = grafo->get_cant_nodos();
	vector<int>* predecesores = new vector<int>(cant_nodos,source);
	list<int>* adyacentes = new list<int>();
	vector<bool>* recorridos = new vector<bool>(cant_nodos, false);
	list<int>* no_recorridos = new list<int>();
	
	no_recorridos->push_back(source);
	while(no_recorridos->size() > 0) {
		int nodo = minimo(no_recorridos);
		(*recorridos)[nodo] = true;
		no_recorridos->remove(nodo);
		
		adyacentes = grafo->get_adyacentes(nodo);
		for(list<int>::iterator it_ady = adyacentes->begin(); it_ady != adyacentes->end(); ++it_ady) {
			int adyacente = *it_ady;
			double dist_ady = pesos[adyacente][source];
			double dist_nodo = pesos[nodo][source];
			double dist_ady_nodo = pesos[adyacente][nodo];
			
			if(dist_ady > dist_nodo + dist_ady_nodo) {
				pesos[adyacente][source] = dist_nodo + dist_ady_nodo;
				pesos[source][adyacente] = dist_nodo + dist_ady_nodo;
				(*predecesores)[adyacente] = nodo;
				
			}
			if((*recorridos)[adyacente] == false)
				no_recorridos->push_back(adyacente);
		}
	}
	
	
	/* reconstruccion del camino */
	list<int> path_reverse = list<int>();
	
	while(target != source){
		path_reverse.push_back(target);
		target = (*predecesores)[target];
	}
	
	path_reverse.push_back(source);
	vector<int> path = vector<int>(path_reverse.size(),0);
	
	/* como el camino se fue reconstruyendo de atras para adelante lo doy vuelta */
	for(unsigned int i=0; i<path.size(); i++) {
		path[i] = path_reverse.back();
		path_reverse.pop_back();
	}
	
	return path;
	
}





