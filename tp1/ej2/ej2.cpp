#include <list>
#include <utility>
#include <vector>
#include <iostream>
using namespace std;

// Varios typedefs
typedef pair<int, int> Joya;
typedef list<Joya> LJoya;

// Prototipado de funciones
void mostrar(const LJoya& l);
LJoya resolver(const LJoya& l);
bool esOptimo(const LJoya& l);

/**
 * La función main toma el listado de trabajos por std input:
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
		LJoya r = LJoya();
		
		for(int i=0;i<n;i++){
			Joya j = Joya();
			cin >> j.first;
			cin >> j.second;
			
			l.push_back(j);
			
		}
		// Capturo el 0 final
		cin >> separador;
		
		cout << "Lista obtenida:" << endl;
		mostrar(l);
		
		cout << "Orden optimo:" << endl;
		r = resolver(l);
		mostrar(r);
		
		n = 0;
		
		cout << endl;
	}

	return 0;
}

LJoya resolver(const LJoya& l){
	
	LJoya r = LJoya();
	
	return r;
}

void mostrar(const LJoya &l){
	
	for(LJoya::const_iterator iter = l.begin(); iter != l.end(); iter++){
		cout << "(" << iter->first << "," << iter->second << ") ";
	}
	
}
