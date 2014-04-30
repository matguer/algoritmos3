#ifndef __PUEBLO_H__
#define __PUEBLO_H__

#include <vector>
#include <math.h>
#include <iostream>

using namespace std;

typedef pair<int, int> Coord;

class Pueblo {
	
	private:
		int _id;
		Coord _coordenadas;
		bool _tiene_central;
		int _id_grupo_pueblo; // Sirve para identificar en que componente conexa se encuentra
		double _distancia_arbol; // Sirve para saber si agregarlo al arbol en cada iteracion
		Pueblo * _pueblo_cercano_arbol;

	public:
		Pueblo();
		Pueblo(int id, int x, int y);
		int getId();
		int getX();
		int getY();
		int getIdGrupoPueblo();
		bool tieneCentral();
		void setIdGrupoPueblo(int id);
		void setDistanciaArbol(double distancia);
		void setPuebloCercano(Pueblo* pCercano);
		double distancia(Pueblo & p);
		double getDistanciaArbol();
		Pueblo * getPuebloCercano();
		void instalarCentral();
		bool operator==(const Pueblo& otra);
		friend ostream& operator<<(ostream& os, Pueblo& p);
};

#endif
