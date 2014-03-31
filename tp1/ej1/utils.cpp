#include "ej1.h"

using namespace std;

/* 
 *
 */
intervalo resolver(LCamiones& c, int periodo){
	
	int inicio = 1;
	int maxInspec = 0;
	intervalo resultado = intervalo();

	// Ordeno la lista de camiones en O(n*log(n))
	// http://www.cplusplus.com/reference/list/list/sort/
	sort(c.begin(), c.end());

	int ultimoCamion;
	int inspecTemp = 0;
	int cantCamiones = int(c.size());
	int finContrato;

	// Recorro los dias en que pasan camiones
	for(int i=0;i<cantCamiones;i++){
		
		// Primer dia fuera del rango
		finContrato = c.at(i) + periodo - 1;
		ultimoCamion = primeroMayor(c, finContrato, 0, cantCamiones-1, cantCamiones-1);
		inspecTemp = ultimoCamion - i;

		// Si encontre un inicio mejor(o igual) reemplazo el anterior
		if(inspecTemp >= maxInspec){
			maxInspec = inspecTemp;
			inicio = i;
		}
		inspecTemp = 0;
	}

	resultado.first = c.at(inicio);
	resultado.second = maxInspec;
	
	return resultado;
}

/* Devuelve el indice del primer elemento mayor a elem
 *
*/
int primeroMayor(LCamiones& c, int elem, int p, int f, int ultimoEncontrado){
	
	if((f-p) <= 1){
		if(c.at(p) > elem){
			return f;
		}else{
			return ultimoEncontrado;
		}
	}else{
		int medio = p + (f-p)/2;
		if(c.at(medio) <= elem){
			return primeroMayor(c, elem, medio, f, ultimoEncontrado);
		}else{
			return primeroMayor(c, elem, p, medio, medio);
		}
	}
}

/**
 * Muestra la lista del resultado
 */
void mostrarResultado(intervalo i){
	
	cout << i.first << " " << i.second << endl;
	
}
