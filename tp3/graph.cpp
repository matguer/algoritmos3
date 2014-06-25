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


void backtrack(graph * grafo, int nodo_objetivo, double k, vector<bool> * nodos_visitados, Camino & camino_actual, Camino & mejor_camino) {
	
	int ultimo_nodo = (*camino_actual.camino).back(); // Ultimo nodo agregado
	list<int> * nodos_adyacentes = grafo->get_adyacentes(ultimo_nodo); // Nodos adyacentes al ultimo nodo recorrido
	
	// Si me pase de la cota K corto esta rama
	if(camino_actual.w1_total > k){
		//cout << "me pase de la cota " << camino_actual.w1_total << " vs " << k << endl;
		return;
	}
	
	// Si ya encontre el nodo final termino
	if(ultimo_nodo == nodo_objetivo){
		/*
		for(list<int>::iterator f = (*camino_actual.camino).begin(); f != (*camino_actual.camino).end(); f++){
			cout << *f << " " << endl;
		}
		cout << endl;
		cout << "w1 total " << camino_actual.w1_total << endl;
		cout << "w2 total " << camino_actual.w2_total << endl << endl;
		*/
		if(camino_actual.w2_total < mejor_camino.w2_total){
			delete mejor_camino.camino;
			mejor_camino.camino = new list<int>((*camino_actual.camino));
			mejor_camino.w1_total = camino_actual.w1_total;
			mejor_camino.w2_total = camino_actual.w2_total;
		}
		return;
	}
	
	// Recorro los adyancentes del ultimo nodo recorrido
	for(list<int>::iterator nodo = nodos_adyacentes->begin(); nodo != nodos_adyacentes->end(); nodo++){
		// Si ya visite el nodo termino
		if((*nodos_visitados)[*nodo] == true){
			continue;
		}

		(*nodos_visitados)[*nodo] = true; // Marco el nodo como visitado para hacer el llamado recursivo
		(*camino_actual.camino).push_back(*nodo);
		camino_actual.w1_total = camino_actual.w1_total + grafo->get_w1(ultimo_nodo, *nodo);
		camino_actual.w2_total = camino_actual.w2_total + grafo->get_w2(ultimo_nodo, *nodo);

		backtrack(grafo, nodo_objetivo, k, nodos_visitados, camino_actual, mejor_camino);
		// Restauro el estado para cuando vuelva
		camino_actual.w1_total = camino_actual.w1_total - grafo->get_w1(ultimo_nodo, *nodo);
		camino_actual.w2_total = camino_actual.w2_total - grafo->get_w2(ultimo_nodo, *nodo);
		(*nodos_visitados)[*nodo] = false;
		(*camino_actual.camino).pop_back();
				
		
	}
	
	
}
