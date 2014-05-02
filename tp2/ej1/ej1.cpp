#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <sstream>

using namespace std;

int sumatoria(int * cartas, int inicio, int fin);
void printCartas(int * cartas, int cant);
void printTabla(vector< vector<int> > * tabla, int cant);

int main(){
		
		// Leo la entrada
		int cant_cartas;

		cin >> cant_cartas;
		
		int * cartas = new int[cant_cartas];
		vector< vector<int> > * tabla_resultados = new vector<vector<int> >(cant_cartas, vector<int>(cant_cartas, 0));
		// El par representa en first: 0 si agarre del lado izquierdo, 1 si agarre del lado derecho, y el second: cantidad de cartas agarradas
		vector< vector<pair<int,int> > > * tabla_elecciones = new vector<vector<pair<int,int> > >(cant_cartas, vector<pair<int,int> >(cant_cartas, pair<int,int>(0,0)));

		for(int i = 0; i<cant_cartas; i++){
			cin >> cartas[i];
		}
		
		
		// Lleno la tabla con los resultados posibles
		int cartas_inicio = 0;
		int maxval = 0;
		
		for(int i = cant_cartas-1; i>=0; i--){
			
			for(int j = 0; j<cant_cartas; j++){
				
				if(i<=j){
					
					int q = (int) -INFINITY;

					if(i==j){
						// Casos base, la mejor opcion es la unica carta que hay
						cartas_inicio = i;
						q = cartas[j];
						(*tabla_elecciones)[i][j] = pair<int,int>(0,1);
					}else{
						
						// Agarrar todas las cartas
						maxval = max(q,sumatoria(cartas, cartas_inicio, j));
						// Actualizo la mejor jugada encontrada hasta el momento
						if(maxval>q){
							(*tabla_elecciones)[i][j] = pair<int,int>(0,j-cartas_inicio+1);
						}
						q = maxval;
						
						// Agarrar desde la izquierda y restarle la jugada optima del rival
						for(int k=cartas_inicio; k < j; k++){
							maxval = max(q, sumatoria(cartas, cartas_inicio, k) - (*tabla_resultados)[k+1][j]);
							// Actualizo la mejor jugada encontrada hasta el momento
							if(maxval>q){
								(*tabla_elecciones)[i][j] = pair<int,int>(0,k-cartas_inicio+1);
							}
							q = maxval;
						}
						
						// Agarrar desde la derecha y restarle la jugada optima del rival
						for(int k=j; k > cartas_inicio; k--){
							maxval = max(q, sumatoria(cartas, k, j) - (*tabla_resultados)[cartas_inicio][k-1]);
							// Actualizo la mejor jugada encontrada hasta el momento
							if(maxval>q){
								(*tabla_elecciones)[i][j] = pair<int,int>(1,k-cartas_inicio+1);
							}
							q = maxval;
							
						}

					}

					
					// q = Max(sumatoria(cartas_{0,0}) - tabla_resultados_{1,n} , ... , sumatoria(cartas_{0,n}))
					(*tabla_resultados)[i][j] = q;
					
				}
				
			}
			
		}
		
		int nro_turno = 0;
		// Indices para sumar los puntos
		int primera_carta = 0;
		int media_carta = 0;
		int ultima_carta = cant_cartas-1;
		int cartas_tomadas = 0;
		//int cant_cartas_originales = cant_cartas;
		int * puntajes = new int[2];
		int puntos = 0;
		ostringstream output_jugadas;
		//Puntajes jugadores
		puntajes[0] = 0;
		puntajes[1] = 0;
		
		while(cant_cartas>0){

			if((*tabla_elecciones)[primera_carta][ultima_carta].first == 0){
				output_jugadas << "izq ";
			}else{
				output_jugadas << "der ";
			}
			cartas_tomadas = (*tabla_elecciones)[primera_carta][ultima_carta].second;
			output_jugadas << cartas_tomadas << endl;
			
			// Si tome desde la derecha
			if((*tabla_elecciones)[primera_carta][cant_cartas+primera_carta-1].first == 1){
				media_carta = cant_cartas-cartas_tomadas;
				puntos = sumatoria(cartas, media_carta, ultima_carta);
			}else{
				media_carta = primera_carta+cartas_tomadas-1;
				puntos = sumatoria(cartas, primera_carta, media_carta);
			}

			puntajes[nro_turno%2] = puntajes[nro_turno%2] + puntos;

			// Ajusto indices
			if((*tabla_elecciones)[primera_carta][cant_cartas+primera_carta-1].first == 1){
				ultima_carta = cant_cartas-cartas_tomadas-1;
			}else{
				primera_carta = primera_carta+cartas_tomadas;
			}
			cant_cartas = cant_cartas-cartas_tomadas;
			nro_turno++;

		}
		
		cout << nro_turno << " " << puntajes[0] << " " << puntajes[1] << endl;
		cout << output_jugadas.str();
		
		//printTabla(tabla_resultados, cant_cartas_originales);
	
		
		delete cartas;
		delete tabla_resultados;
		delete puntajes;

		return 0;
}

void printCartas(int * cartas, int cant){
	cout << "[";
	for(int i = 0; i<cant; i++){
		cout << cartas[i] << ",";
	}
	cout << "]";
}

void printTabla(vector< vector<int> > * tabla, int cant){
	for(int i = 0; i<cant; i++){
		for(int j = 0; j<cant; j++){
			cout << (*tabla)[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}

// Calcula la sumatoria de un arreglo hasta la posicion limit
int sumatoria(int * cartas, int inicio, int fin){
	int sum = 0;
	for(int i = inicio; i<=fin; i++){
		sum = sum + cartas[i];
	}
	return sum;
}



