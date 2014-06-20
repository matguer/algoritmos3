#ifndef __ALGORITMOS_H__
#define __ALGORITMOS_H__

#include <vector>
#include "graph.h"

class algoritmos
{
	public:
		algoritmos();
		~algoritmos();
		vector<vector<int> > floyd(graph* grafo, int w);
		vector<int> reconstruirPath(int u, int v, vector<vector<int> > matrizNext);

};

#endif
