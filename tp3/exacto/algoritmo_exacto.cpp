#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <assert.h>
#include <math.h>
#include "../graph.h"

using namespace std;

void backtrack(graph * grafo, int nodo_objetivo, double k, vector<bool> * nodos_visitados, Camino & camino_actual, Camino & mejor_camino);

int main(int argc, char* argv[]){
		

		// Leo la entrada
		unsigned int n;
		unsigned int m;
		unsigned int u;
		unsigned int v;
		double k;
		
		unsigned int v1;
		unsigned int v2;
		double w1;
		double w2;

		cin >> n;
		cin >> m;
		cin >> u;
		cin >> v;
		cin >> k;
		
		graph * grafo = new graph(n);
		
		for(unsigned int i = 0; i<m; i++){
				cin >> v1;
				cin >> v2;
				cin >> w1;
				cin >> w2;
				grafo->add_edge(v1,v2,w1,w2);
		}
		
		//grafo->print();
		
		// Estructura que guarda el mejor camino que encontre cumpliendo ambas condiciones
		Camino mejorcamino = Camino();
		mejorcamino.camino = new list<int>();
		mejorcamino.w1_total = 0;
		mejorcamino.w2_total = INFINITY;

		// El camino que voy construyendo en cada rama del backtracking, siempre arranca desde u
		Camino camino_actual = Camino();
		camino_actual.camino = new list<int>();
		(*camino_actual.camino).push_back(u);
		camino_actual.w1_total = 0.0;
		camino_actual.w2_total = 0.0;
		vector<bool> * nodos_visitados = new vector<bool>(n+1, false);
		(*nodos_visitados)[u] = true;
		
		backtrack(grafo, v, k, nodos_visitados, camino_actual, mejorcamino);
		
		// Muestro el mejor camino encontrado que este acotado por K y minimice w2
		for(list<int>::iterator f = (*mejorcamino.camino).begin(); f != (*mejorcamino.camino).end(); f++){
			cout << *f << " ";
		}
		cout << endl;
		cout << "w1 total " << mejorcamino.w1_total << endl;
		cout << "w2 total " << mejorcamino.w2_total << endl << endl;

		delete grafo;
		delete mejorcamino.camino;
		delete camino_actual.camino;
		delete nodos_visitados;
}

void backtrack(graph * grafo, int nodo_objetivo, double k, vector<bool> * nodos_visitados, Camino & camino_actual, Camino & mejor_camino) {
	
	int ultimo_nodo = (*camino_actual.camino).back(); // Ultimo nodo agregado
	list<int> * nodos_adyacentes = grafo->get_adyacentes(ultimo_nodo); // Nodos adyacentes al ultimo nodo recorrido
	
	// Si me pase de la cota K corto esta rama
	if(camino_actual.w1_total > k){
		//cout << "me pase de la cota " << camino_actual.w1_total << " vs " << k << endl;
		return;
	}
	
	// Si ya encontre el nodo final termino
	if(ultimo_nodo == nodo_objetivo){
		/*
		for(list<int>::iterator f = (*camino_actual.camino).begin(); f != (*camino_actual.camino).end(); f++){
			cout << *f << " " << endl;
		}
		cout << endl;
		cout << "w1 total " << camino_actual.w1_total << endl;
		cout << "w2 total " << camino_actual.w2_total << endl << endl;
		*/
		if(camino_actual.w2_total < mejor_camino.w2_total){
			delete mejor_camino.camino;
			mejor_camino.camino = new list<int>((*camino_actual.camino));
			mejor_camino.w1_total = camino_actual.w1_total;
			mejor_camino.w2_total = camino_actual.w2_total;
		}
		return;
	}
	
	// Recorro los adyancentes del ultimo nodo recorrido
	for(list<int>::iterator nodo = nodos_adyacentes->begin(); nodo != nodos_adyacentes->end(); nodo++){
		// Si ya visite el nodo termino
		if((*nodos_visitados)[*nodo] == true){
			continue;
		}

		(*nodos_visitados)[*nodo] = true; // Marco el nodo como visitado para hacer el llamado recursivo
		(*camino_actual.camino).push_back(*nodo);
		camino_actual.w1_total = camino_actual.w1_total + grafo->get_w1(ultimo_nodo, *nodo);
		camino_actual.w2_total = camino_actual.w2_total + grafo->get_w2(ultimo_nodo, *nodo);
		
		backtrack(grafo, nodo_objetivo, k, nodos_visitados, camino_actual, mejor_camino);
		// Restauro el estado para cuando vuelva
		camino_actual.w1_total = camino_actual.w1_total - grafo->get_w1(ultimo_nodo, *nodo);
		camino_actual.w2_total = camino_actual.w2_total - grafo->get_w2(ultimo_nodo, *nodo);
		(*nodos_visitados)[*nodo] = false;
		(*camino_actual.camino).pop_back();
				
		
	}
	
	
}
