#ifndef EJ2_H
#define EJ2_H

#include <list>
#include <utility>
#include <iostream>
#include <stdlib.h>

using namespace std;

typedef long double PorcentajePeso;

struct Joya {
	int identificador;
	int tiempo_fabricacion;
	int devaluacion_diaria;
	PorcentajePeso porcentaje_peso;
};

// Prototipado de funciones
void mostrarResultado(list<Joya> &l);
void resolver(list<Joya>& l);
bool pairCompare(const Joya& firstElem, const Joya& secondElem);
int perdida(const list<Joya> &l);
bool esOptimo(list<Joya>& l);
list<list<Joya> > permute(list<Joya> & L1);

#endif
