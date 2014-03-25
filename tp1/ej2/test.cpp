#include "ej2.h"

using namespace std;

/**
 * La función main toma el listado de trabajos por std input:
 */
int main()
{
	int n;
	int separador;
	LJoya l;
	list<pair<PorcentajePeso,pair<NroJoya,Joya> > > r;
	LJoya * l2;
	Joya * j;
	
	// Lee el input y realiza los tests

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
		
		l = LJoya();
		r = list<pair<PorcentajePeso,pair<NroJoya,Joya> > >();
		
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
	
	// Tests aleatorios	
	for(int i=0;i<100;i++){
		
		l2 = new LJoya();
		n = rand() % 5 + 1;
		cout << n << endl;
		for(int k=0;k<n;k++){
			j = new Joya();
			j->first = rand() % 10 + 1;
			j->second = rand() % 10 + 1;
			
			l2->push_back(*j);
		}
		
		r = resolver(*l2);
		
		if(esOptimo(r)){
			cout << "TEST: OK";
		}else{
			cout << "TEST: FAILED";
		}
		
		delete l2;
		
		cout << endl;
		
	}
	

	return 0;
	
}
