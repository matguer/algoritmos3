#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <assert.h>
#include <math.h>
#include "../graph.h"
#include "backtrack.cpp"

using namespace std;

void backtrack(graph * grafo, int nodo_objetivo, double k, vector<bool> * nodos_visitados, Camino & camino_actual, Camino & mejor_camino, list<pair<double, double> > * posibles_caminos);

int main(int argc, char* argv[]){
		

		// Leo la entrada
		unsigned int n;
		unsigned int m;
		unsigned int u;
		unsigned int v;
		double k;
		int separador;
		
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
			
			graph * grafo = new graph(n);
			
			for(unsigned int i = 0; i<m; i++){
					cin >> v1;
					cin >> v2;
					cin >> w1;
					cin >> w2;
					grafo->add_edge(v1-1,v2-1,w1,w2);
			}

			//grafo->print();
			
			// Todos los caminos que llegan
			list<pair<double, double> > * posibles_caminos = new list<pair<double, double> >();
			
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
			
			backtrack(grafo, v-1, k, nodos_visitados, camino_actual, mejorcamino, posibles_caminos);
			
			// Muestro el mejor camino encontrado que este acotado por K y minimice w2
			if((*mejorcamino.camino).size()>0){
				cout << mejorcamino.w1_total << " " << mejorcamino.w2_total;
				cout << " " << (*mejorcamino.camino).size();
				for(list<int>::iterator f = (*mejorcamino.camino).begin(); f != (*mejorcamino.camino).end(); f++){
					cout << " " << (*f+1);
				}
			}else{
				cout << "no";
			}
			
			// Muestro el mejor camino encontrado que este acotado por K y minimice w2
			/*
			cout << "Otros caminos:" << endl;
			for(list<pair<double, double> >::iterator c = posibles_caminos->begin(); c != posibles_caminos->end(); c++)
				cout << c->first << " " << c->second << endl;
			}
			*/
			
			// Capturo el 0 final
			cin >> separador;
			cout << endl;
			n = 0;

			delete grafo;
			delete mejorcamino.camino;
			delete camino_actual.camino;
			delete nodos_visitados;
			delete posibles_caminos;
			
		
		}
}
