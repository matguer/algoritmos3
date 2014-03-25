#include "ej2.h"

using namespace std;

/**
 * La función devuelve una lista de pair<porcentajePeso,Joya>, 
 * donde porcentajePeso es el % del peso de la joya sobre el total de los pesos, 
 * y Joya los datos originales de input
 */
std::list<pair<PorcentajePeso,pair<NroJoya,Joya> > > resolver(const LJoya& l){
	
	list<pair<PorcentajePeso,pair<NroJoya,Joya> > > r = list<pair<PorcentajePeso,pair<NroJoya,Joya> > >();
	PorcentajePeso sumatoria_pesos = 0.0;
	PorcentajePeso peso;
	
	// Recorro las joyas para calcular el total de pesos : O(n)
	for(LJoya::const_iterator iter = l.begin(); iter != l.end(); iter++){
		// El "peso" de la joya se calcula como D / T
		peso = ((PorcentajePeso) iter->first) / ((PorcentajePeso) iter->second);
		sumatoria_pesos = sumatoria_pesos + peso;
	}
	
	// Ahora armo la lista final con los % de peso sobre el total de cada joya : O(n)
	int i = 1;
	for(LJoya::const_iterator iter = l.begin(); iter != l.end(); iter++){
		pair<PorcentajePeso,pair<NroJoya,Joya> > pairResultado = pair<PorcentajePeso,pair<NroJoya,Joya> >();
		
		peso = ((PorcentajePeso) iter->first) / ((PorcentajePeso) iter->second);
	
		pairResultado.first = ((PorcentajePeso) peso) / ((PorcentajePeso) sumatoria_pesos);
		pairResultado.second.second = *iter;
		pairResultado.second.first = i; // La posicion en la lista original
		
		r.push_back(pairResultado);
		i++;
	}
	
	// Ordeno la lista de resultados segun el % de peso de mayor a menor: : O(n*log(n)) 
	// http://www.cplusplus.com/reference/list/list/sort/
	r.sort(pairCompare);
	
	return r;
}

/**
 * Calcula la perdida de dinero para una lista dada
 */
int perdida(const list<pair<PorcentajePeso,pair<NroJoya,Joya> > > &l){
	
	int dias_transcurridos = 0;
	int perdida_total = 0;
	
	for(list<pair<PorcentajePeso,pair<NroJoya,Joya> > >::const_iterator iter = l.begin(); iter != l.end(); iter++){
		dias_transcurridos = dias_transcurridos + iter->second.second.second;
		perdida_total = perdida_total + dias_transcurridos*iter->second.second.first;
	}
	
	return perdida_total;
}

/**
 * Comparador para sort de list<pair<PorcentajePeso,pair<NroJoya,Joya> > >
 */
bool pairCompare(const std::pair<PorcentajePeso,pair<NroJoya,Joya> > & firstElem, const std::pair<PorcentajePeso,pair<NroJoya,Joya> > & secondElem) {
  return firstElem.first > secondElem.first;
}

/**
 * Muestra la lista del resultado
 */
void mostrarResultado(list<pair<PorcentajePeso,pair<NroJoya,Joya> > > &l){
	
	for(list<pair<PorcentajePeso,pair<NroJoya,Joya> > >::iterator iter = l.begin(); iter != l.end(); iter++){
		cout << iter->second.first << " ";
	}
	
}

/**
 * Comprueba si el valor devuelto por "resolver" es el optimo, comparando con todas las posibles permutaciones
 */
bool esOptimo(list<pair<PorcentajePeso,pair<NroJoya,Joya> > > &l){
	
	int perdida_minima_permutaciones = 0;
	int perdida_maxima_permutaciones = 0;
	int tmp = 0;
	list<pair<PorcentajePeso,pair<NroJoya,Joya> > > l2 = l;
	
	list<list<pair<PorcentajePeso,pair<NroJoya,Joya> > > > permutaciones = permute(l2);
	
	for(list<list<pair<PorcentajePeso,pair<NroJoya,Joya> > > >::iterator iter = permutaciones.begin(); iter != permutaciones.end(); iter++){
		
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
list<list<pair<PorcentajePeso,pair<NroJoya,Joya> > > > permute(list<pair<PorcentajePeso,pair<NroJoya,Joya> > > & L1){
    if (L1.size() == 1)
        return std::list<list<pair<PorcentajePeso,pair<NroJoya,Joya> > > >(1,L1);

    std::list<list<pair<PorcentajePeso,pair<NroJoya,Joya> > > > res;
    for (list<pair<PorcentajePeso,pair<NroJoya,Joya> > >::iterator i = L1.begin(); i != L1.end();)
    {
        // remember this
        pair<PorcentajePeso,pair<NroJoya,Joya> > x = (*i);

        // make a list without the current element
        list<pair<PorcentajePeso,pair<NroJoya,Joya> > > tmp(L1.begin(), i++);
        tmp.insert(tmp.end(), i, L1.end());

        // recurse to get all sub-permutations
        std::list<list<pair<PorcentajePeso,pair<NroJoya,Joya> > > > sub = permute(tmp);

        // amend sub-permutations by adding the element
        for (std::list<list<pair<PorcentajePeso,pair<NroJoya,Joya> > > >::iterator j=sub.begin(); j!=sub.end();j++)
            (*j).push_front(x);

        // finally append modified results to our running collection.
        res.insert(res.begin(), sub.begin(), sub.end());
    }
    return res;
}
