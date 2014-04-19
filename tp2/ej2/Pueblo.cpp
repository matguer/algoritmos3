#include "Pueblo.h"
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

Pueblo::Pueblo(){
	
	_id = 0;
	_id_grupo_pueblo = 0;
	_tiene_central = false;
	_coordenadas = pair<int,int>(0,0);
	
}

Pueblo::Pueblo(int id, int x, int y){
	
	_id = id;
	_id_grupo_pueblo = id;
	_tiene_central = false;
	_coordenadas = pair<int,int>(x,y);
	
}

int Pueblo::getId(){
	return _id;
}

int Pueblo::getIdGrupoPueblo(){
	return _id_grupo_pueblo;
}

void Pueblo::setIdGrupoPueblo(int id){
	_id_grupo_pueblo = id;
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
	os << "Pueblo(Id: " << p.getId() << ", Coord: <" << p.getX() << "," << p.getY() << ">, Central:" << p._tiene_central << ", IdGrupo: " << p._id_grupo_pueblo << "), ";
	return os;
}
