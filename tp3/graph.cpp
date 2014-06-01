#include <iostream>
#include <stdlib.h>
#include <list>
#include <vector>
#include <queue>
#include "graph.h"

using namespace std;

graph::graph() { 
	graph_container = new vector<list<int>* >();
	weights1 = new vector<vector<int> >();
	weights2 = new vector<vector<int> >();
	cant_nodos = 0;
}

graph::graph(int n) { 
	graph_container = new vector<list<int>* >(n);
	cant_nodos = n;
	
	for(int i=0; i < cant_nodos; i++){
		(*graph_container)[i] = new list<int>();
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

void graph::add_edge(int u, int v, int w1, int w2){ 
	// Es un grafo no dirigido
	((*graph_container)[u])->push_back(v);
	((*graph_container)[v])->push_back(u);
	(*weights1)[u][v] = w1;
	(*weights1)[v][u] = w1;
	(*weights2)[u][v] = w2;
	(*weights2)[v][u] = w2;
}

void graph::print(){ 
	
	for(int i=0; i < cant_nodos; i++){
		
		cout << "Aristas del nodo " << i << ": ";
		for(list<int>::iterator f = ((*graph_container)[i])->begin(); f != ((*graph_container)[i])->end(); f++){
			cout << *f << ", ";
		}
		
		cout << endl;
		
	}
}
