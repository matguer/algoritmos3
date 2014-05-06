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

	/* Arreglo donde se guarda por cada nodo un flag que indica si ya lo visite */
	int visitados[cant_nodos];
	/* Arreglo donde se guarda el padre de cada nodo para reconstruir el camino */
	int padres[cant_nodos];
	// nodo target encontrado, ya que el destino pueden ser varios k+1 nodos
	int nodo_target_encontrado = -1;
	// Camino encontrado
	list<int> camino;

	/* Antes de comenzar con todo el procedimiendo preguntamos si source es algun target
	*  y de ser asi salgo enlistando el nodo en la solucion.
	*/
	if(source >= target_init && source <= target_end) {
		camino.push_back(source);
		return camino;
	}


	/* Se inicializan a todos como no visitados y sin padre */
	for(int i=0; i<cant_nodos; i++) {
		visitados[i] = 0;
		padres[i] = -1;
	}

	/* fix porque sino tira error de que padres no se usa */
	if(padres[source] == -1) padres[source] = -1;



	/* Comienza la recorrida para buscar algun target */
	cola.push(source);
	visitados[source] = 1;

	/* Se recorren todos los nodos a menos que encuentre algun target */
	while(!cola.empty() && nodo_target_encontrado == -1) {

		int nodo_padre = cola.front();
		cola.pop();

		list<int>* adyacentes = graph_container[nodo_padre];

		/* Por cada nodo adyacente al actual se corrobora que no haya sido visitado, se lo marca como tal,
		*  se le asigna un padre y se lo pushea a la cola para recorrer a sus hijos.
		*/
		for(list<int>::iterator it = adyacentes->begin(); it != adyacentes->end(); ++it) {

			int nodo_hijo = *it;

			/* Solo lo analizo si no fue visitado previamente */
			if(visitados[nodo_hijo] == 0) {
				
				/* Se marca al nodo como visitado para evitar recorrerlo de nuevo, se le asigna padre
				*  para reconstruir el camino al source y se lo pushea para recorrer a los hijos.
				*/
				visitados[nodo_hijo] = 1;
				padres[nodo_hijo] = nodo_padre;
				cola.push(nodo_hijo);

				/* Si encontre algun target dejo de iterar y guardo cual de ellos encontre */
				if(nodo_hijo >= target_init && nodo_hijo <= target_end) {
					nodo_target_encontrado = nodo_hijo;
					break;
				}

			}
		}
	}

	
	/* Comenzando del nodo_target_encontrado se arma el camino hasta el source siguiendo a los padres */
	int nodo = nodo_target_encontrado;
	
	camino.push_back(nodo);
	while(nodo != source) {
		nodo = padres[nodo];
		camino.push_back(nodo);
	}

	return camino;

}
