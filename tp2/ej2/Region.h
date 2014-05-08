#ifndef __REGION_H__
#define __REGION_H__

#include "Pueblo.h"
#include <list>
#include <limits>

using namespace std;

class Region {
	
	private:
		list<Pueblo*> * _pueblos ;
		list<pair<Pueblo*, Pueblo*> > * _arbol_pueblos ;
		int _centralitas;
		int _centrales_instaladas;
		int _tuberias_instaladas;
		vector< pair<pair<Pueblo*,Pueblo*>, double> > * _pueblos_por_distancia; // Pares de pueblos de mas cercanos a mas lejanos


	public:
		Region(list<Pueblo*> * lista_pueblos, int centralitas);
		Region();
		~Region();
		void print();
		void resolver();
		void printPueblosConectados();
		int getCentralesInstaladas();
		int getTuberiasInstaladas();
		Pueblo* actualizarDistancias(Pueblo* puebloNuevo);
};

#endif
