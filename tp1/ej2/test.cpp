#include "ej2.h"
#include <time.h>

using namespace std;

/**
 * La función main toma el listado de trabajos por std input:
 */
int main(int argc, char *argv[])
{
	int n;
	int seed = (int) *argv[1]; // Semilla para los rand()
	list<Joya> * l;
	Joya * j;
	
	if(seed>0){
				
		srand(seed);
		
		// Tests aleatorios	
		for(int i=0;i<50;i++){
			
			l = new list<Joya>();
			n = rand() % 1000000 + 1;

			for(int k=0;k<n;k++){
				j = new Joya();
				j->devaluacion_diaria = rand() % 100 + 1;
				j->tiempo_fabricacion = rand() % 100 + 1;
				
				l->push_back(*j);
			}
			clock_t t = clock();
			resolver(*l);
			t = clock() - t;
			
			cout << n << "\t" << t << endl;
			
			/*
			if(esOptimo(*l2)){
				cout << "TEST: OK";
			}else{
				cout << "TEST: FAILED";
			}
			*/
			
			delete l;
			
		}
		
		/*
		t = clock() - t;
		cout << t << endl;
		*/
		
	}
	
	return 0;
	
}
