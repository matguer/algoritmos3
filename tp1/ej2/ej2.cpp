#include <list>
#include <utility>
#include <iostream>
using namespace std;

// Varios typedefs
typedef int NroJoya;
typedef pair<int, int> Joya;
typedef list<Joya> LJoya;

// Prototipado de funciones
void mostrar(const LJoya& l);
void mostrarResultado(list<pair<long double,pair<NroJoya,Joya> > > &l);
list<pair<long double,pair<NroJoya,Joya> > > resolver(const LJoya& l);
bool esOptimo(list<pair<long double,pair<NroJoya,Joya> > >& l);
bool pairCompare(const std::pair<long double, pair<NroJoya,Joya > >& firstElem, const std::pair<long double,pair<NroJoya,Joya> >& secondElem);
int perdida(const list<pair<long double,pair<NroJoya,Joya> > > &l);
list<list<pair<long double,pair<NroJoya,Joya> > > > permute(list<pair<long double,pair<NroJoya,Joya> > > & L1);

/**
 * La funci�n main toma el listado de trabajos por std input:
 */
int main()
{
	int n;
	int separador;

	while(true) {
		
		// Si termine de leer el archivo salgo
		if(cin.eof()){
			break;
		}

		// Primera linea es la cantidad de joyas
		cin >> n;

		if(n==0){
			break;
		}
		
		LJoya l = LJoya();
		std::list<pair<long double,pair<NroJoya,Joya> > > r = list<pair<long double,pair<NroJoya,Joya> > >();
		
		for(int i=0;i<n;i++){
			Joya j = Joya();
			cin >> j.first;
			cin >> j.second;
			
			l.push_back(j);
			
		}
		// Capturo el 0 final
		cin >> separador;
		
		r = resolver(l);
		mostrarResultado(r);
		cout << perdida(r) << endl;
		
		n = 0;
		
	}

	return 0;
}


/**
 * La funci�n devuelve una lista de pair<porcentajePeso,Joya>, 
 * donde porcentajePeso es el % del peso de la joya sobre el total de los pesos, 
 * y Joya los datos originales de input
 */
std::list<pair<long double,pair<NroJoya,Joya> > > resolver(const LJoya& l){
	
	list<pair<long double,pair<NroJoya,Joya> > > r = list<pair<long double,pair<NroJoya,Joya> > >();
	long double sumatoria_pesos = 0.0;
	long double peso;
	
	// Recorro las joyas para calcular el total de pesos : O(n)
	for(LJoya::const_iterator iter = l.begin(); iter != l.end(); iter++){
		// El "peso" de la joya se calcula como D / T
		peso = iter->first / iter->second;
		sumatoria_pesos = sumatoria_pesos + peso;
	}
	
	// Ahora armo la lista final con los % de peso sobre el total de cada joya : O(n)
	int i = 1;
	for(LJoya::const_iterator iter = l.begin(); iter != l.end(); iter++){
		pair<long double,pair<NroJoya,Joya> > pairResultado = pair<long double,pair<NroJoya,Joya> >();
		
		peso = iter->first / iter->second;
		
		pairResultado.first = peso / sumatoria_pesos;
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
 * Comparador para sort de list<pair<long double,pair<NroJoya,Joya> > >
 */
bool pairCompare(const std::pair<long double,pair<NroJoya,Joya> > & firstElem, const std::pair<long double,pair<NroJoya,Joya> > & secondElem) {
  return firstElem.first > secondElem.first;
}

/**
 * Muestra la lista del input
 */
void mostrar(const LJoya &l){
	
	for(LJoya::const_iterator iter = l.begin(); iter != l.end(); iter++){
		cout << "(" << iter->first << "," << iter->second << ") ";
	}
	
}

/**
 * Muestra la lista del resultado
 */
void mostrarResultado(list<pair<long double,pair<NroJoya,Joya> > > &l){
	
	for(list<pair<long double,pair<NroJoya,Joya> > >::iterator iter = l.begin(); iter != l.end(); iter++){
		cout << iter->second.first << " ";
	}
	
}


/**
 * Comprueba si el valor devuelto por "resolver" es el optimo, comparando con todas las posibles permutaciones
 */
bool esOptimo(list<pair<long double,pair<NroJoya,Joya> > > &l){
	
	int perdida_minima_permutaciones = 0;
	int tmp = 0;
	list<pair<long double,pair<NroJoya,Joya> > > l2 = l;
	
	list<list<pair<long double,pair<NroJoya,Joya> > > > permutaciones = permute(l2);
	
	for(list<list<pair<long double,pair<NroJoya,Joya> > > >::iterator iter = permutaciones.begin(); iter != permutaciones.end(); iter++){
		
		tmp = perdida(*iter);
		
		if(perdida_minima_permutaciones == 0 || perdida_minima_permutaciones > tmp){
			perdida_minima_permutaciones = tmp;
		}
		
	}
	
	int perdida_optimo = perdida(l);
	
	return (perdida_optimo<=perdida_minima_permutaciones);
	
}

/**
 * Calcula la perdida de dinero para una lista dada
 */
int perdida(const list<pair<long double,pair<NroJoya,Joya> > > &l){
	
	int dias_transcurridos = 0;
	int perdida_total = 0;
	
	for(list<pair<long double,pair<NroJoya,Joya> > >::const_iterator iter = l.begin(); iter != l.end(); iter++){
		dias_transcurridos = dias_transcurridos + iter->second.second.second;
		perdida_total = perdida_total + dias_transcurridos*iter->second.second.first;
	}
	
	return perdida_total;
}

/**
 * Permuta la lista de un resultado
 */
list<list<pair<long double,pair<NroJoya,Joya> > > > permute(list<pair<long double,pair<NroJoya,Joya> > > & L1){
    if (L1.size() == 1)
        return std::list<list<pair<long double,pair<NroJoya,Joya> > > >(1,L1);

    std::list<list<pair<long double,pair<NroJoya,Joya> > > > res;
    for (list<pair<long double,pair<NroJoya,Joya> > >::iterator i = L1.begin(); i != L1.end();)
    {
        // remember this
        pair<long double,pair<NroJoya,Joya> > x = (*i);

        // make a list without the current element
        list<pair<long double,pair<NroJoya,Joya> > > tmp(L1.begin(), i++);
        tmp.insert(tmp.end(), i, L1.end());

        // recurse to get all sub-permutations
        std::list<list<pair<long double,pair<NroJoya,Joya> > > > sub = permute(tmp);

        // amend sub-permutations by adding the element
        for (std::list<list<pair<long double,pair<NroJoya,Joya> > > >::iterator j=sub.begin(); j!=sub.end();j++)
            (*j).push_front(x);

        // finally append modified results to our running collection.
        res.insert(res.begin(), sub.begin(), sub.end());
    }
    return res;
}
