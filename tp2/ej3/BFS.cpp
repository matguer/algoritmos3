#include <iostream>
#include <list>
#include <vector>
#include <queue>

#include "BFS.h"

using namespace std;

BFS::BFS() {}

BFS::~BFS() {}

void BFS::test() {

	vector< list<int> > adj(7, list<int>());

	list<int> l = list<int>();
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	adj[0] = l;

	l = list<int>();
	l.push_back(0);
	adj[1] = l;

	l = list<int>();
	l.push_back(0);
	l.push_back(3);
	l.push_back(4);
	adj[2] = l;

	l = list<int>();
	l.push_back(0);
	l.push_back(2);
	l.push_back(5);
	l.push_back(6);
	adj[3] = l;

	l = list<int>();
	l.push_back(2);
	adj[4] = l;

	l = list<int>();
	l.push_back(3);
	adj[5] = l;

	l = list<int>();
	l.push_back(3);
	adj[6] = l;


	cout << "VECTOR DE LISTAS DE ADYACENCIA" << endl;
	cout << "size: " << adj.size() << endl;
	for(unsigned int i=0; i<adj.size(); i++)	{
		list<int> lista = adj[i];
		cout << "nodo: " << i << endl;
		for(list<int>::iterator it = lista.begin(); it != lista.end(); ++it) {
			cout << *it << " - ";
		}
		cout << endl;
	}

	execute(adj, 3, 4);
}


/**
* El metodo execute debe implementar el algoritmo BFS e imprimir por pantalla el camino
* mas corto del nodo source al nodo target y el tamanio del mismo.
* @param: adj_list: vector con las listas de adyacencia para cada nodo
* @param: source: nodo del que se quiere arrancar a buscar
* @param: target: nodo destino de la busqueda
*/
void BFS::execute(vector< list<int> > adj_list, int source, int target) {

	queue<int> cola;
	int cant_nodos = adj_list.size();
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

		list<int> adyacentes = adj_list[nodo_padre];
		for(list<int>::iterator it = adyacentes.begin(); it != adyacentes.end(); ++it) {
			int nodo_hijo = *it;
			if(visitados[nodo_hijo] == 0) {
				visitados[nodo_hijo] = 1;
				padres[nodo_hijo] = nodo_padre;
				cola.push(nodo_hijo);
			}
		}
	}

	
	cout << endl << endl;

	// Se imprime el camino para llegar del source al target
	if(visitados[target] == 0) {
		cout << "No se puede generar un camino del source al target" << endl;
	} else {
		cout << "CAMINO MAS CORTO (CANT. ARISTAS) DEL NODO SOURCE: " << source << "  AL NODO TARGET: " << target << endl;
		int nodo = target;
		list<int> camino;
		camino.push_back(nodo);
		while(nodo != source) {
			nodo = padres[nodo];
			camino.push_back(nodo);
		}
	
		cout << "size: " << (camino.size() - 1) << endl;
		for(list<int>::iterator it = camino.begin(); it != camino.end(); ++it) {
			cout << *it << " - ";
		}
	}
	cout << endl << endl;

}
