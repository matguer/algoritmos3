#include "ej1.h"
#include <time.h>
#include <cmath>

using namespace std;

/**
 * La función main toma el listado de trabajos por std input:
 */
int main(int argc, char *argv[])
{
	int seed = (int) *argv[1]; // Semilla para los rand()
	int periodo;
	LCamiones* camionesLista;
	int nroCamiones;
	int camionDia;
	
	if(seed>0){
				
		srand(seed);

		periodo = rand() % 100000;
		
		// Tests aleatorios	
		for(int i=0;i<100;i++){
			camionesLista = new LCamiones();
			nroCamiones = rand() % 10000000 + 1;
			//periodo = nroCamiones;

			for(int k=0;k<nroCamiones;k++){
				camionDia = rand() % 10000000;
				camionesLista->push_back(camionDia);
			}
			clock_t t = clock();
			resolver(*camionesLista, periodo);
			t = clock() - t;
			//float t_float = (float)t/log2f((float)nroCamiones);
		
			cout << nroCamiones << "\t" << t << endl;
			
			//cout << nroCamiones << "\t" << t_float << endl;
			delete camionesLista;	
		}
	}
	
	return 0;
	
}
