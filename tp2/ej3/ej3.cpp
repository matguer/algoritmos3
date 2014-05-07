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

/*
 * Funcion que dada una fila, una columna y un estado de consumo de k, devuelve el numero de nodo correspondiente
 */
unsigned int getNumeroNodo(unsigned int tablero_casilleros_lado, unsigned int tablero_k, unsigned int fila, unsigned int col, unsigned int estado){
	
	unsigned int nro_nodo = (fila*tablero_casilleros_lado*(tablero_k+1) + (col*(tablero_k+1)) + estado);
	assert(0 <= nro_nodo);
	assert(nro_nodo < tablero_casilleros_lado*tablero_casilleros_lado*(tablero_k+1));
					
	return nro_nodo;
}

/*
 * Esta funcion decide dados dos nodos si hay una arista entre ellos y de que estado a que estado.
 * Si la hay, agrega la arista al grafo
*/
void unirNodos(directed_graph * grafo, int nro_nodo_fuente, int columna_nodo_fuente, int fila_nodo_fuente, int potencia_nodo_fuente, int estado_nodo_fuente, int columna_nodo_destino, int fila_nodo_destino, bool mirarFila, int tablero_casillas_por_lado, int tablero_k_inicial){
	
	int k_restantes = tablero_k_inicial-estado_nodo_fuente;
	int indice_fuente = 0;
	int indice_destino = 0;
	int nro_nodo_destino = 0;
	
	// Ajustamos los indices que nos interesan segun si estoy recorriendo fila o columna
	if(mirarFila){
		indice_fuente = columna_nodo_fuente;
		indice_destino = columna_nodo_destino;
	}else{
		indice_fuente = fila_nodo_fuente;
		indice_destino = fila_nodo_destino;
	}
	
	// Evito conectar la casilla consigo misma
	if(columna_nodo_fuente != columna_nodo_destino || fila_nodo_fuente!=fila_nodo_destino){
		
		// Verifico si el nodo de destino es alcanzable con la potencia de la casilla actual
		if( ((int) indice_fuente-potencia_nodo_fuente) <= (int) indice_destino && indice_destino <= (indice_fuente+potencia_nodo_fuente)){
			nro_nodo_destino = getNumeroNodo(tablero_casillas_por_lado, tablero_k_inicial, fila_nodo_destino, columna_nodo_destino, estado_nodo_fuente);
			// Conecto el nodo de la casilla actual en estado_nodo_actual 0 con el nodo de la casilla 
			// alcanzable en estado_nodo_actual 0 ya que no gaste ningun k para llegar ahi
			grafo->add_edge(nro_nodo_fuente,nro_nodo_destino);
		
		// Veo si puedo llegar usando k
		}else{
			int diferencia = indice_fuente-(potencia_nodo_fuente+k_restantes);
			
			// Si el poder de la casilla mas los k restantes del estado me lo permiten
			if( diferencia <= (int) indice_destino && indice_destino <= (indice_fuente+potencia_nodo_fuente+k_restantes)){
				int cuanto_k_necesito = 0;
				
				if(indice_fuente <= (int) indice_destino){
					cuanto_k_necesito = indice_destino - potencia_nodo_fuente - indice_fuente;
				}else{
					cuanto_k_necesito = indice_fuente - potencia_nodo_fuente - indice_destino;
				}
				// Lo voy a juntar con el nodo que puedo llegar pero a un estado correspondiente
				nro_nodo_destino = getNumeroNodo(tablero_casillas_por_lado, tablero_k_inicial, fila_nodo_destino, columna_nodo_destino, estado_nodo_fuente+cuanto_k_necesito);
				// Conecto el nodo de la casilla actual en estado_nodo_actual 0 con el nodo de la casilla 
				// alcanzable a su estado_nodo_actual correspondiente segun el gasto de k
				grafo->add_edge(nro_nodo_fuente,nro_nodo_destino);
			}
			
		}
	}
}

int main(int argc, char* argv[]){
		
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
		
		unsigned int fila_nodo_fuente;
		unsigned int columna_nodo_fuente;
		unsigned int estado_nodo_fuente;
		unsigned int potencia_nodo_fuente;
		
		// Asigno las posibles aristas, i = todos los posibles nodos que representan tanto casillas sin gastos de k como con algun gasto
		for(unsigned int nro_nodo_fuente = 0; nro_nodo_fuente<cant_nodos; nro_nodo_fuente++){
			
			// Datos de la casilla fuente
			fila_nodo_fuente = (nro_nodo_fuente / (k+1)) / n;
			columna_nodo_fuente = ((nro_nodo_fuente / (k+1)) % n);
			estado_nodo_fuente = nro_nodo_fuente % (k+1);
			potencia_nodo_fuente = (*potencias)[fila_nodo_fuente][columna_nodo_fuente];
							
			// Recorro la fila y conecto la casilla con todas las alcanzables de la misma
			for(unsigned int columna_nodo_destino=0; columna_nodo_destino<n; columna_nodo_destino++){
				
				int fila_nodo_destino = fila_nodo_fuente;
				
				// Si corresponde, se unen el nodo_fuente con el nodo_destino
				unirNodos(grafo, nro_nodo_fuente, columna_nodo_fuente, fila_nodo_fuente, potencia_nodo_fuente, estado_nodo_fuente, columna_nodo_destino, fila_nodo_destino, true, n, k);

			}
			// Recorro la columna y conecto la casilla con todas las alcanzables de la misma
			for(unsigned int fila_nodo_destino=0; fila_nodo_destino<n; fila_nodo_destino++){
				
				int columna_nodo_destino = columna_nodo_fuente;
				
				// Si corresponde, se unen el nodo_fuente con el nodo_destino
				unirNodos(grafo, nro_nodo_fuente, columna_nodo_fuente, fila_nodo_fuente, potencia_nodo_fuente, estado_nodo_fuente, columna_nodo_destino, fila_nodo_destino, false, n, k);
				
			}
		}
		
		//grafo->print();

		int nro_nodo_inicio = getNumeroNodo(n, k, fo-1, co-1, 0);
		int nro_nodo_fin = getNumeroNodo(n, k, fd-1, cd-1, 0);
		int k_ultimo_estado = 0;
		int k_usado = 0;
		
		list<int> camino = grafo->bfs(nro_nodo_inicio, nro_nodo_fin, nro_nodo_fin+k);
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
			
			cout << fila_nodo_actual+1 << " " << columna_nodo_actual+1 << " " << k_usado << endl;
		}
		
		
		delete grafo;
		delete potencias;
		
}



