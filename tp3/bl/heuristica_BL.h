#ifndef __HEURISTICA_BL_H__
#define __HEURISTICA_BL_H__

#include <iostream>
#include <stdlib.h>
#include <list>
#include <cmath>
#include <vector>
#include "../graph.h"
#include "../algoritmos.h"

using namespace std;

bool pesoEnRegla(vector<int> camino, vector<vector<double> > pesos, double k);
double getPeso(vector<int> camino, vector<vector<double> > pesos);
vector<int> switchTramo(vector<int> camino1, vector<int> tramoNuevo, int nodoSource);
void imprimirCamino(vector<int> camino);
void imprimirSolucion(vector<int> camino, vector<vector<double> > pesos1, vector<vector<double> > pesos2);
void heuristicabl(graph* grafo, unsigned int u, unsigned int v, double k);
void borrarRepetidos(vector<int>& v);

#endif
