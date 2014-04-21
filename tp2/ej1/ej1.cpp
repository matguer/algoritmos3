#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <cmath>

using namespace std;

int resolver(int * cartas, int cant_cartas, int & cant_agarro, int & mejor_diferencia);
int sumatoria(int * cartas, int init, int limit);
void printCartas(int * cartas, int cant);

/**
 * La función main toma el listado de instancias por std input:
 */
int main(){
		
		
		int cant_cartas;

		cin >> cant_cartas;
		
		int * cartas = new int[cant_cartas];

		for(int i = 0; i<cant_cartas; i++){
			cin >> cartas[i];
		}
		
		int cant_agarro = 0;
		int mejor_diferencia = 0;
		
		cout << "Mejor diferencia: " << resolver(cartas, cant_cartas, cant_agarro, mejor_diferencia) << endl;
		cout << "Agarrando " << cant_agarro << " cartas" << endl;
		cout << "Mejor diferencia v2: " << mejor_diferencia << endl;

		delete cartas;

		return 0;
}

// Dado un arreglo de cartas, devuelve la posicion de la carta optima

int resolver(int * cartas, int cant_cartas, int & cant_agarro, int & mejor_diferencia){
	
	// Caso base de una sola carta, no queda otra opcion
	if(cant_cartas==1){
		return cartas[0];
	// Caso recursivo, calculo el maximo de agarrar
	}else{
		
		int q = (int) -INFINITY;
		int puntos = 0;
		int diferencia = 0;
		
		// Caso tomando desde la izquierda
		for(int i = 1; i<=cant_cartas; i++){
			
			if(i==cant_cartas){
				
				puntos = sumatoria(cartas, 0, cant_cartas-1);
				// Voy modificando la cantidad de cartas que me conviene tomar
				if(puntos>mejor_diferencia){
					cant_agarro = cant_cartas;
					mejor_diferencia = puntos;
				}
				q = max(puntos,q);
				
			}else{

				// Puntos acumulados en este posible paso
				puntos = sumatoria(cartas, 0, i-1);
				
				// Subarreglo (subproblema) de cartas optima que tomaria el rival
				int * sub_cartas = cartas + i;
				diferencia = puntos - resolver(sub_cartas, cant_cartas-i, cant_agarro, mejor_diferencia);
				
				// Voy modificando la cantidad de cartas que me conviene tomar
				if(diferencia>mejor_diferencia){
					cant_agarro = i;
					mejor_diferencia = diferencia;
				}
				q = max(diferencia,q);
				
			}

		}
		
		
		// Caso tomando desde la derecha
		for(int i = cant_cartas; i>0; i--){
			
			if(i==cant_cartas){
				
				puntos = sumatoria(cartas, 0, cant_cartas-1);
				// Voy modificando la cantidad de cartas que me conviene tomar
				if(puntos>mejor_diferencia){
					cant_agarro = i;
					mejor_diferencia = puntos;
				}
				q = max(puntos,q);
				
				cout << puntos << endl;
				
			}else{
				
				printCartas(cartas, cant_cartas-1);
				cout << endl;

				// Puntos acumulados en este posible paso
				puntos = sumatoria(cartas, i, cant_cartas-1);
				
				cout << "agarro de " << i << " a " << cant_cartas-1 << " " << puntos << endl;
								
				// Subarreglo (subproblema) de cartas optima que tomaria el rival
				cout << "subarreglo " << 0 << " a " << i << endl;
				int * sub_cartas = cartas;
				diferencia = puntos - resolver(sub_cartas, i, cant_agarro, mejor_diferencia);
				
				
				// Voy modificando la cantidad de cartas que me conviene tomar
				if(diferencia>mejor_diferencia){
					cant_agarro = cant_cartas-i;
					mejor_diferencia = diferencia;
				}
				q = max(diferencia,q);
			}
			
		}
		
		
		// Max(cartas[0] - resolver(cartas[1..n]) , ... , cartas[i..j-1] - resolver(cartas[j..n-1]))
		return q;
	}
	
}

void printCartas(int * cartas, int cant){
	cout << "[";
	for(int i = 0; i<=cant; i++){
		cout << cartas[i] << ",";
	}
	cout << "]";
}

// Calcula la sumatoria de un arreglo hasta la posicion limit
int sumatoria(int * cartas, int init, int limit){
	int sum = 0;
	for(int i = init; i<=limit; i++){
		sum = sum + cartas[i];
	}
	return sum;
}



