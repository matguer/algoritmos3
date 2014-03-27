#include "ej1.h"

using namespace std;

/**

 */
intervalo resolver(LCamiones& c, int periodo, int totalCamiones){
	
	int inicio = 1;
	int maxInspec = 0;
	intervalo resultado = intervalo();

	// Ordeno la lista de camiones en O(n*log(n))
	// http://www.cplusplus.com/reference/list/list/sort/
	c.sort();

	int ultimoDia;
	int inspecTemp = 0;
	// Recorro los dias en que pasan camiones
	for(LCamiones::const_iterator iter = c.begin(); iter != c.end(); iter++){
		// Seteo cual seria el ultimo dia de contratacion
		ultimoDia = *iter + periodo - 1;
		// Me paro en cada dia y me fijo cuantos camiones agarraria si contrato al inspector ese dia
		for (LCamiones::const_iterator iterInterno = iter; (iterInterno != c.end() && *iterInterno <= ultimoDia); iterInterno++){
			inspecTemp++;
		}

		// Si encontre un inicio mejor(o igual) reemplazo el anterior
		if(inspecTemp >= maxInspec){
			maxInspec = inspecTemp;
			inicio = *iter;
		}
		inspecTemp = 0;
	}

	resultado.first = inicio;
	resultado.second = maxInspec;
	
	return resultado;
}


/**
 * Muestra la lista del resultado
 */
void mostrarResultado(intervalo i){
	
	cout << i.first << " " << i.second << endl;
	
}
