#include <iostream>
#include <stdlib.h>
#include <list>
#include <cmath>
#include <vector>
#include "../graph.h"
#include "../Algoritmos.h"
#include "heuristica_BL.h"

using namespace std;

int main(int argc, char* argv[]) {

	// Leo la entrada
	double k;
	graph* grafo;
	int separador;
	unsigned int n;
	unsigned int m;
	unsigned int u;
	unsigned int v;
	
	unsigned int v1;
	unsigned int v2;
	double w1;
	double w2;
	
	while(true) {
			
		// Si termine de leer el archivo salgo
		if(cin.eof()){
			break;
		}

		cin >> n;
		cin >> m;
		cin >> u;
		cin >> v;
		cin >> k;
		
		if(n == 0){
			break;
		}
		
		grafo = new graph(n);
		
		for(unsigned int i = 0; i<m; i++){
				cin >> v1;
				cin >> v2;
				cin >> w1;
				cin >> w2;
				grafo->add_edge(v1-1,v2-1,w1,w2);
		}

		heuristicabl(grafo,u-1,v-1,k);
		
		// Capturo el 0 final
		cin >> separador;
		cout << endl;
		n = 0;
		
		delete grafo;
		
	}

	return 0;
}
