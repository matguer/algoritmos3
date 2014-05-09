#include "Pueblo.h"
#include <vector>
#include <limits>
#include <iostream>
#include <math.h>

using namespace std;

Pueblo::Pueblo(){
	
	_id = 0;
	_distancia_arbol = std::numeric_limits<double>::infinity();
	_tiene_central = false;
	_coordenadas = pair<int,int>(0,0);
	
}

Pueblo::Pueblo(int id, int x, int y){
	
	_id = id;
	_distancia_arbol = std::numeric_limits<double>::infinity();
	_tiene_central = false;
	_coordenadas = pair<int,int>(x,y);
	
}

int Pueblo::getId(){
	return _id;
}

void Pueblo::setDistanciaArbol(double distancia){
	_distancia_arbol = distancia;
}

void Pueblo::setPuebloCercano(Pueblo* pCercano){
	_pueblo_cercano_arbol = pCercano;
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

double Pueblo::getDistanciaArbol(){
	return _distancia_arbol;
}

Pueblo * Pueblo::getPuebloCercano(){
	return _pueblo_cercano_arbol;
}

void Pueblo::instalarCentral(){
	_tiene_central = true;
}

bool Pueblo::operator==(const Pueblo& otra) {
	return (otra._id == _id);
}

bool Pueblo::tieneCentral(){
	return _tiene_central;
}

ostream& operator<<(ostream& os, Pueblo& p){
	os << "Pueblo(Id: " << p.getId() << ", Coord: <" << p.getX() << "," << p.getY() << ">, Central:" << p._tiene_central << "), ";
	return os;
}
