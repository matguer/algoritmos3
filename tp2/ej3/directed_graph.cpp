#include <iostream>
#include <stdlib.h>
#include <list>
#include <map>
#include "directed_graph.h"

using namespace std;

directed_graph::directed_graph() { 
	graph_container = map<int, list<int>* >();
	cant_nodos = 0;
}

directed_graph::directed_graph(int n) { 
	graph_container = map<int, list<int>* >();
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
