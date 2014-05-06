#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <assert.h>
#include "directed_graph.h"

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

unsigned int getNumeroNodo(unsigned int n, unsigned int k, unsigned int fila, unsigned int col, unsigned int estado){
	
	unsigned int nro_nodo_vecino = (fila*n*(k+1) + (col*(k+1)) + estado);
	assert(0 <= nro_nodo_vecino);
	assert(nro_nodo_vecino < n*n*(k+1));
					
	return nro_nodo_vecino;
}

int main(int argc, char* argv[]){
		
		// Si se recibe un 1 por parametro se ejecuta el test de BFS (SACAR A LA HORA DE LA ENTREGA)	
		if(argc > 1 && atoi(argv[1]) == 1) {

			directed_graph * grafo = new directed_graph(7);
			grafo->add_edge(0,1);
			grafo->add_edge(0,2);
			grafo->add_edge(0,3);
			
			grafo->add_edge(1,0);
			
			grafo->add_edge(2,0);
			grafo->add_edge(2,3);
			grafo->add_edge(2,4);
			
			grafo->add_edge(3,0);
			grafo->add_edge(3,2);
			grafo->add_edge(3,5);
			grafo->add_edge(3,6);
			
			grafo->add_edge(4,2);
			
			grafo->add_edge(5,3);
			
			grafo->add_edge(6,3);

			list<int> camino = grafo->bfs(4, 3, 3);
			// Muestro el camino
			for(list<int>::iterator i = camino.begin(); i != camino.end(); i++) {
				
				cout << *i << " - ";
			}
			
			cout << endl << endl;
			
			delete grafo;

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
		
		unsigned int fila_nodo_actual;
		unsigned int columna_nodo_actual;
		unsigned int estado_nodo_actual;
		unsigned int potencia_nodo_actual;
		unsigned int nro_nodo_vecino;
		unsigned int k_restantes;
		
		// Asigno las posibles aristas, i = todos los posibles nodos que representan tanto casillas sin gastos de k como con algun gasto
		// O((n^2)*k) * O(2*n)
		for(unsigned int i = 0; i<cant_nodos; i++){
			
			// Datos de la casilla
			fila_nodo_actual = (i / (k+1)) / n;
			columna_nodo_actual = ((i / (k+1)) % n);
			estado_nodo_actual = i % (k+1);
			potencia_nodo_actual = (*potencias)[fila_nodo_actual][columna_nodo_actual];
			k_restantes = k-estado_nodo_actual;
			
			//cout << i << ": f " << fila_nodo_actual << " c " << columna_nodo_actual << " e " << estado_nodo_actual << " p " << potencia_nodo_actual << endl;
				
			// Recorro la fila y conecto la casilla con todas las alcanzables de la misma
			// O(n)
			for(unsigned int j=0; j<n; j++){

				// Evito conectar la casilla consigo misma
				if(j!=columna_nodo_actual){
					
					int diferencia = columna_nodo_actual-potencia_nodo_actual;

					if( diferencia <= (int) j && j <= (columna_nodo_actual+potencia_nodo_actual)){
						nro_nodo_vecino = getNumeroNodo(n, k, fila_nodo_actual, j, estado_nodo_actual);
						// Conecto el nodo de la casilla actual en estado_nodo_actual 0 con el nodo de la casilla 
						// alcanzable en estado_nodo_actual 0 ya que no gaste ningun k para llegar ahi
						grafo->add_edge(i,nro_nodo_vecino);
					
					// Veo si puedo llegar usando k
					}else{
						diferencia = columna_nodo_actual-(potencia_nodo_actual+k_restantes);
						
						// Si el poder de la casilla mas los k restantes del estado me lo permiten...
						if( diferencia <= (int) j && j <= (columna_nodo_actual+potencia_nodo_actual+k_restantes)){
							
							int cuanto_k_necesito = 0;
							
							if(columna_nodo_actual <= (int) j){
								cuanto_k_necesito = j - potencia_nodo_actual - columna_nodo_actual;
							}else{
								cuanto_k_necesito = columna_nodo_actual - potencia_nodo_actual - j;
							}
							
							// Lo voy a juntar con el nodo que puedo llegar pero a un estado correspondiente
							nro_nodo_vecino = getNumeroNodo(n, k, fila_nodo_actual, j, estado_nodo_actual+cuanto_k_necesito);
							// Conecto el nodo de la casilla actual en estado_nodo_actual 0 con el nodo de la casilla 
							// alcanzable a su estado_nodo_actual correspondiente segun el gasto de k
							grafo->add_edge(i,nro_nodo_vecino);
						}
						
					}
				}

			}
			// fin recorrido de la fila
			
			
			// Recorro la columna y conecto la casilla con todas las alcanzables de la misma
			// O(n)
			for(unsigned int j=0; j<n; j++){
				
				// Evito conectar la casilla consigo misma
				if(j!=fila_nodo_actual){
					
					int diferencia = fila_nodo_actual-potencia_nodo_actual;
					
					if( diferencia <= (int) j && j <= (fila_nodo_actual+potencia_nodo_actual)){
						nro_nodo_vecino = getNumeroNodo(n, k, j, columna_nodo_actual, estado_nodo_actual);
						// Conecto el nodo de la casilla actual en estado_nodo_actual 0 con el nodo de la casilla 
						// alcanzable en estado_nodo_actual 0 ya que no gaste ningun k para llegar ahi
						grafo->add_edge(i,nro_nodo_vecino);
					
					// Veo si puedo llegar usando k
					}else{

						diferencia = fila_nodo_actual-(potencia_nodo_actual+k_restantes);
						
						// Si el poder de la casilla mas los k restantes del estado me lo permiten...
						if( diferencia <= (int) j && j <= (fila_nodo_actual+potencia_nodo_actual+k_restantes)){
							
							int cuanto_k_necesito = 0;
							
							if(fila_nodo_actual <= (int) j){
								cuanto_k_necesito = j - potencia_nodo_actual - fila_nodo_actual;
							}else{
								cuanto_k_necesito = fila_nodo_actual - potencia_nodo_actual - j;
							}
							
							// Lo voy a juntar con el nodo que puedo llegar pero a un estado correspondiente
							nro_nodo_vecino = getNumeroNodo(n, k, j, columna_nodo_actual, estado_nodo_actual+cuanto_k_necesito);
							// Conecto el nodo de la casilla actual en estado_nodo_actual 0 con el nodo de la casilla 
							// alcanzable a su estado_nodo_actual correspondiente segun el gasto de k
							grafo->add_edge(i,nro_nodo_vecino);
						}
						
					}
				}

			}
			// fin recorrido de la columna_nodo_actual

		}
		
		//grafo->print();

		int nro_nodo_inicio = getNumeroNodo(n, k, fo-1, co-1, 0);
		int nro_nodo_fin = getNumeroNodo(n, k, fd-1, cd-1, 0);
		int k_ultimo_estado = 0;
		int k_usado = 0;
		
		list<int> camino = grafo->bfs(nro_nodo_inicio, nro_nodo_fin+k, nro_nodo_fin+k);
		camino.reverse();
		camino.pop_front();		
		
		cout << camino.size() << endl;
	
		// Muestro el camino
		for(list<int>::iterator i = camino.begin(); i != camino.end(); i++) {
			int fila_nodo_actual = ((*i) / (k+1)) / n;
			int columna_nodo_actual = (((*i) / (k+1)) % n);
			int estado_nodo_actual = (*i) % (k+1);
			
			if(k_ultimo_estado!=estado_nodo_actual){
				k_usado = estado_nodo_actual - k_ultimo_estado;
				k_ultimo_estado = estado_nodo_actual;
			}else{
				k_usado = 0;
			}
			
			cout << fila_nodo_actual << " " << columna_nodo_actual << " " << k_usado << endl;
		}
		
		
		delete grafo;
		delete potencias;
		
}



