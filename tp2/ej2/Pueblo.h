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

	public:
		Pueblo();
		Pueblo(int id, int x, int y);
		int getId();
		int getX();
		int getY();
		double distancia(Pueblo & p);
		friend ostream& operator<<(ostream& os, Pueblo& p);
};

#endif
