#include "Ficha.h"
#include "Tablero.h"
#include "DiccionarioFichas.h"
#include <vector>
#include <map>
#include <list>
#include <iostream>
#include <stdlib.h>

using namespace std;

list<Ficha> * parseInput(int cant_fichas);
void backtrack(Tablero * tablero, DiccionarioFichas * fichas_ordenadas, Tablero & mejor_tablero);

/* La funcion parseInput debe recibir la cantidad de fichas a generar y 
   debe crear un arreglo de longitud cant_fichas de punteros a Ficha 
   con los valores parseados del stdin
*/
list<Ficha> * parseInput(int cant_fichas) {

	list<Ficha> * fichas = new list<Ficha>();
	for(int i=0; i<(cant_fichas); i++) { 
		Color color[4];
		for(int j=0; j<4; j++) { 
			int aux;
			cin >> aux;
			color[j] = aux;
		}
		Ficha ficha = Ficha(i+1, color[0], color[1], color[2], color[3]);
		fichas->push_back(ficha);
	}
	return fichas;
}



void backtrack(Tablero * tablero, DiccionarioFichas * fichas_ordenadas, Tablero & mejor_tablero) {
	
	list<Ficha> * fichas_posibles;													// O(1)
	
	// Podas
	if(tablero->reject(mejor_tablero)){ 												// O(1)
		return; 														// O(1)
	}
	
	// Si encuentro un tablero completo termino, si es un tablero mejor que el mejor actual lo reemplazo
	if(tablero->accept(mejor_tablero)){												// O(n*m)
		return; 														// O(1)
	}					
	

	if(tablero->getPosicionesRecorridas() < (tablero->getFilas() * tablero->getColumnas())){					// O(1)
				
		// Solo recorro las fichas que pueden ir en ese lugar, osea, las que coinciden el color superior e izquierdo con la ficha de arriba y la de atras
		// Si es la 1ra posicion o no tengo fichas arriba o atras, puedo poner todas
		pair<Color, Color> restriccion = tablero->restriccionFicha(tablero->getPosicionLibre());				// O(1) 


		fichas_posibles = fichas_ordenadas->dameFichas(restriccion);					// O(n * m * #colores * #colores)
		

		// Recorro las fichas que vale la pena ubicar
		for(list<Ficha>::iterator f = fichas_posibles->begin(); f != fichas_posibles->end(); f++){				// O(n*m)

			// Para cada ficha restante, llamo un backtracking con el tablero
			// y agrego la proxima ficha al nuevo tablero
			Tablero* tablero_con_una = new Tablero(*tablero);								// O(n*m)
			tablero_con_una->agregarFicha(*f);										// O(1)

			// Le paso al proximo bt las fichas sin la que puse para no repetir
			DiccionarioFichas * fichas_ordenadas_sin_una = new DiccionarioFichas(*fichas_ordenadas);			// O(n*m)
			fichas_ordenadas_sin_una->sacarFicha(*f);					// O(log (#colores * #colores)) + O(n*m)

			backtrack(tablero_con_una, fichas_ordenadas_sin_una, mejor_tablero);						

			delete tablero_con_una;												// O(1)
			delete fichas_ordenadas_sin_una;										// O(1)
		}
		
		// Limpio las fichas temporales
		delete fichas_posibles;													// O(1)
		
		// Siempre considero el caso de no agregar ficha
		Tablero* tablero_con_vacia = new Tablero(*tablero);									// O(n*m)
		Ficha fvacia = Ficha();													// O(1)
		tablero_con_vacia->agregarFicha(fvacia);										// O(1)
			
		backtrack(tablero_con_vacia, fichas_ordenadas, mejor_tablero);
		
		delete tablero_con_vacia;												// O(1)
	
	}
	
}

/* ************************************************************************* */
/* ********************************* MAIN ********************************** */
/* ************************************************************************* */

int main(int argc, char* argv[]) {

	int alto, ancho, cant_fichas, cant_colores;

	cin >> alto;
	cin >> ancho;
	cin >> cant_colores;
	
	cant_fichas = alto * ancho;
	
	list<Ficha> * fichas_iniciales = parseInput(cant_fichas);
	
	Tablero mejor_tablero = Tablero(alto, ancho);
	// Genero un mejor tablero con todas las posiciones alternadas completas, siempre se puede armar ese tablero.
	/* Ej:
	 * 	1 0 2 
		0 3 0 
		4 0 5
	*/
	mejor_tablero.llenarTableroConDiagonales(*fichas_iniciales); 
	// Datos para la 1er llamada
	Tablero * tablero_inicial = new Tablero(alto, ancho);
	DiccionarioFichas * fichas_ordenadas = new DiccionarioFichas(*fichas_iniciales, cant_colores);

	backtrack(tablero_inicial, fichas_ordenadas, mejor_tablero);
	
	mejor_tablero.print();
	
	delete tablero_inicial;
	delete fichas_ordenadas;
	delete fichas_iniciales;
	

}

