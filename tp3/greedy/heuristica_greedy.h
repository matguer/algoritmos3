#ifndef __HEURISTICA_GREEDY_H__
#define __HEURISTICA_GREEDY_H__

#include <iostream>
#include <stdlib.h>
#include <vector>
#include "../graph.h"
#include "../Algoritmos.h"

using namespace std;

class heuristicaGreedy {

	private:
		bool pesoEnRegla(vector<int> camino, vector<vector<double> > pesos);
		double getPeso(vector<int> camino, vector<vector<double> > pesos);
		void imprimirCamino(vector<int> camino);
		void imprimirSolucion(vector<int> camino, vector<vector<double> > pesos1, vector<vector<double> > pesos2);
		vector<int> unirCaminos(vector<int> camino1, vector<int> camino2);
		double k;
		unsigned int n;
		unsigned int u;
		unsigned int v;
		
		unsigned int v1;
		unsigned int v2;
		double w1;
		double w2;
	public:
		heuristicaGreedy(double k, unsigned int u, unsigned int v);
		~heuristicaGreedy();
		void execute(graph * grafo);
};

#endif
