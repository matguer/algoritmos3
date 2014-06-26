#include <iostream>
#include <stdlib.h>
#include <list>
#include <vector>
#include <cmath>
#include <queue>
#include <assert.h>
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
	graph_container = new vector<list<int>* >(n);
		
	for(int i=0; i<n; i++){
		(*graph_container)[i] = new list<int>();
	}
	
	// Se setean todos los pesos en infinito, es decir que a priori no hay ejes
	weights1 = new vector<vector<double> >(n, vector<double>(n, INFINITY));
	weights2 = new vector<vector<double> >(n, vector<double>(n, INFINITY));

	// Se setea la distancia de cada nodo a si mismo en 0
	for(int i=0; i<n; i++) {
		(*weights1)[i][i] = 0;
		(*weights2)[i][i] = 0;
	}
}

graph::~graph() { 
	for(int i=0; i < cant_nodos; i++){
		delete (*graph_container)[i];
	}
	delete graph_container;
	delete weights1;
	delete weights2;
}

void graph::add_edge(int u, int v, double w1, double w2){ 
	// Es un grafo no dirigido
	assert (u>=0);
	assert (v>=0);
	assert (u<cant_nodos);
	assert (v<cant_nodos);
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


void graph::print(){ 
	
	for(int i=0; i < cant_nodos; i++){

		cout << "Aristas del nodo " << i << ": ";
		for(list<int>::iterator f = ((*graph_container)[i])->begin(); f != ((*graph_container)[i])->end(); f++){
			cout << *f << " (w1: " << (*weights1)[i][*f] << " w2: " << (*weights2)[i][*f] << "), ";
		}
		
		cout << endl;
		
	}
}

vector<vector<double> > graph::get_weights1() { 
	return (*weights1); 
}

vector<vector<double> > graph::get_weights2() {
	return (*weights2); 
}


int graph::get_cant_nodos() {
	return cant_nodos;
}
