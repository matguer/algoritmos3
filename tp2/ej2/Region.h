#ifndef __REGION_H__
#define __REGION_H__

#include "Pueblo.h"
#include <list>

using namespace std;

class Region {
	
	private:
		list<Pueblo> _pueblos ;
		int _centralitas;

	public:
		Region(list<Pueblo> lista_pueblos, int centralitas);
		Region();
		void print();
};

#endif
