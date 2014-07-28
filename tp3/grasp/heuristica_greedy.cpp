#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <assert.h>
#include <cmath>
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

vector<int> heuristicaGreedy::execute(graph * grafo, int seed) {

	vector<vector<double> > pesos1_orig = grafo->get_weights1();
	vector<vector<double> > pesos2_orig = grafo->get_weights2();

	vector<vector<double> > pesos1 = grafo->get_weights1();
	vector<vector<double> > pesos2 = grafo->get_weights2();
	Algoritmos* algoritmo = new Algoritmos();

	vector<vector<int> > floyd1 = algoritmo->floyd(pesos1);
	vector<vector<int> > floyd2 = algoritmo->floyd(pesos2);
	
	vector<int> caminoFinal = vector<int>();

	/* Si el camino minimo en w1 es mayor a la cota K entonces no hay solucion */
	vector<int> camino_w1 = algoritmo->reconstruirPathFloyd(u, v, floyd1);
	if(!pesoEnRegla(camino_w1, pesos1_orig)) {
		return caminoFinal;
	}

	/* Si el camino minimo en w2 respeta la cota K entonces es la solucion exacta */
	vector<int> camino_w2 = algoritmo->reconstruirPathFloyd(u, v, floyd2);
	if(pesoEnRegla(camino_w2, pesos1_orig)) {
		return camino_w2;
	}
	
	srand(seed);

	int cant_nodos = grafo->get_cant_nodos();
	int visitados[cant_nodos];
	for(int i=0; i<cant_nodos; i++){
		visitados[i] = 0;
	}
	
	unsigned int nodoActual = u;
	while(nodoActual != v) {	
		
		caminoFinal.push_back(nodoActual);								
		visitados[nodoActual] = 1;
		
		vector<int> nodos_potenciales;
		list<int> adyacentes = *(grafo->get_adyacentes(nodoActual));
		
		for(list<int>::const_iterator it = adyacentes.begin(); it != adyacentes.end(); ++it) {
			unsigned int nodo = *it;
			if(visitados[nodo] == 0) {
				vector<int> camino_temp = algoritmo->reconstruirPathFloyd(nodo, v, floyd1);
				if(pesoEnRegla(unirCaminos(caminoFinal, camino_temp), pesos1_orig)){
					if(nodo == v) {
						nodoActual = v;
						break;
					} else {
						nodos_potenciales.push_back(nodo);
					}
				}
			}
		}
		
		if(nodoActual != v) {
			if(nodos_potenciales.size() == 0) {
				/* no encontro solucion */
				return vector<int>();
			}
			int nodo_elegido = rand() % nodos_potenciales.size();	
			nodoActual = nodos_potenciales[nodo_elegido];
		}
	}

	caminoFinal.push_back(nodoActual);
	borrarRepetidos(caminoFinal);
	delete algoritmo;
	return caminoFinal;
		
}


/***
 * La funcion pesoEnRegla obtiene el peso del camino y lo compara con la cota K.
 * La complejidad es O(n) siendo n la longitud del camino.
 */
bool heuristicaGreedy::pesoEnRegla(vector<int> camino, vector<vector<double> > pesos) {
	return k >= getPeso(camino, pesos);	// O(n)
}


/***
 * La funcion getPeso recorre todos los nodos del camino pasado por parametro sumando los pesos
 * de los mismos en un acumulador. Su complejidad es O(n) siendo n la longitud del camino.
 */
double heuristicaGreedy::getPeso(vector<int> camino, vector<vector<double> > pesos) {
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
 * del peor caso es O(2*n), asintoticamente O(n).
 */
vector<int> heuristicaGreedy::unirCaminos(vector<int> camino1, vector<int> camino2) {
	int size1 = camino1.size();
	int size2 = camino2.size();
	vector<int> caminoNuevo = vector<int>(size1 + size2, 0);
	
	for(int i=0; i<size1; i++) {
		caminoNuevo[i] = camino1[i];
	}

	for(int i=0; i<size2; i++) {
		caminoNuevo[size1 + i] = camino2[i];
	}

	return caminoNuevo;
}

/***
 * El metodo borrarRepetidos comienza a recorrer del final hacia adelante
 * el camino pasado por parametro y bueca las repeticiones. En caso de haber 
 * mas de una se queda con la mas cercana al comienzo del camino
 * y elimina todo el tramo intermedio entre el nodo y su repeticion.
 * La complejidad esta dada por dos for anidados que en el peor de los casos
 * recorren n nodos, por ende es O(n^2).
 */
void heuristicaGreedy::borrarRepetidos(vector<int>& v) {
    int i=v.size() - 1;				// O(1)
    int j=i-1;					// O(1)
    list<int> camino;				// O(1)
    while(i>=0) {				// O(n)
        camino.push_back(v[i]);			// O(1)
        int aux = j;				// O(1)
        while(aux >= 0) {			// O(n)
            if(v[aux] == v[i]) {		// O(1)
            	j = aux-1;			// O(1)
            }
            aux--;				// O(1)
        }
        i=j;					// O(1)
        j--;					// O(1)
    }
    v = vector<int>(camino.size(), 0);		// O(n)
    for(unsigned int x=0; x<v.size(); x++) {	// O(n)
        v[x] = camino.back();			// O(1)
        camino.pop_back();			// O(1)
    }
}
