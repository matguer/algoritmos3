#include "Region.h"
#include "Pueblo.h"
#include <iostream>

using namespace std;

Region::Region(){
	
	_centralitas = 0;
	_pueblos = list<Pueblo>();
	
}

Region::Region(list<Pueblo> lista_pueblos, int centralitas){
	
	_centralitas = centralitas;
	_pueblos = lista_pueblos;
	
	for(list<Pueblo>::iterator p = _pueblos.begin(); p != _pueblos.end(); p++){
		
		for(list<Pueblo>::iterator p2 = _pueblos.begin(); p2 != _pueblos.end(); p2++){
			cout << "distancia entre " << *p << " y " << *p2 << ": " << p->distancia(*p2) << endl;
		}
		
	}
	
}

void Region::print(){
	
	cout << "#Pueblos: " << _pueblos.size() << endl;
	cout << "Centralitas: " << _centralitas << endl << endl;
	
	cout << "[";
	
	for(list<Pueblo>::iterator p = _pueblos.begin(); p != _pueblos.end(); p++){
		
		cout << *p;
	}
	
	cout << "]" << endl;
	
}

