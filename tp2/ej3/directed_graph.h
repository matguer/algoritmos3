#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <iostream>
#include <stdlib.h>
#include <list>
#include <map>

using namespace std;

class directed_graph
{
	private:
		map<int, list<int>* > graph_container;
		int cant_nodos;
	public:
		directed_graph(int cant_nodos);
		directed_graph();
		~directed_graph();
		void add_edge(int u, int v);
		void print();

};

#endif
