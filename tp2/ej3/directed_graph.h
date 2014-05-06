#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <iostream>
#include <stdlib.h>
#include <list>
#include <vector>
#include <queue>

using namespace std;

class directed_graph
{
	private:
		vector<list<int>*> graph_container;
		int cant_nodos;
	public:
		directed_graph(int cant_nodos);
		directed_graph();
		~directed_graph();
		void add_edge(int u, int v);
		void print();
		list<int> bfs(int source, int target_init, int target_end);

};

#endif
