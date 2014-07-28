#include "../graph.h"
#include "backtrack.cpp"
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

			for(int porcentaje = 1; porcentaje<=100; porcentaje=porcentaje+5){
				
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
				
				clock_t t = clock();
				backtrack(grafo, v-1, k, nodos_visitados, camino_actual, mejorcamino, posibles_caminos);
				t = clock() - t;
				if((*mejorcamino.camino).size()>0){
					cout << mejorcamino.w1_total << " " << mejorcamino.w2_total;
					cout << " " << (*mejorcamino.camino).size();
					for(list<int>::iterator f = (*mejorcamino.camino).begin(); f != (*mejorcamino.camino).end(); f++){
						cout << " " << (*f+1);
					}
				}else{
					cout << "no";
				}
				cout << endl;

				if((double)t > 0.0)
					cerr << n << "\t" << (cant_aristas/2) << "\t" << t << endl;
			
				delete grafo;
				
			}	
		}
	}
	
	return 0;
	
}
