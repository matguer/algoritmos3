#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <assert.h>
#include <cmath>
#include "../graph.h"
#include "../Algoritmos.h"
#include "heuristica_grasp.h"

using namespace std;

heuristicaGrasp::heuristicaGrasp(double k, unsigned int u, unsigned int v){
	this->k = k;
	this->u = u;
	this->v = v;
}
heuristicaGrasp::~heuristicaGrasp(){}

void heuristicaGrasp::execute(graph * grafo, int seed, int iteraciones) {
	
	vector<vector<double> > pesos1_orig = grafo->get_weights1();
	vector<vector<double> > pesos2_orig = grafo->get_weights2();
	
	heuristicabl* heu_bl = new heuristicabl(k, u, v);
	heuristicaGreedy* heu_greedy = new heuristicaGreedy(k, u, v);
	
	vector<int> solucion_inicial;
	vector<int> solucion_parcial;
	vector<int> solucion_final;
	int peso_solucion_final = (int)INFINITY;
	
	/* comienzan las iteraciones en busca de la mejor solucion */
	for(int i=0; i<iteraciones; i++) {
		
		solucion_inicial = heu_greedy->execute(grafo, seed);	
		
		if(solucion_inicial.size() > 0) {
			solucion_parcial = heu_bl->execute(grafo, solucion_inicial);
			int peso_solucion_parcial = getPeso(solucion_parcial, pesos1_orig);
			if(peso_solucion_parcial < peso_solucion_final) {
				solucion_final = solucion_parcial;
				peso_solucion_final = peso_solucion_parcial;
			}
		}
		
		
	}
	
	if(solucion_final.size() > 0) {
		imprimirSolucion(solucion_final, pesos1_orig, pesos2_orig);
	} else {
		cout << "no" << endl;
	}
	
	delete heu_bl;
	delete heu_greedy;
	
	return;
	
}


/***
 * La funcion pesoEnRegla obtiene el peso del camino y lo compara con la cota K.
 * La complejidad es O(n) siendo n la longitud del camino.
 */
bool heuristicaGrasp::pesoEnRegla(vector<int> camino, vector<vector<double> > pesos) {
	return k >= getPeso(camino, pesos);	// O(n)
}


/***
 * La funcion getPeso recorre todos los nodos del camino pasado por parametro sumando los pesos
 * de los mismos en un acumulador. Su complejidad es O(n) siendo n la longitud del camino.
 */
double heuristicaGrasp::getPeso(vector<int> camino, vector<vector<double> > pesos) {
	double pesoTotal = 0.0;
	for(unsigned int i=0; i<camino.size()-1; i++) {	// O(n), caso en el cual tenemos un camino hamiltoniano que pasa por todos los nodos.
		pesoTotal += pesos[camino[i]][camino[i+1]];	// acceso a la matriz en O(1)
	}
	return pesoTotal;
}

void heuristicaGrasp::imprimirCamino(vector<int> camino) {
	for(vector<int>::const_iterator it = camino.begin(); it != camino.end(); ++it)
		cout << (*it + 1) << " ";
}

void heuristicaGrasp::imprimirSolucion(vector<int> camino, vector<vector<double> > pesos1, vector<vector<double> > pesos2) {
	double pesoTotal1 = getPeso(camino, pesos1);
	double pesoTotal2 = getPeso(camino, pesos2);
	
	cout << pesoTotal1 << " " << pesoTotal2 << " " << camino.size() << " ";
	imprimirCamino(camino);
	cout << endl;
}