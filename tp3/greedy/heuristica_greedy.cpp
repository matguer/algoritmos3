#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <assert.h>
#include <math.h>
#include "../graph.h"
#include "../Algoritmos.h"
#include "heuristica_greedy.h"

using namespace std;

heuristicaGreedy::heuristicaGreedy(double k, unsigned int u, unsigned int v){
	this->k = k;
	this->u = u;
	this->v = v;
}
heuristicaGreedy::~heuristicaGreedy(){}

void heuristicaGreedy::execute(graph * grafo) {

	vector<vector<double> > pesos1_orig = grafo->get_weights1();
	vector<vector<double> > pesos2_orig = grafo->get_weights2();

	vector<vector<double> > pesos1 = grafo->get_weights1();
	vector<vector<double> > pesos2 = grafo->get_weights2();
	Algoritmos* algoritmo = new Algoritmos();

	vector<vector<int> > floyd1 = algoritmo->floyd(pesos1);
	vector<vector<int> > floyd2 = algoritmo->floyd(pesos2);
	

	/* Si el camino minimo en w1 es mayor a la cota K entonces no hay solucion */
	vector<int> camino_w1 = algoritmo->reconstruirPathFloyd(u, v, floyd1);
	if(!pesoEnRegla(camino_w1, pesos1_orig)) {
		cout << "no" << endl;
		return;
	}

	/* Si el camino minimo en w2 respeta la cota K entonces es la solucion exacta */
	vector<int> camino_w2 = algoritmo->reconstruirPathFloyd(u, v, floyd2);
	if(pesoEnRegla(camino_w1, pesos1_orig)) {
		imprimirSolucion(camino_w2, pesos1_orig, pesos2_orig);
		delete algoritmo;
		return;
	}

	unsigned int nodoActual = u;
	bool finalRecorrido = false;
	vector<int> caminoFinal = vector<int>();
	while(nodoActual != v && !finalRecorrido) {	// O(n), caso en el cual tenemos un camino hamiltoniano que pasa por todos los nodos.
		caminoFinal.push_back(nodoActual);								// O(1)
		camino_w2 = algoritmo->reconstruirPathFloyd(nodoActual, v, floyd2);				// O(n)

		/* tomo el primer nodo nodo_1 del camino_w2 entre el nodoActual y v, 
			- caso 1: si es menor a k el peso en w1 entonces es el minimo posible por aca en w2 y cumple w1 
		 	- caso 2: sino me fijo si en el peor de los casos, siguiendo por nodo_1 y a partir de ahi hacer
		 		el camino_w1 cumple que el peso sea menor a k, si es asi avanzo un nodo y repito el procedimiento
		 	- caso 3: si ninguna de las dos condiciones anteriores se cumple entonces me veo obligado a avanzar al
		 		primer nodo del camino_w1 y repetir el procedimiento */

		/* primer nodo del camino_w2 */
		int nodo1_w2 = camino_w2[1];									// O(1)
		vector<int> camino_w2_potencial = algoritmo->reconstruirPathFloyd(nodo1_w2, v, floyd2);	// O(n)
		vector<int> camino_aux = unirCaminos(caminoFinal, camino_w2_potencial);			// O(n^2)
		camino_aux.push_back(v);									// O(1)

		if(pesoEnRegla(camino_aux, pesos1_orig)) {							// O(n^2)
			/* caso 1 */
			caminoFinal = unirCaminos(caminoFinal, camino_w2_potencial);				// O(n^2)
			finalRecorrido = true;									// O(1)
		} else {
			/* caso 2 o 3 */
			vector<int> camino_w1_potencial = algoritmo->reconstruirPathFloyd(nodo1_w2, v, floyd1);	// O(n)
			vector<int> camino_aux = unirCaminos(caminoFinal, camino_w1_potencial);		// O(n^2)
			camino_aux.push_back(v);								// O(1)
			if(pesoEnRegla(camino_aux, pesos1_orig)) {						// O(n^2)
				/* caso 2 */
				nodoActual = nodo1_w2;								// O(1)
			} else {
				camino_w1_potencial = algoritmo->reconstruirPathFloyd(nodoActual, v, floyd1);	// O(n)
				vector<int> camino_aux = unirCaminos(caminoFinal, camino_w1_potencial);	// O(n^2)
				camino_aux.push_back(v);							// O(1)
				if(pesoEnRegla(camino_aux, pesos1)) {						// O(n^2)
					/* primer nodo del camino_w1 */
					nodoActual = camino_w1_potencial[1]; 					// O(1)
				} else {
					cout << "no";								// O(1)
					return;									// O(1)
				}
			}
			
		}
	}

	/* por ultimo agregamos v al camino final */
	caminoFinal.push_back(v);

	imprimirSolucion(caminoFinal, pesos1_orig, pesos2_orig);
	
	delete algoritmo;
	
	return;
	
}


/***
 * La funcion pesoEnRegla obtiene el peso del camino y lo compara con la cota K.
 * La complejidad es O(n) siendo n la longitud del camino.
 */
bool heuristicaGreedy::pesoEnRegla(vector<int> camino, &vector<vector<double> > pesos) {
	return k >= getPeso(camino, pesos);	// O(n)
}


/***
 * La funcion getPeso recorre todos los nodos del camino pasado por parametro sumando los pesos
 * de los mismos en un acumulador. Su complejidad es O(n) siendo n la longitud del camino.
 */
double heuristicaGreedy::getPeso(vector<int> camino, &vector<vector<double> > pesos) {
	double pesoTotal = 0.0;
	for(unsigned int i=0; i<camino.size()-1; i++) {	// O(n), caso en el cual tenemos un camino hamiltoniano que pasa por todos los nodos.
		pesoTotal += pesos[camino[i]][camino[i+1]];	// acceso a la matriz en O(1)
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

/***
 * La funcion unirCaminos toma los dos caminos pasados por parametros y los retorna unidos en un vector nuevo.
 * La complejidad es entonces O(l1+l2) siendo l1 y l2 las longitudes de ambos caminos.
 * Para nuestro problema en el peor caso los dos caminos pasan por todos los nodos, por lo tanto la complejidad
 * del peor caso es O(n^2)
 */
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
