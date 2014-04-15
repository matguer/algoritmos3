#include "ej1.h"

using namespace std;

/* 
 * 
 */
/*Resultado resolver(LCartas& c){
	
	Resultado resultado = Resultado();

	vector<int> izq;
	vector<int> der;

	int cantCartas = c.size();
	int maxIzq = 0;
	int maxDer = 0;

	// Armo dos arreglos, uno de izquierda a derecha y otro al reves
	for(int i=0;i<cantCartas;i++){
		if(i == 0){
			izq[i] = c.at(i);
			der[i] = c.at(cantCartas - i);
		}else{
			izq[i] = c.at(i) + izq[i-1];
			der[i] = c.at(cantCartas - i) + der[i-1];
		}

		if(maxIzq < izq[i]){
			maxIzq = i;
		}
		if(maxDer < der[i]){
			maxDer = i;
		}
	}

	pair<int, int> resultadosJugadores = pair(0,0);
	char[] proximo = "first";
	bool termine = false;

	while(!termine){

	}


}*/