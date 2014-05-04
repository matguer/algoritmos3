#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <vector>
#include "directed_graph.h"

using namespace std;

void printTabla(vector< vector<int> > * tabla, int n){
	for(int i = 0; i<n; i++){
		for(int j = 0; j<n; j++){
			cout << (*tabla)[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}

int main(){
		
		// Leo la entrada
		int n;
		int fo;
		int co;
		int fd;
		int cd;
		int k;

		cin >> n;
		cin >> fo;
		cin >> co;
		cin >> fd;
		cin >> cd;
		cin >> k;
		
		int cant_nodos = n*n*(k+1);
		
		vector< vector<int> > * potencias = new vector<vector<int> >(n, vector<int>(n, 0));

		for(int i = 0; i<n; i++){
			for(int j = 0; j<n; j++){
				cin >> (*potencias)[i][j];
			}
		}
		
		//printTabla(potencias, n);
		directed_graph * grafo = new directed_graph(cant_nodos);
		
		int fila;
		int columna;
		int estado;
		int potencia;
		int nro_proximo_nodo;
		
		// Asigno las posibles aristas, i = nodo que representa la casilla en el estado que no se gasto ningun k
		for(int i = 0; i<cant_nodos; i++){
			
			// Datos de la casilla
			fila = (i / (k+1)) / n;
			columna = ((i / (k+1)) % n);
			estado = i % (k+1);
			potencia = (*potencias)[fila][columna];
			
			//cout << i << ": f " << fila << " c " << columna << " e " << estado << " p " << potencia << endl;
			
			// Conecto la casilla con todas las alcanzables de la fila
			for(int j=0; j<=n; j++){
				/*
				fila_proximo_nodo = (j / (k+1)) / n;
				
				if(potencia <= abs(columna-)){
				
				grafo->add_edge(i,i+nro_proximo_nodo);
				
				}
				*/ 
				
			}

			
			
		}
		
		grafo->print();
		
		delete grafo;
		delete potencias;
		
}



