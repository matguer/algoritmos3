#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <sstream>
#include <vector>
#include "directed_graph.h"
#include "BFS.h"

using namespace std;

void printTabla(vector< vector<unsigned int> > * tabla, unsigned int n){
	for(unsigned int i = 0; i<n; i++){
		for(unsigned int j = 0; j<n; j++){
			cout << (*tabla)[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}

int getNumeroNodo(unsigned int n, unsigned int k, unsigned int fila, unsigned int col, unsigned int estado){
	return (fila*n*(k+1) + (col*(k+1)) + estado);
}

int main(int argc, char* argv[]){
		
		// Si se recibe un 1 por parametro se ejecuta el test de BFS (SACAR A LA HORA DE LA ENTREGA)	
		if(argc > 1 && atoi(argv[1]) == 1) {
			BFS bfs;
			bfs.test();
			return 0;
		}

		// Leo la entrada
		unsigned int n;
		unsigned int fo;
		unsigned int co;
		unsigned int fd;
		unsigned int cd;
		unsigned int k;

		cin >> n;
		cin >> fo;
		cin >> co;
		cin >> fd;
		cin >> cd;
		cin >> k;
		
		unsigned int cant_nodos = n*n*(k+1);
		
		vector< vector<unsigned int> > * potencias = new vector<vector<unsigned int> >(n, vector<unsigned int>(n, 0));

		for(unsigned int i = 0; i<n; i++){
			for(unsigned int j = 0; j<n; j++){
				cin >> (*potencias)[i][j];
			}
		}
		
		//printTabla(potencias, n);
		directed_graph * grafo = new directed_graph(cant_nodos);
		
		unsigned int fila;
		unsigned int columna;
		unsigned int estado;
		unsigned int potencia;
		unsigned int nro_nodo_vecino;
		
		// Asigno las posibles aristas, i = nodo que representa la casilla en el estado que no se gasto ningun k
		// O((n^2)*k) * O(2*n)
		for(unsigned int i = 0; i<cant_nodos; i++){
			
			// Datos de la casilla
			fila = (i / (k+1)) / n;
			columna = ((i / (k+1)) % n);
			estado = i % (k+1);
			potencia = (*potencias)[fila][columna];
			
			//cout << i << ": f " << fila << " c " << columna << " e " << estado << " p " << potencia << endl;

			// Para los nodos que representan casillas sin gasto de k...
			if(estado==0){
				
				// Recorro la fila y conecto la casilla con todas las alcanzables de la misma
				// O(n)
				for(unsigned int j=0; j<n; j++){
					
					// Evito conectar la casilla consigo misma
					if(j!=columna){
						
						int diferencia = columna-potencia;
						
						if( diferencia <= (int) j && j <= (columna+potencia)){
							nro_nodo_vecino = getNumeroNodo(n, k, fila, j, 0);
							grafo->add_edge(i,nro_nodo_vecino);
						
						// Veo si puedo llegar usando k
						}else{
							
							diferencia = columna-(potencia+k);
							
							if( diferencia <= (int) j && j <= (columna+potencia+k)){
								int cuanto_k_necesito = j - potencia - columna;
								
								nro_nodo_vecino = getNumeroNodo(n, k, fila, j, cuanto_k_necesito);
								grafo->add_edge(i,nro_nodo_vecino);
							}
							
						}
					}

				}
				
				// Recorro la columna y conecto la casilla con todas las alcanzables de la misma
				// O(n)
				for(unsigned int j=0; j<n; j++){
					
					// Evito conectar la casilla consigo misma
					if(j!=fila){
						
						int diferencia = fila-potencia;
						
						if( diferencia <= (int) j && j <= (fila+potencia)){
							nro_nodo_vecino = getNumeroNodo(n, k, j, columna, 0);
							grafo->add_edge(i,nro_nodo_vecino);
						
						}
					}

				}
			
			}

		}
		
		grafo->print();
		
		delete grafo;
		delete potencias;
		
}



