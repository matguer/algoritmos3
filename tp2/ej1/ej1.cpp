#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <cmath>

using namespace std;

int resolver(int * cartas, int cant_cartas, int & cant_agarro, int & mejor_diferencia);
int sumatoria(int * cartas, int cant);
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
		int puntos_izq = 0;
		int puntos_der = 0;
		int diferencia_izq = 0;
		int diferencia_der = 0;
		
		// Caso tomando desde la izquierda
		for(int i = 1; i<=cant_cartas; i++){
			
			if(i==cant_cartas){
				
				puntos_izq = sumatoria(cartas, cant_cartas);
				// Voy modificando la cantidad de cartas que me conviene tomar
				q = max(puntos_izq,q);
				
			}else{
				
				// Tomo las cartas 0..i
				int * sub_cartas_izq = cartas;
				int sub_cantidad_izq = i;
				int * sub_cartas_der = cartas + i;
				int sub_cantidad_der = cant_cartas-i;
				
				/*
				cout << "Todas las cartas ";
				printCartas(cartas, cant_cartas);
				cout << endl;
				
				cout << "Cartas desde la izq ";
				printCartas(sub_cartas_izq, sub_cantidad_izq);
				cout << endl;
				
				cout << "Cartas desde la der ";
				printCartas(sub_cartas_der, sub_cantidad_der);
				cout << endl;
				*/
				
				// Puntos acumulados en este posible paso
				puntos_izq = sumatoria(sub_cartas_izq, sub_cantidad_izq);
				puntos_der = sumatoria(sub_cartas_der, sub_cantidad_der);
				
				/*
				cout << "Puntos izq " << puntos_izq << endl;
				cout << "Puntos der " << puntos_der << endl;
				*/
				
				// Subarreglo (subproblema) de cartas optima que tomaria el rival
				diferencia_izq = puntos_izq - resolver(sub_cartas_der, sub_cantidad_der, cant_agarro, mejor_diferencia);
				diferencia_der = puntos_der - resolver(sub_cartas_izq, sub_cantidad_izq, cant_agarro, mejor_diferencia);
				
				/*
				cout << "Dif izq " << diferencia_izq << endl;
				cout << "Dif der " << diferencia_der << endl << endl;
				*/
				
				q = max(diferencia_izq,q);	
				q = max(diferencia_der,q);
				
			}

		}
		
	
		
		// Max(cartas[0] - resolver(cartas[1..n]) , ... , cartas[i..j-1] - resolver(cartas[j..n-1]))
		return q;
	}
	
}

void printCartas(int * cartas, int cant){
	cout << "[";
	for(int i = 0; i<cant; i++){
		cout << cartas[i] << ",";
	}
	cout << "]";
}

// Calcula la sumatoria de un arreglo hasta la posicion limit
int sumatoria(int * cartas, int cant){
	int sum = 0;
	for(int i = 0; i<cant; i++){
		sum = sum + cartas[i];
	}
	return sum;
}



