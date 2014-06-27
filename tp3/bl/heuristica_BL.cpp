#include <iostream>
#include <stdlib.h>
#include <list>
#include <cmath>
#include <vector>
#include "../graph.h"
#include "../algoritmos.h"
#include "heuristica_BL.h"

using namespace std;

void heuristicabl(graph* grafo, unsigned int u, unsigned int v, double k){
	
	algoritmos* algoritmo = new algoritmos();

	vector<vector<double> > pesos1_orig = grafo->get_weights1();
	vector<vector<double> > pesos2_orig = grafo->get_weights2();

	vector<vector<double> > pesos1 = grafo->get_weights1();
	vector<vector<int> > floyd1 = algoritmo->floyd(pesos1);

	/* Generacion del camino minimo para w1 */
	vector<int> camino1 = algoritmo->reconstruirPathFloyd(u,v,floyd1);

	/* Si este peso supera el K entonces no voy a encontrar uno menor,
		por lo tanto no hay solucion */
	if(!pesoEnRegla(camino1,pesos1_orig,k)) {
		cout << "no";
		return;
	}

	vector<vector<double> > pesos2 = grafo->get_weights2();
	vector<vector<int> > floyd2 = algoritmo->floyd(pesos2);
	
	/* Se recorre todo el camino c1 y para cada par de nodos se va reemplazando el tramo por el 
		camino minimo entre ese par de nodos para w2. En cada iteracion si no se supera el 
		valor de K entonces se realiza el reemplazo.*/
	unsigned int j = 0;
	while(j<camino1.size() - 1) {
		vector<int> tramoCamino2 = algoritmo->reconstruirPathFloyd(camino1[j],camino1[j+1], floyd2);
		vector<int> caminoNuevo = switchTramo(camino1, tramoCamino2, j);
		borrarRepetidos(caminoNuevo);
		if(pesoEnRegla(caminoNuevo,pesos1_orig,k)) {
			camino1 = caminoNuevo;
		}
		j++;
	}
	
	delete algoritmo;

	imprimirSolucion(camino1, pesos1_orig, pesos2_orig);
}


bool pesoEnRegla(vector<int> camino, vector<vector<double> > pesos, double k) {
	return k >= getPeso(camino, pesos);
}

double getPeso(vector<int> camino, vector<vector<double> > pesos) {
	double pesoTotal = 0.0;
	for(unsigned int i=0; i<camino.size()-1; i++) {
		pesoTotal += pesos[camino[i]][camino[i+1]];
	}
	return pesoTotal;
}

vector<int> switchTramo(vector<int> camino1, vector<int> tramoNuevo, int nodoSource) {
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

void imprimirCamino(vector<int> camino) {
	for(vector<int>::const_iterator it = camino.begin(); it != camino.end(); ++it)
		cout << (*it+1) << " ";
}

void imprimirSolucion(vector<int> camino, vector<vector<double> > pesos1, vector<vector<double> > pesos2) {
	double pesoTotal1 = getPeso(camino, pesos1);
	double pesoTotal2 = getPeso(camino, pesos2);
	
	cout << pesoTotal1 << " " << pesoTotal2 << " " << camino.size() << " ";
	imprimirCamino(camino);
}


void borrarRepetidos(vector<int>& v) {
    int i=v.size() - 1;
    int j=i-1;
    list<int> camino;
    while(i>=0) {
        camino.push_back(v[i]);
        int aux = j;
        while(aux >= 0) {
            if(v[aux] == v[i]) {
            	j = aux-1;
            }
            aux--;
        }
        i=j;
        j--;
    }
    v = vector<int>(camino.size(), 0);
    for(unsigned int x=0; x<v.size(); x++) {
        v[x] = camino.back();
        camino.pop_back();
    }
}
