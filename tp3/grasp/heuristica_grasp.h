#ifndef __HEURISTICA_GRASP_H__
#define __HEURISTICA_GRASP_H__

#include <iostream>
#include <stdlib.h>
#include <vector>
#include "../graph.h"
#include "../Algoritmos.h"
#include "heuristica_greedy.h"
#include "heuristica_BL.h"

using namespace std;

class heuristicaGrasp {

	private:
		bool pesoEnRegla(vector<int> camino, vector<vector<double> > pesos);
		double getPeso(vector<int> camino, vector<vector<double> > pesos);
		void imprimirCamino(vector<int> camino);
		void imprimirSolucion(vector<int> camino, vector<vector<double> > pesos1, vector<vector<double> > pesos2);
		double k;
		unsigned int n;
		unsigned int u;
		unsigned int v;
		
		unsigned int v1;
		unsigned int v2;
		double w1;
		double w2;
	public:
		heuristicaGrasp(double k, unsigned int u, unsigned int v);
		~heuristicaGrasp();
		void execute(graph * grafo, int seed, int iteraciones);
};

#endif
