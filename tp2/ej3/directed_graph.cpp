#include <iostream>
#include <stdlib.h>
#include <list>
#include <vector>
#include <queue>
#include "directed_graph.h"

using namespace std;

directed_graph::directed_graph() { 
	graph_container = vector<list<int>* >();
	cant_nodos = 0;
}

directed_graph::directed_graph(int n) { 
	graph_container = vector<list<int>* >(n);
	cant_nodos = n;
	
	for(int i=0; i < cant_nodos; i++){
		graph_container[i] = new list<int>();
	}
}

directed_graph::~directed_graph() { 
	for(int i=0; i < cant_nodos; i++){
		delete graph_container[i];
	}
}

void directed_graph::add_edge(int u, int v){ 
	(graph_container[u])->push_back(v);
}

void directed_graph::print(){ 
	
	for(int i=0; i < cant_nodos; i++){
		
		cout << "Aristas del nodo " << i << ": ";
		for(list<int>::iterator f = (graph_container[i])->begin(); f != (graph_container[i])->end(); f++){
			cout << *f << ", ";
		}
		
		cout << endl;
		
	}
}

/**
* El metodo debe implementar el algoritmo BFS e imprimir por pantalla el camino
* mas corto del nodo source al nodo target y el tamanio del mismo.
* @param: graph_container: vector con las listas de adyacencia para cada nodo
* @param: source: nodo del que se quiere arrancar a buscar
* @param: target: nodo destino de la busqueda
*/
list<int> directed_graph::bfs(int source, int target_init, int target_end) {

	queue<int> cola;
	int cant_nodos = graph_container.size();
	int visitados[cant_nodos];
	int padres[cant_nodos];

	// Se inicializan a todos como no visitados y sin padre
	for(int i=0; i<cant_nodos; i++) {
		visitados[i] = 0;
		padres[i] = -1;
	}

	cola.push(source);
	visitados[source] = 1;
	// fix temporal porque sino tira error de que padres no se usa
	if(padres[source] == -1) padres[source] = -1;

	while(!cola.empty()) {
		int nodo_padre = cola.front();
		cola.pop();

		list<int>* adyacentes = graph_container[nodo_padre];
		for(list<int>::iterator it = adyacentes->begin(); it != adyacentes->end(); ++it) {
			int nodo_hijo = *it;
			if(visitados[nodo_hijo] == 0) {
				visitados[nodo_hijo] = 1;
				padres[nodo_hijo] = nodo_padre;
				cola.push(nodo_hijo);
			}
		}
	}

	
	// Camino encontrado
	list<int> camino;

	// Se imprime el camino para llegar del source al target_init
	if(visitados[target_init] != 0) {

		int nodo = target_init;
		
		camino.push_back(nodo);
		while(nodo != source) {
			nodo = padres[nodo];
			camino.push_back(nodo);
		}
		
		
	}
	
	return camino;

}
