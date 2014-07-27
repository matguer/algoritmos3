#ifndef __ALGORITMOS_H__
#define __ALGORITMOS_H__

#include <vector>
#include "graph.h"

class Algoritmos
{
	public:
		Algoritmos();
		~Algoritmos();
		vector<vector<int> > floyd(vector<vector<double> >& matrizWeight);
		vector<int> reconstruirPathFloyd(int u, int v, vector<vector<int> > matrizNext);
		vector<int> dijkstra(graph* grafo, vector<vector<double> >& pesos, int source, int target);
};

#endif
