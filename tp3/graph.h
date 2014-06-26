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
		vector<vector<double> > * weights1;
		vector<vector<double> > * weights2;
		int cant_nodos;
	public:
		graph(int cant_nodos);
		graph();
		~graph();
		void add_edge(int u, int v, double w1, double w2);
		list<int> * get_adyacentes(int u);
		double get_w1(int u, int v);
		double get_w2(int u, int v);
		void print();
		vector<vector<double> > get_weights1();
		vector<vector<double> > get_weights2();
		int get_cant_nodos();

};

struct Camino{
	list<int> * camino;
	double w1_total;
	double w2_total;
};

#endif
