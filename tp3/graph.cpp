#include <iostream>
#include <stdlib.h>
#include <list>
#include <vector>
#include <queue>
#include "graph.h"

using namespace std;

graph::graph() { 
	graph_container = new vector<list<int>* >();
	weights1 = new vector<vector<double> >();
	weights2 = new vector<vector<double> >();
	cant_nodos = 0;
}

graph::graph(int n) { 
	cant_nodos = n;
	graph_container = new vector<list<int>* >(n+1);
		
	for(int i=1; i <= n; i++){
		(*graph_container)[i] = new list<int>();
	}
	
	weights1 = new vector<vector<double> >(n+1, vector<double>(n+1, 0));
	weights2 = new vector<vector<double> >(n+1, vector<double>(n+1, 0));
}

graph::~graph() { 
	for(int i=1; i <= cant_nodos; i++){
		delete (*graph_container)[i];
	}
	delete graph_container;
	delete weights1;
	delete weights2;
}

void graph::add_edge(int u, int v, double w1, double w2){ 
	// Es un grafo no dirigido
	((*graph_container)[u])->push_back(v);
	((*graph_container)[v])->push_back(u);
	(*weights1)[u][v] = w1;
	(*weights1)[v][u] = w1;
	(*weights2)[u][v] = w2;
	(*weights2)[v][u] = w2;
}

list<int> * graph::get_adyacentes(int u){
	return (*graph_container)[u];
}

double graph::get_w1(int u, int v){
	return (*weights1)[u][v];
}

double graph::get_w2(int u, int v){
	return (*weights2)[u][v];
}


//matrizNext debe estar inicializado a 0. Esta matriz se usa para reconstruir el camino.
//matrizWeight es la matriz de pesos a la que se le calculará camino minimo.
vector<vector<double> > graph::floyd(vector<vector<double> > matrizWeight, vector<vector<double> > matrizNext){
//	vector<vector<double> > matrizAux = weights2;

	double infinito = (double) INFINITY;
	
	//Inicializo la matrizNext con los nodos siguientes
	for(int i = 0; i < cantNodos; i++){
		for(int j = 0; j< cantNodos; j++){
			if ((*matrizWeight)[i][j] != infinito && i != j){
				(*matrizNext)[i][j] = j;
			}
		}
	}
	
	
	for(int k = 0; k < cantNodos; k++){
		for(int i = 0; i < cantNodos; i++){
			for(int j = 0; j< cantNodos; j++){
				
				if ((*matrizWeight)[i][j] != infinito && i != j){
					if ((*matrizWeight)[i][j] > (*matrizWeight)[i][k] + (*matrizWeight)[k][j]){
						(*matrizWeight)[i][j] = (*matrizWeight)[i][k] + (*matrizWeight)[k][j];
						(*matrizNext)[i][j] = (*matrizNext)[i][k];
					}
				}
			}
		}
	}
}

vector<int> graph::reconstruirPath(int u, int v, vector<vector<double> > matrizNext){
	
	vector<int> path;
	
	if((*matrizNext)[u][v] == null)
		return path;
		
	path = new vector<double>;
	i = 0;
	
	while(u != v){
		u = (*matrizNext)[u][v];
		(*path)[i] = u;
		i++;
	}
	return path;
}

void graph::print(){ 
	
	for(int i=1; i <= cant_nodos; i++){

		cout << "Aristas del nodo " << i << ": ";
		for(list<int>::iterator f = ((*graph_container)[i])->begin(); f != ((*graph_container)[i])->end(); f++){
			cout << *f << " (w1: " << (*weights1)[i][*f] << " w2: " << (*weights2)[i][*f] << "), ";
		}
		
		cout << endl;
		
	}
}
