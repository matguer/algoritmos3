#include "Ficha.h"
#include "Tablero.h"
#include <vector>
#include <map>
#include <list>
#include <iostream>

using namespace std;

enum Estado {MEJOR_SOLUCION, SOLUCION_VIABLE, SOLUCION_INVIABLE, FINAL_TABLERO}; 
typedef map< pair<Color, Color>, list<Ficha> > Diccionario;


Ficha** parseInput(int cant_fichas);
void generarMejorSolucionDefault(Ficha** fichas);
pair<Color,Color> getColoresAdyacentes(Tablero tablero, Coord coord);
void imprimirLista(list<Ficha> valor);
void imprimirDiccionario(Diccionario dic);
void resolver(Tablero tablero, Diccionario* dic);
bool backtrack(Tablero tablero, Diccionario dic, Coord coord);
Estado check(Tablero& tablero, Coord coord);


Tablero t_mejor_solucion;
int cant_colores;


/* La funcion parseInput debe recibir la cantidad de fichas a generar y 
   debe crear un arreglo de longitud cant_fichas de punteros a Ficha 
   con los valores parseados del stdin
*/
Ficha** parseInput(int cant_fichas) {

	Ficha** fichas = new Ficha*[cant_fichas];
	for(int i=0; i<(cant_fichas); i++) { 
		Color color[4];
		for(int j=0; j<4; j++) { 
			int aux;
			cin >> aux;
			color[j] = aux;
		}
		Ficha* ficha = new Ficha(i+1, color[0], color[1], color[2], color[3]);
		fichas[i] = ficha;
	}
	return fichas;
}


/* La funcion generarMejorSolucionDefault debe generar una primera mejor solucion
   contra la que se iran comparando el resto hasta ser reemplazada por una mejor.
   En este caso la solucion default es intercalar fichas entre las filas y columnas
   de manera tal que ninguna tenga fichas adyacentes
*/
void generarMejorSolucionDefault(Ficha** fichas) {
	int i_fichas = 0;
	for(int i=0; i<t_mejor_solucion.getFilas(); i++) {
		for(int j=0; j<t_mejor_solucion.getColumnas(); j++) {
			if((i%2 == 0) && (j%2 == 0)) t_mejor_solucion.agregarFicha(Coord(i,j), *(fichas[i_fichas])), i_fichas++;
			if((i%2 != 0) && (j%2 != 0)) t_mejor_solucion.agregarFicha(Coord(i,j), *(fichas[i_fichas])), i_fichas++;
		}
	}
}


/* La funcion getColoresAdyacentes debe recibir un tablero y una coordenada en el mismo
   y retornar el par de colores que indican los colores de la ficha de arriba e izquierda
   respectivamente
*/
pair<Color,Color> getColoresAdyacentes(Tablero tablero, Coord coord) {

	/* Esta en la esquina superior izquierda, no hay colores adyacentes */
	if(coord.first == 0 && coord.second == 0) return pair<Color,Color>(NO_COLOR,NO_COLOR);

	/* Esta en la primera fila, no hay color arriba pero si a la izquierda */
	if(coord.first == 0) {
		Ficha izquierda = tablero.getFicha(Coord(coord.first, coord.second - 1));
		return pair<Color,Color>(NO_COLOR, izquierda.getLado(DERECHA));
	}

	/* Esta en la primera columna, no hay color a la izquierda pero si arriba*/
	Ficha superior = tablero.getFicha(Coord(coord.first - 1, coord.second));

	if(coord.second == 0) {
		return pair<Color,Color>(superior.getLado(INFERIOR), NO_COLOR);
	}

	Ficha izquierda = tablero.getFicha(Coord(coord.first, coord.second - 1));

	/* Esta por el medio del tablero, hay color arriba y a la izquierda*/
	return pair<Color,Color>(superior.getLado(INFERIOR), izquierda.getLado(DERECHA));
}


/* La funcion auxiliar imprimirLista debe imprimir el listado de fichas pasado por parametro */
void imprimirLista(list<Ficha> valor) {
	list<Ficha>::iterator it_valor;
	for(it_valor = valor.begin(); it_valor != valor.end(); ++it_valor) {
		(*it_valor).print();
		cout << " - ";
	}
	cout << endl;
}

/* La funcion auxiliar imprimirDiccionario debe imprimir el diccionario pasado por parametro */
void imprimirDiccionario(Diccionario dic) {

	cout << endl << "DICCIONARIO" << endl;

	Diccionario::iterator it_clave;
	for(it_clave = dic.begin(); it_clave != dic.end(); ++it_clave) {
		list<Ficha> valor = (*it_clave).second;
		imprimirLista(valor);
		cout << endl;
	}

}


/* La funcion resolver debe recibir un tablero y un diccionario de fichas, recorrer el mismo
   y para cada ficha del diccionario colocarla en la primera posicion y llamar a la funcion
   backtrack.
   VER SI SE PUEDE SACAR ESTA FUNCION Y HACERLO TODO EN EL BACKTRACK
*/
void resolver(Tablero tablero, Diccionario* dic) {

	bool mejor_solucion = false;
	
	Diccionario::iterator it_dic;
	Coord coord(0,0);

	for(it_dic = dic->begin(); it_dic != dic->end(); ++it_dic) {
		list<Ficha> lista = (*it_dic).second;
		pair<Color,Color> clave = (*it_dic).first;
		unsigned int size = lista.size();
		for(unsigned int i=0; i<size; i++) {
			Ficha ficha = lista.back();
			lista.pop_back();
			(*dic)[clave] = lista;
			tablero.agregarFicha(coord,ficha);
			if ((mejor_solucion = backtrack(tablero, *dic, coord))) break;
			tablero.quitarFicha(coord);
			lista.push_front(ficha);
			dic->erase(clave);
			(*dic)[clave] = lista;
		}
		if(mejor_solucion) break;
	}
}


/* La funcion bactrack debe recibir un tablero, un diccionario de fichas y una coordenada del tablero
   que indique la ultima posicion utilizada y, con esos datos, debera chequear el estado del tablero y
   en caso de ser necesario colocar una nueva ficha y volver a llamarse para continuar con el proceso
   de generacion de la mejor solucion.
*/
bool backtrack(Tablero tablero, Diccionario dic, Coord coord) {

	cout << "TABLERO MEJOR PARCIAL AL VOLVER AL BACKTRACK: " << t_mejor_solucion.getCantidadFichas() << endl;
	Estado estado = check(tablero, coord);
	cout << "TABLERO MEJOR PARCIAL AL VOLVER AL BACKTRACK: " << t_mejor_solucion.getCantidadFichas() << endl;
	t_mejor_solucion.print();

	if(estado == MEJOR_SOLUCION) {
		return true;
	}

	if(estado == SOLUCION_INVIABLE || estado == FINAL_TABLERO) {
		return false;
	}


	else {
		coord = tablero.siguientePosicion(coord);	
		pair<Color,Color> clave = getColoresAdyacentes(tablero, coord);

		/*  
		  CORROBORAR SI SUPERIOR E IZQUIERDA ES NO_COLOR Y RECORRER TODAS LAS COMBINACIONES
		  DEL DIC QUE TENGAN SUPERIOR O IZQUIERDA EL QUE ES NO_COLOR.
		*/
		list<pair<Color, Color> > claves = list<pair<Color,Color> >();

		if(clave.first == NO_COLOR && clave.second == NO_COLOR) {
			for(int i=1; i<=cant_colores; i++) {
				for(int j=1; j<=cant_colores; j++) {
					pair<Color,Color> clave_actual = pair<Color,Color>(i,j);
					claves.push_back(clave_actual);
				}
			}
		} else if(clave.first == NO_COLOR) {
			for(int i=1; i<=cant_colores; i++) {
				pair<Color,Color> clave_actual = pair<Color,Color>(i,clave.second);
				claves.push_back(clave_actual);
			}
		} else if(clave.second == NO_COLOR) {
			for(int i=1; i<=cant_colores; i++) {
				pair<Color,Color> clave_actual = pair<Color,Color>(clave.first,i);
				claves.push_back(clave_actual);
			}
		} else if(clave.first != NO_COLOR && clave.second != NO_COLOR) claves.push_back(clave);



		unsigned int cant_claves = claves.size();	
		for(unsigned int i=0; i<cant_claves; i++) {
			
			pair<Color,Color> clave_actual = claves.back();
			claves.pop_back();
			
			Diccionario::iterator it_fichas_potables = dic.find(clave_actual);
			if(it_fichas_potables != dic.end()) {
				list<Ficha> fichas_potables = it_fichas_potables->second;
				unsigned int size = fichas_potables.size();
				for(unsigned int i=0; i<size; i++) {
					Ficha ficha = fichas_potables.back();
					fichas_potables.pop_back();
					dic[clave_actual] = fichas_potables;
					tablero.agregarFicha(coord,ficha);
					if (backtrack(tablero, dic, coord)) return true;
					tablero.quitarFicha(coord);
					fichas_potables.push_front(ficha);
					dic.erase(clave_actual);
					dic[clave_actual] = fichas_potables;
				}
			}
		}
		if (backtrack(tablero, dic, coord)) return true;
		return false;
	
	}

}


/* La funcion check debe recibir un tablero y una coordenada indicando la ultima posicion utilizada
   y con esos datos debe decidir si el tablero es una solucion, es viable a encontrar una solucion o
   no.
*/
Estado check(Tablero& tablero, Coord coord) {

	/* Si el tablero esta completo encontre una solucion inmejorable */
	if(tablero.completo()) {
		cout << "entro por mejor" << endl;
		t_mejor_solucion = tablero;
		return MEJOR_SOLUCION;
	}

	/* Si llegue al final del tablero y tengo menos fichas puestas que la mejor solucion */
	if((coord.first == tablero.getFilas() - 1)
		&& (coord.second == tablero.getColumnas() - 1)
		&& (tablero.getCantidadFichas() <= t_mejor_solucion.getCantidadFichas())) {
		return SOLUCION_INVIABLE;	
	}

	/* ESTE LINEA NO ME ESTA GUARDANDO EL TABLERO BIEN, CREO QUE ES PORQUE LE FALTA ESE TIPO DE CONSTRUCTOR A LA CLASE TABLERO */
	if(tablero.getCantidadFichas() > t_mejor_solucion.getCantidadFichas()) { 
		//cout << "TABLERO MEJOR PARCIAL: " << endl;
		//tablero.print();
		t_mejor_solucion = tablero;
		//cout << "TABLERO MEJOR PARCIAL POST ASIGNACION: " << endl;
		//t_mejor_solucion.print();
	}
	
	
	/* IMPLEMENTAR ACA LA PODA QUE CHEQUE SI AUN COMPLETANDO LA FILA DE ABAJO Y LAS RESTANTES NO LLEGA A LA MEJOR.
	
	   PENSE QUE TAMBIEN SE PODRIA HACER ALGO SIMILAR CON LAS COLUMNAS, ES DECIR QUE POR CADA FICHA QUE PONGO CHEQUEO
	   CUANTAS COLUMNAS MAS PUEDO LLENAR EN LA FILA MAS LAS DEMAS FILAS Y VER SI ES VIABLE O NO. COMO QUE EN REALIDAD
	   SIGUE SIENDO MAS DE LA ANTERIOR PERO LE AGREGARIAMOS UN POQUITITO MAS.	
	*/

	if(tablero.posicionesRecorridas(coord) == (tablero.getFilas() * tablero.getColumnas())) return FINAL_TABLERO;

	return SOLUCION_VIABLE;
}



/* ************************************************************************* */
/* ********************************* MAIN ********************************** */
/* ************************************************************************* */

int main(int argc, char* argv[]) {

	int alto, ancho, cant_fichas;

	cin >> alto;
	cin >> ancho;
	cin >> cant_colores;
	
	/* Generacion de fichas leyendo la entrada */
	cant_fichas = alto * ancho;
	Ficha** fichas = parseInput(cant_fichas);

	/* Carga de fichas en el diccionario */
	Diccionario* dic = new Diccionario();
	Diccionario::iterator it_dic;
	for(int i=0; i<cant_fichas; i++) {
		pair<Color,Color> clave(fichas[i]->getLado(SUPERIOR),fichas[i]->getLado(IZQUIERDA));
		list<Ficha> lista;
		it_dic = dic->find(clave);
		if(it_dic != dic->end()) lista = it_dic->second;
		lista.push_back(*fichas[i]);
		(*dic)[clave] = lista; 
	}

	/* Generacion de la mejor solucion default */
	t_mejor_solucion = Tablero(alto, ancho);
	generarMejorSolucionDefault(fichas);
	//cout << "MEJOR SOLUCION: " << t_mejor_solucion->getCantidadFichas() << endl;
	//t_mejor_solucion->print();

	Tablero tablero(alto, ancho);

	resolver(tablero, dic);

	cout << "MEJOR SOLUCION: " << t_mejor_solucion.getCantidadFichas() << endl;
	t_mejor_solucion.print();
}

