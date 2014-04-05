#include "ej1.h"

using namespace std;

/* 
 *
 */
intervalo resolver(LCamiones& c, int periodo){
	
	int inicio = 1;
	int maxInspec = 0;
	intervalo resultado = intervalo();
	//vector<int>::iterator itCamiones;


	// Ordeno la lista de camiones en O(n*log(n))
	// http://www.cplusplus.com/reference/list/list/sort/
	sort(c.begin(), c.end());

	vector<int>::iterator ultimoCamion;
	int inspecTemp = 0;
	int cantCamiones = int(c.size());
	int finContrato;
	int ultimoVisto = 0;
	int index;

	// Recorro los dias en que pasan camiones
	for(int i=0;i<cantCamiones;i++){
		
		// me fijo si el ultimo que verifique no es igual al actual en caso de que hayan repetidos
		if(ultimoVisto != c.at(i)){
			// Primer dia fuera del rango
			finContrato = c.at(i) + periodo - 1;
			cout << "fin contrato: " << finContrato << endl;
			
			// Obtengo el primer camion fuera del rango O(log2(N)+1) donde N es la distancia entre inicio y final
			// http://www.cplusplus.com/reference/algorithm/upper_bound/
			ultimoCamion = upper_bound(c.begin(), c.end(), finContrato);
			cout << "primero fuera de rango: " << *ultimoCamion << endl;
			
			index = ultimoCamion - c.begin();
			inspecTemp = index - i;
			cout << "camiones: " << inspecTemp << endl;

			// Si encontre un inicio mejor(o igual) reemplazo el anterior
			if(inspecTemp >= maxInspec){
				maxInspec = inspecTemp;
				inicio = i;
			}
			inspecTemp = 0;
		}
		ultimoVisto = c.at(i);

	}

	resultado.first = c.at(inicio);
	resultado.second = maxInspec;
	
	return resultado;
}
/**
 * Muestra la lista del resultado
 */
void mostrarResultado(intervalo i){
	
	cout << i.first << " " << i.second << endl;
	
}
