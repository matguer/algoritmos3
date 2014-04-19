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
	
	//r->printPueblosConectados();
	//r->print();
	
	//Imprimo q y m
	cout << r->getCentralesInstaladas() << " " << r->getTuberiasInstaladas() << endl;
	
	// Imprimo donde se instalaron centrales
	for(list<Pueblo*>::iterator p = lista_pueblos->begin(); p != lista_pueblos->end(); p++){
		if((**p).tieneCentral()){
			cout << (**p).getId() << " ";
		}
	}
	cout << endl;
	
	// Imprimo donde se pusieron las tuberias
	int i = 1;
	for(list<Pueblo*>::iterator p = lista_pueblos->begin(); p != lista_pueblos->end(); p++){
		
		int j = 1;
		for(list<Pueblo*>::iterator p2 = lista_pueblos->begin(); p2 != lista_pueblos->end(); p2++){
			
			// Para evitar guardar la distancia simetrica
			if(i > j && r->hayTuberia(**p,**p2)){
				cout << (**p).getId() << " " << (**p2).getId() << endl;
			}
			
			j++;
			
		}
		i++;
	}
	
	delete r;
	delete lista_pueblos;

}

