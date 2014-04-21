#include "Region.h"
#include "Pueblo.h"
#include <list>
#include <time.h>	
#include <stdlib.h>   
#include <iostream>
#include <cmath>

using namespace std;

/**
 * La función main toma el listado de trabajos por std input:
 */

int main(int argc, char *argv[])
{
	int seed = (int) *argv[1]; // Semilla para los rand()

//int main (){
//	int seed;
//	cin >> seed;	
	if(seed>0){
		srand(seed);


		// Tests aleatorios	
		for(int i=0;i<3;i++){			
			int nroPueblos = rand() % 10000;
			int nroCentrales = rand() % 10000;
			list<Pueblo*> * pueblosLista = new list<Pueblo*>();
			int x, y;
			
			for(int j=0; j<nroPueblos; j++){

				x = rand() % 100;
				y = rand() % 100;
				Pueblo * p = new Pueblo(j, x, y);
				pueblosLista->push_back(p);


			}

			Region * r = new Region(pueblosLista, nroCentrales);

			
			clock_t t = clock();
			r->resolver();
			t = clock() - t;

			
			cout << nroPueblos << "\t"  << t << endl;
			
			delete r;
			//delete p;
			delete pueblosLista;
		}
	}
	return 0;	
}
