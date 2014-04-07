#include "Ficha.h"
#include "Tablero.h"
#include "DiccionarioFichas.h"
#include <vector>
#include <map>
#include <list>
#include <iostream>
#include <stdlib.h>

using namespace std;

enum Estado {MEJOR_SOLUCION, SOLUCION_VIABLE, SOLUCION_INVIABLE, FINAL_TABLERO}; 

list<Ficha> * parseInput(int cant_fichas);
bool backtrack(Tablero & tablero, list<Ficha> & fichas, DiccionarioFichas & fichas_ordenadas, Tablero & mejor_tablero);

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


bool backtrack(Tablero & tablero, list<Ficha> & fichas, DiccionarioFichas & fichas_ordenadas, Tablero & mejor_tablero) {

	if(tablero.reject()){ return false; }
	
	if(tablero.accept(mejor_tablero)){ 
		return true; 
	}

	for(list<Ficha>::iterator f = fichas.begin(); f != fichas.end(); f++){
			
		// Para cada ficha restante, llamo un backtracking con el tablero
		// y agrego la proxima ficha al nuevo tablero
		Tablero * tablero_con_una = new Tablero(tablero);
		tablero_con_una->agregarFicha(*f);
		//tablero_con_una->print();
		// Le paso al proximo bt las fichas sin la que puse para no repetir
		list<Ficha> * fichas_sin_una = new list<Ficha>(fichas); // O(fichas)
		fichas_sin_una->remove(*f); // O(fichas)
		
		//tablero_con_una->print();
			
		return backtrack(*tablero_con_una, *fichas_sin_una, fichas_ordenadas, mejor_tablero);
	}
	
	// Siempre considero el caso de no agregar ficha
	Tablero * tablero_con_una = new Tablero(tablero);
	Ficha fvacia = Ficha();
	tablero_con_una->agregarFicha(fvacia);
	list<Ficha> * fichas_sin_una = new list<Ficha>(fichas);
		
	return backtrack(*tablero_con_una, *fichas_sin_una, fichas_ordenadas, mejor_tablero);
	
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
	Tablero mejor_tablero = Tablero(alto, ancho);
	
	// Datos para la 1er llamada
	Tablero * tablero_inicial = new Tablero(alto, ancho);
	list<Ficha> * fichas_iniciales = parseInput(cant_fichas);
	DiccionarioFichas * fichas_iniciales_ordenadas = new DiccionarioFichas(*fichas_iniciales);

	if(backtrack(*tablero_inicial, *fichas_iniciales, *fichas_iniciales_ordenadas, mejor_tablero)){
		cout << endl << "Mejor tablero" << endl;
		mejor_tablero.print();
	}

}

