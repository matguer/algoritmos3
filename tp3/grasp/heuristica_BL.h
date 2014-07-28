#ifndef __HEURISTICA_BL_H__
#define __HEURISTICA_BL_H__

#include <iostream>
#include <stdlib.h>
#include <list>
#include <cmath>
#include <vector>
#include "../graph.h"
#include "../Algoritmos.h"

using namespace std;

class heuristicabl {
	private:
		bool pesoEnRegla(vector<int> camino, vector<vector<double> > pesos, double k);
		double getPeso(vector<int> camino, vector<vector<double> > pesos);
		vector<int> switchTramo(vector<int> camino1, vector<int> tramoNuevo, int nodoSource);
		void imprimirCamino(vector<int> camino);
		void imprimirSolucion(vector<int> camino, vector<vector<double> > pesos1, vector<vector<double> > pesos2);
		void borrarRepetidos(vector<int>& v);
		double k;
		unsigned int n;
		unsigned int u;
		unsigned int v;
		
		unsigned int v1;
		unsigned int v2;
		double w1;
		double w2;

	public:
		heuristicabl(double k, unsigned int u, unsigned int v);
		~heuristicabl();
		vector<int> execute(graph * grafo, vector<int>& solucion_inicial);
};
#endif
