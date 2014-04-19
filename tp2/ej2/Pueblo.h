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

	public:
		Pueblo();
		Pueblo(int id, int x, int y);
		int getId();
		int getX();
		int getY();
		int getIdGrupoPueblo();
		bool tieneCentral();
		void setIdGrupoPueblo(int id);
		double distancia(Pueblo & p);
		void instalarCentral();
		bool operator==(const Pueblo& otra);
		friend ostream& operator<<(ostream& os, Pueblo& p);
};

#endif
