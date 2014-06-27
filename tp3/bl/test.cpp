#include "../graph.h"
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
		list_n.push_back(10);
		list_n.push_back(15);
		list_n.push_back(20);
		list_n.push_back(25);
		
		for(list<int>::iterator it_n = list_n.begin(); it_n != list_n.end(); it_n++){
			
			n = *it_n;
			v = n;

			for(int porcentaje = 2; porcentaje<=100; porcentaje++){
				
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

				clock_t t = clock();
				heuristicabl(grafo,u-1,v-1,k);
				t = clock() - t;

				cout << n << "\t" << (cant_aristas/2) << "\t" << t << endl;
			
				delete heuristica;
				delete grafo;
				
			}	
		}
	}
	
	return 0;
	
}
