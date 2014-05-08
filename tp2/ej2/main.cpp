#include "Pueblo.h"
#include "Region.h"
#include <list>
#include <limits>
#include <iostream>
#include <stdlib.h>
#include <cstdlib>


using namespace std;

int main(int argc, char* argv[]) {

	int cant_pueblos, cant_centrales, x, y;

	cin >> cant_pueblos;
	cin >> cant_centrales;
	
	list<Pueblo*> * lista_pueblos = new list<Pueblo*>();
	
	for(int i = 1; i<= cant_pueblos; i++){
		cin >> x;
		cin >> y;
		Pueblo * p = new Pueblo(i, x, y);
		lista_pueblos->push_back(p);
	} 
	
	Region * r = new Region(lista_pueblos, cant_centrales);

	clock_t timer = clock();	
	
	r->resolver();
	
	// Si recibe un 1 como parametro se habilita el modo de medicion.
	if(argc > 1 && atoi(argv[1]) == 1) {
		timer = clock() - timer;
		cout << "TIEMPO: " << timer << endl;
	}

	r->printPueblosConectados();
	
	delete r;
	delete lista_pueblos;

}

