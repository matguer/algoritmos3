#include "Pueblo.h"
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

Pueblo::Pueblo(){
	
	_id = 0;
	_coordenadas = pair<int,int>(0,0);
	
}

Pueblo::Pueblo(int id, int x, int y){
	
	_id = id;
	_coordenadas = pair<int,int>(x,y);
	
}

int Pueblo::getId(){
	return _id;
}

int Pueblo::getX(){
	return _coordenadas.first;
}

int Pueblo::getY(){
	return _coordenadas.second;
}

double Pueblo::distancia(Pueblo & p){
	return sqrt( pow(_coordenadas.first - p.getX(),2) + pow(_coordenadas.second - p.getY(),2) );
}

ostream& operator<<(ostream& os, Pueblo& p){
	os << "Pueblo(" << p.getId() << ", <" << p.getX() << "," << p.getY() << ">), ";
	return os;
}
