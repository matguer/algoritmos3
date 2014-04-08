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

bool backtrack(Tablero & tablero, DiccionarioFichas & fichas_ordenadas, Tablero & mejor_tablero) {
	
	list<Ficha> * fichas_posibles;
	
	if(tablero.reject(mejor_tablero, fichas_ordenadas)){ return false; }
	
	/*
	if(tablero.accept(mejor_tablero)){ 
		return true; 
	}
	*/
	
	// Voy guardando el mejor tablero
	if(tablero.getPosicionesOcupadas() > mejor_tablero.getPosicionesOcupadas()){
		mejor_tablero = tablero;
	}
		
	// Solo recorro las fichas que pueden ir en ese lugar, osea, las que coinciden el color superior e izquierdo con la ficha de arriba y la de atras
	// Si es la 1ra posicion o no tengo fichas arriba o atras, puedo poner todas
	pair<Color, Color> restriccion = tablero.restriccionFicha(tablero.getPosicionLibre());
	fichas_posibles = fichas_ordenadas.dameFichas(restriccion);
	
	cout << "Fichas posibles:";
	fichas_ordenadas.imprimirListaFichas(*fichas_posibles);
	
	// Recorro las fichas que vale la pena ubicar
	for(list<Ficha>::iterator f = fichas_posibles->begin(); f != fichas_posibles->end(); f++){

		// Para cada ficha restante, llamo un backtracking con el tablero
		// y agrego la proxima ficha al nuevo tablero
		Tablero * tablero_con_una = new Tablero(tablero);
		tablero_con_una->agregarFicha(*f);

		// Le paso al proximo bt las fichas sin la que puse para no repetir
		fichas_ordenadas.sacarFicha(*f);		
		//fichas_ordenadas.imprimirDiccionarioFichas();

		tablero_con_una->print();
		
		// Limpio las fichas temporales
		delete fichas_posibles;
			
		return backtrack(*tablero_con_una, fichas_ordenadas, mejor_tablero);
	}
	
	// Limpio las fichas temporales
	delete fichas_posibles;
	
	// Siempre considero el caso de no agregar ficha
	Tablero * tablero_con_una = new Tablero(tablero);
	Ficha fvacia = Ficha();
	tablero_con_una->agregarFicha(fvacia);
		
	return backtrack(*tablero_con_una, fichas_ordenadas, mejor_tablero);

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
	DiccionarioFichas * fichas_ordenadas = new DiccionarioFichas(*fichas_iniciales);

	if(backtrack(*tablero_inicial, *fichas_ordenadas, mejor_tablero)){
		cout << endl << "Mejor tablero" << endl;
		mejor_tablero.print();
	}


}

