#include "../graph.h"
#include "heuristica_grasp.h"
#include "heuristica_greedy.h"
#include <time.h>
#include <cmath>

using namespace std;

/**
 * La función main toma el listado de trabajos por std input:
 */
int main(int argc, char *argv[])
{
	int seed = (int) *argv[1]; // Semilla para los rand()
	int cant_aristas = 0;
	int u = 1;
	int n = 0;
	int w1 = 0;
	int w2 = 0;
	int v = 0;
	int k = 1000;

	if(seed>0){
				
		srand(seed);
		
		// Tests aleatorios	
		list<int> list_n = list<int>();
		for (int i=10; i<=18; i++) {
		  list_n.push_back(i);
		}
		
		for(list<int>::iterator it_n = list_n.begin(); it_n != list_n.end(); it_n++){
			
			n = *it_n;
			v = n;

			for(int porcentaje = 1; porcentaje<=100; porcentaje+=5){
				
				cant_aristas = 0;
				graph * grafo = new graph(n);
				
				// Genero un arbol para asegurarme que al menos hay un camino para llegar de u a v
				for(int i = 0; i<n-1; i++){
					cant_aristas++;
					w1 = rand() % 1000;
					w2 = rand() % 1000;
					grafo->add_edge(i,i+1,w1,w2);
				}
			
				// Conecto al azar aristas
				for(int i = 0; i<n-1; i++){
					for(int j = 0; j<n-1; j++){
						if(i!=j && i!=j+1 && (rand() % 100 < porcentaje)){
							cant_aristas++;
							w1 = rand() % 1000;
							w2 = rand() % 1000;
							grafo->add_edge(i,j,w1,w2);
						}
					}
				}
				
				vector<vector<double> > pesos1 = grafo->get_weights1();
				vector<vector<double> > pesos2 = grafo->get_weights2();
				
				cout << n << " " << cant_aristas*2 << " " << u << " " << v << " " << k << endl;
				for(int i = 0; i<n; i++){
					list<int> ady = *(grafo->get_adyacentes(i));
					for(list<int>::iterator it = ady.begin(); it != ady.end(); ++it) {
						int nodo = *it;
						cout << i+1 << " " << nodo+1 << " " << pesos1[i][nodo] << " " << pesos2[i][nodo] << endl;
					}
				}
				cout << "SEP" << endl;
			
				delete grafo;
				
			}	
			
		}
	}
	
	return 0;
	
}
