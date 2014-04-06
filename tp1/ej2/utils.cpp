#include "ej2.h"

using namespace std;

/**
 * La función devuelve una lista de pair<porcentajePeso,Joya>, 
 * donde porcentajePeso es el % del peso de la joya sobre el total de los pesos, 
 * y Joya los datos originales de input
 */
void resolver(list<Joya>& l){
	
	// Calculo la relacion entre la devaluacion diaria y el tiempo de cada joya : O(n)
	int i = 1;
	for(list<Joya>::iterator joya = l.begin(); joya != l.end(); joya++){
		
		joya->porcentaje_peso = ((PorcentajePeso) joya->devaluacion_diaria) / ((PorcentajePeso) joya->tiempo_fabricacion);
		joya->identificador = i; // La posicion en la lista original
		
		i++;
	}
	
	// Ordeno la lista de resultados segun el % de peso de mayor a menor: : O(n*log(n)) 
	// http://www.cplusplus.com/reference/list/list/sort/
	l.sort(pairCompare);

}

/**
 * Calcula la perdida de dinero para una lista dada
 */
int perdida(const list<Joya> &l){
	
	int dias_transcurridos = 0;
	int perdida_total = 0;
	
	for(list<Joya>::const_iterator joya = l.begin(); joya != l.end(); joya++){
		dias_transcurridos = dias_transcurridos + joya->tiempo_fabricacion;
		perdida_total = perdida_total + dias_transcurridos * (joya->devaluacion_diaria);
	}
	
	return perdida_total;
}

/**
 * Comparador para sort de list<Joya>
 */
bool pairCompare(const Joya & firstElem, const Joya & secondElem) {
  return firstElem.porcentaje_peso > secondElem.porcentaje_peso;
}

/**
 * Muestra la lista del resultado
 */
void mostrarResultado(list<Joya> &l){
	
	for(list<Joya>::iterator joya = l.begin(); joya != l.end(); joya++){
		cout << joya->identificador << " ";
	}
	
}

/**
 * Comprueba si el valor devuelto por "resolver" es el optimo, comparando con todas las posibles permutaciones
 */
bool esOptimo(list<Joya> &l){
	
	int perdida_minima_permutaciones = 0;
	int perdida_maxima_permutaciones = 0;
	int tmp = 0;
	list<Joya> l2 = l;
	
	list<list<Joya> > permutaciones = permute(l2);
	
	for(list<list<Joya> >::iterator iter = permutaciones.begin(); iter != permutaciones.end(); iter++){
		
		tmp = perdida(*iter);
		
		if(perdida_minima_permutaciones == 0 || perdida_minima_permutaciones > tmp){
			perdida_minima_permutaciones = tmp;
		}
		
		if(perdida_maxima_permutaciones < tmp){
			perdida_maxima_permutaciones = tmp;
		}
		
	}
	
	int perdida_optimo = perdida(l);
	
	cout << "Menor perdida permutaciones: " << perdida_minima_permutaciones << endl;
	cout << "Mayor perdida permutaciones: " << perdida_maxima_permutaciones << endl;
	cout << "Menor perdida algoritmo: " << perdida_optimo << endl;
	
	
	return (perdida_optimo<=perdida_minima_permutaciones);
	
}

/**
 * Permuta la lista de un resultado
 */
list<list<Joya> > permute(list<Joya> & L1){
    if (L1.size() == 1)
        return std::list<list<Joya> >(1,L1);

    std::list<list<Joya> > res;
    for (list<Joya>::iterator i = L1.begin(); i != L1.end();)
    {
        // remember this
        Joya x = (*i);

        // make a list without the current element
        list<Joya> tmp(L1.begin(), i++);
        tmp.insert(tmp.end(), i, L1.end());

        // recurse to get all sub-permutations
        std::list<list<Joya> > sub = permute(tmp);

        // amend sub-permutations by adding the element
        for (std::list<list<Joya> >::iterator j=sub.begin(); j!=sub.end();j++)
            (*j).push_front(x);

        // finally append modified results to our running collection.
        res.insert(res.begin(), sub.begin(), sub.end());
    }
    return res;
}
