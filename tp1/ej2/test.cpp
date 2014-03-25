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
		
		LJoya l = LJoya();
		std::list<pair<PorcentajePeso,pair<NroJoya,Joya> > > r = list<pair<PorcentajePeso,pair<NroJoya,Joya> > >();
		
		for(int i=0;i<n;i++){
			Joya j = Joya();
			cin >> j.first;
			cin >> j.second;
			
			l.push_back(j);
			
		}
		// Capturo el 0 final
		cin >> separador;

		r = resolver(l);
		
		if(esOptimo(r)){
			cout << "TEST: OK";
		}else{
			cout << "TEST: FAILED";
		}
		cout << endl;
		
		n = 0;
		
	}

	return 0;
	
}
