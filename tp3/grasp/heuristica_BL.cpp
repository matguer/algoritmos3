#include <iostream>
#include <stdlib.h>
#include <list>
#include <cmath>
#include <vector>
#include "../graph.h"
#include "../Algoritmos.h"
#include "heuristica_BL.h"

using namespace std;

heuristicabl::heuristicabl(double k, unsigned int u, unsigned int v){
	this->k = k;
	this->u = u;
	this->v = v;
}
heuristicabl::~heuristicabl(){}

vector<int> heuristicabl::execute(graph * grafo, vector<int>& solucion_inicial) {

	vector<vector<double> > pesos1_orig = grafo->get_weights1();
	vector<vector<double> > pesos2_orig = grafo->get_weights2();
	
	Algoritmos* algoritmo = new Algoritmos();

	vector<int> solucion_final = solucion_inicial;
	
	vector<vector<double> > pesos2 = grafo->get_weights2();
	vector<vector<int> > floyd2 = algoritmo->floyd(pesos2);
	vector<int> camino2 = algoritmo->reconstruirPathFloyd(u,v,floyd2);
	
	/* Se recorre todo el camino c1 y para cada par de nodos se va reemplazando el tramo por el 
		camino minimo entre ese par de nodos para w2. En cada iteracion si no se supera el 
		valor de K entonces se realiza el reemplazo.
	   Como vemos la complejidad de este tramo de procesamiento se corresponde a n iteraciones de 
	   acciones que en el peor caso demora O(n^2), por ende la complejidad total sera O(n^3).
	*/
	for(unsigned int j=0; j<solucion_final.size()-1; j++) {							// O(n)
		vector<int> tramoCamino2 = algoritmo->reconstruirPathFloyd(solucion_final[j],solucion_final[j+1], floyd2);	// O(n)
		vector<int> caminoNuevo = switchTramo(solucion_final, tramoCamino2, j);				// O(n)
		borrarRepetidos(caminoNuevo);									// O(n^2)
		if(pesoEnRegla(caminoNuevo,pesos1_orig,k)) {							// O(n)
			solucion_final = caminoNuevo;									// O(n)
		}
	}
	
	delete algoritmo;

	return solucion_final;
}


/***
 * La funcion pesoEnRegla obtiene el peso del camino y lo compara con la cota K.
 * La complejidad es O(n) siendo n la longitud del camino.
 */
bool heuristicabl::pesoEnRegla(vector<int> camino, vector<vector<double> > pesos, double k) {
	return k >= getPeso(camino, pesos);	// O(n)
}


/***
 * La funcion getPeso recorre todos los nodos del camino pasado por parametro sumando los pesos
 * de los mismos en un acumulador. Su complejidad es O(n) siendo n la longitud del camino.
 */
double heuristicabl::getPeso(vector<int> camino, vector<vector<double> > pesos) {
	double pesoTotal = 0.0;
	for(unsigned int i=0; i<camino.size()-1; i++) {	// O(n), caso en el cual tenemos un camino hamiltoniano que pasa por todos los nodos.
		pesoTotal += pesos[camino[i]][camino[i+1]];	// acceso a la matriz en O(1)
	}
	return pesoTotal;
}

/***
 * La funcion switchTramo recibe un camino, el tramo de camino nuevo a insertar y el nodo desde el
 * cual se realizara el cambio, asumiendo que se realiza entre el mismo y el siguiente en el camino.
 * En cuanto a la complejidad, en el peor de los casos tanto el camino como el tramoNuevo tienen
 * longitud n, de esta manera la complejidad del metodo seria O(2*n), acotado asintoticamente a
 * O(n).
 */
vector<int> heuristicabl::switchTramo(vector<int> camino1, vector<int> tramoNuevo, int nodoSource) {
	unsigned int sizeCamino1 = camino1.size();
	unsigned int sizeTramoNuevo = tramoNuevo.size();

	vector<int> caminoNuevo = vector<int>(sizeCamino1 + sizeTramoNuevo - 2, 0);

	/* El caminoNuevo se mantiene igual que camino1 hasta la posicion indicada como nodoSource */
	for(int i=0; i<=nodoSource; i++) {
		caminoNuevo[i] = camino1[i];
	}

	/* A partir del nodoSource en adelante se agrega el tramoNuevo */
	for(int i=nodoSource+1; i<(nodoSource + sizeTramoNuevo - 1); i++) {
		caminoNuevo[i] = tramoNuevo[i-nodoSource];
	}

	/* Una vez que se completo el tramoNuevo se siguen agregando las ultimas posiciones del camino1 */
	for(unsigned int i=nodoSource+sizeTramoNuevo - 1; i<caminoNuevo.size(); i++) {
		caminoNuevo[i] = camino1[i-sizeTramoNuevo+2];
	}
	
	return caminoNuevo;
}

void heuristicabl::imprimirCamino(vector<int> camino) {
	for(vector<int>::const_iterator it = camino.begin(); it != camino.end(); ++it)
		cout << (*it+1) << " ";
}

void heuristicabl::imprimirSolucion(vector<int> camino, vector<vector<double> > pesos1, vector<vector<double> > pesos2) {
	double pesoTotal1 = getPeso(camino, pesos1);
	double pesoTotal2 = getPeso(camino, pesos2);
	
	cout << pesoTotal1 << " " << pesoTotal2 << " " << camino.size() << " ";
	imprimirCamino(camino);
	cout << endl;
}


/***
 * El metodo borrarRepetidos comienza a recorrer del final hacia adelante
 * el camino pasado por parametro y bueca las repeticiones. En caso de haber 
 * mas de una se queda con la mas cercana al comienzo del camino
 * y elimina todo el tramo intermedio entre el nodo y su repeticion.
 * La complejidad esta dada por dos for anidados que en el peor de los casos
 * recorren n nodos, por ende es O(n^2).
 */
void heuristicabl::borrarRepetidos(vector<int>& v) {
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
