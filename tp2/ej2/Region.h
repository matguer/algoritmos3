#ifndef __REGION_H__
#define __REGION_H__

#include "Pueblo.h"
#include <list>

using namespace std;

class Region {
	
	private:
		list<Pueblo*> * _pueblos ;
		int _centralitas;
		int _centrales_instaladas;
		int _tuberias_instaladas;
		list<pair<pair<Pueblo*,Pueblo*>, double> > * _pueblos_por_distancia; // Pares de pueblos de mas cercanos a mas lejanos
		vector<vector<bool> > * _pueblos_conectados_ady; // Matriz de adyacencia que representa las tuberias construidas
		int _cant_grupos_pueblos; // Cantidad de componentes conexas

	public:
		Region(list<Pueblo*> * lista_pueblos, int centralitas);
		Region();
		~Region();
		void print();
		void resolver();
		void printPueblosConectados();
};

#endif
