#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <iostream>
#include <stdlib.h>
#include <list>
#include <vector>
#include <queue>

using namespace std;

class graph
{
	private:
		vector<list<int>*> * graph_container;
		vector<vector<int> > * weights1;
		vector<vector<int> > * weights2;
		int cant_nodos;
	public:
		graph(int cant_nodos);
		graph();
		~graph();
		void add_edge(int u, int v, int w1, int w2);
		void print();

};

#endif
