#include "ej2.h"
#include <time.h>

using namespace std;

/**
 * La función main toma el listado de trabajos por std input:
 */
int main()
{
	int n;
	int separador;
	list<Joya> l;
	list<Joya> r;
	list<Joya> * l2;
	Joya * j;
	
	// Lee el input y realiza los tests
	/*
	clock_t t;
	t = clock();
	*/
	
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
		
		l = list<Joya>();
		
		for(int i=0;i<n;i++){
			Joya j = Joya();
			cin >> j.devaluacion_diaria;
			cin >> j.tiempo_fabricacion;
			
			l.push_back(j);
			
		}
		// Capturo el 0 final
		cin >> separador;

		resolver(l);
		
		if(esOptimo(l)){
			cout << "TEST: OK";
		}else{
			cout << "TEST: FAILED";
		}
		cout << endl;
		
		n = 0;
		
	}
	
	// Tests aleatorios	
	for(int i=0;i<100;i++){
		
		l2 = new list<Joya>();
		n = rand() % 5 + 1;

		for(int k=0;k<n;k++){
			j = new Joya();
			j->devaluacion_diaria = rand() % 10 + 1;
			j->tiempo_fabricacion = rand() % 10 + 1;
			
			l2->push_back(*j);
		}
		
		resolver(*l2);
		
		if(esOptimo(*l2)){
			cout << "TEST: OK";
		}else{
			cout << "TEST: FAILED";
		}
		
		delete l2;
		
		cout << endl;
		
	}
	
	/*
	t = clock() - t;
	cout << t << endl;
	*/
	
	return 0;
	
}
