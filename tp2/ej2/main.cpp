#include "Pueblo.h"
#include "Region.h"
#include <list>
#include <iostream>
#include <stdlib.h>

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
	
	r->resolver();
	
	r->print();
	
	r->printPueblosConectados();
	
	delete r;
	delete lista_pueblos;

}

