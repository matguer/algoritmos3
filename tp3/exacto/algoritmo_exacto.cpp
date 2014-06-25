#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <assert.h>
#include <math.h>
#include "../graph.h"

using namespace std;

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
				grafo->add_edge(v1-1,v2-1,w1,w2);
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
		(*camino_actual.camino).push_back(u-1);
		camino_actual.w1_total = 0.0;
		camino_actual.w2_total = 0.0;
		vector<bool> * nodos_visitados = new vector<bool>(n, false);
		(*nodos_visitados)[u-1] = true;
		
		backtrack(grafo, v-1, k, nodos_visitados, camino_actual, mejorcamino);
		
		// Muestro el mejor camino encontrado que este acotado por K y minimice w2
		for(list<int>::iterator f = (*mejorcamino.camino).begin(); f != (*mejorcamino.camino).end(); f++){
			cout << (*f+1) << " ";
		}
		cout << endl;
		cout << "w1 total " << mejorcamino.w1_total << endl;
		cout << "w2 total " << mejorcamino.w2_total << endl << endl;

		delete grafo;
		delete mejorcamino.camino;
		delete camino_actual.camino;
		delete nodos_visitados;
}
