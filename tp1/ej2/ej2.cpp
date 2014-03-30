#include "ej2.h"

using namespace std;

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
		
		list<Joya> l = list<Joya>();
		
		for(int i=0;i<n;i++){
			
			Joya j = Joya();
			cin >> j.devaluacion_diaria;
			cin >> j.tiempo_fabricacion;

			l.push_back(j);
			
		}
		// Capturo el 0 final
		cin >> separador;
		
		resolver(l);
		mostrarResultado(l);
		cout << perdida(l) << endl;
		
		n = 0;
		
	}

	return 0;
}


