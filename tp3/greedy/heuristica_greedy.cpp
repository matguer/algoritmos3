#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <assert.h>
#include <math.h>
#include "../graph.h"
#include "../algoritmos.h"
#include "heuristica_greedy.h"

using namespace std;

heuristicaGreedy::heuristicaGreedy(){}
heuristicaGreedy::~heuristicaGreedy(){}

void heuristicaGreedy::execute() {
		

	// Leo la entrada

	cin >> n;
	cin >> m;
	cin >> u;
	cin >> v;
	/* en el input los nodos van de 1 a N y el grafo los trabaja de 0 a N-1 */
	u--;
	v--;
	cin >> k;
	
	graph * grafo = new graph(n);
	
	for(unsigned int i = 0; i<m; i++){
			cin >> v1;
			cin >> v2;
			cin >> w1;
			cin >> w2;
			grafo->add_edge(v1-1,v2-1,w1,w2);
	}
	
	vector<vector<double> > pesos1 = grafo->get_weights1();
	vector<vector<double> > pesos2 = grafo->get_weights2();
	algoritmos* algoritmo = new algoritmos();

	vector<vector<int> > floyd1 = algoritmo->floyd(pesos1);
	vector<vector<int> > floyd2 = algoritmo->floyd(pesos2);
	
	vector<int> camino_w1 = algoritmo->reconstruirPathFloyd(u, v, floyd1);
	vector<int> camino_w2;
	if(!pesoEnRegla(camino_w1, pesos1)) {
		cout << "no" << endl;
		return;
	}

	unsigned int nodoActual = u;
	bool finalRecorrido = false;
	vector<int> caminoFinal = vector<int>();
	while(nodoActual != v && !finalRecorrido) {
		caminoFinal.push_back(nodoActual);
		camino_w2 = algoritmo->reconstruirPathFloyd(nodoActual, v, floyd2);

		/* tomo el primer nodo nodo_1 del camino_w2 entre el nodoActual y v, 
			- caso 1: si es menor a k el peso en w1 entonce es el minimo posible por aca en w2 y cumple w1 
		 	- caso 2: sino me fijo si en el peor de los casos, siguiendo por nodo_1 y a partir de ahi hacer
		 		el camino_w1 cumple que el peso sea menor a k, si es asi avanzo un nodo y repito el procedimiento
		 	- caso 3: si ninguna de las dos condiciones anteriores se cumple entonces me veo obligado a avanzar al
		 		primer nodo del camino_w1 y repetir el procedimiento */

		/* primer nodo del camino_w2 */
		int nodo1_w2 = camino_w2[1];
		vector<int> camino_w2_potencial = algoritmo->reconstruirPathFloyd(nodo1_w2, v, floyd2);
		vector<int> camino_aux = unirCaminos(caminoFinal, camino_w2_potencial);
		camino_aux.push_back(v);

		if(pesoEnRegla(camino_aux, pesos1)) {
			/* caso 1 */
			caminoFinal = unirCaminos(caminoFinal, camino_w2_potencial);
			finalRecorrido = true;
		} else {
			/* caso 2 o 3 */
			vector<int> camino_w1_potencial = algoritmo->reconstruirPathFloyd(nodo1_w2, v, floyd1);
			vector<int> camino_aux = unirCaminos(caminoFinal, camino_w1_potencial);
			camino_aux.push_back(v);
			if(pesoEnRegla(camino_aux, pesos1)) {
				/* caso 2 */
				nodoActual = nodo1_w2;
			} else {
				camino_w1_potencial = algoritmo->reconstruirPathFloyd(nodoActual, v, floyd1);
				vector<int> camino_aux = unirCaminos(caminoFinal, camino_w1_potencial);
				camino_aux.push_back(v);
				if(pesoEnRegla(camino_aux, pesos1)) {
					/* primer nodo del camino_w1 */
					nodoActual = camino_w1_potencial[1]; 				
				} else {
					cout << "no" << endl;
					return;
				}
			}
			
		}
	}

	/* por ultimo agregamos v al camino final */
	caminoFinal.push_back(v);

	imprimirSolucion(caminoFinal, pesos1, pesos2);
	return;
	
}


bool heuristicaGreedy::pesoEnRegla(vector<int> camino, vector<vector<double> > pesos) {
	return k >= getPeso(camino, pesos);
}

double heuristicaGreedy::getPeso(vector<int> camino, vector<vector<double> > pesos) {
	double pesoTotal = 0.0;
	for(unsigned int i=0; i<camino.size()-1; i++) {
		pesoTotal += pesos[camino[i]][camino[i+1]];
	}
	return pesoTotal;
}

void heuristicaGreedy::imprimirCamino(vector<int> camino) {
	for(vector<int>::const_iterator it = camino.begin(); it != camino.end(); ++it)
		cout << (*it + 1) << " ";
}

void heuristicaGreedy::imprimirSolucion(vector<int> camino, vector<vector<double> > pesos1, vector<vector<double> > pesos2) {
	double pesoTotal1 = getPeso(camino, pesos1);
	double pesoTotal2 = getPeso(camino, pesos2);
	
	cout << pesoTotal1 << " " << pesoTotal2 << " " << camino.size() << " ";
	imprimirCamino(camino);
	cout << endl;
}

vector<int> heuristicaGreedy::unirCaminos(vector<int> camino1, vector<int> camino2) {
	int size1 = camino1.size();
	int size2 = camino2.size();
	vector<int> caminoNuevo = vector<int>(size1 + size2 - 1, 0);
	
	for(int i=0; i<size1; i++) {
		caminoNuevo[i] = camino1[i];
	}

	for(int i=0; i<size2 - 1; i++) {
		caminoNuevo[size1 + i] = camino2[i];
	}

	return caminoNuevo;
}
