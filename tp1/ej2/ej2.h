#ifndef EJ2_H
#define EJ2_H

#include <list>
#include <utility>
#include <iostream>
#include <stdlib.h>

using namespace std;

typedef int NroJoya;
typedef pair<int, int> Joya;
typedef list<Joya> LJoya;
typedef long double PorcentajePeso;

// Prototipado de funciones
void mostrarResultado(list<pair<PorcentajePeso,pair<NroJoya,Joya> > > &l);
list<pair<PorcentajePeso,pair<NroJoya,Joya> > > resolver(const LJoya& l);
bool pairCompare(const std::pair<PorcentajePeso, pair<NroJoya,Joya > >& firstElem, const std::pair<PorcentajePeso,pair<NroJoya,Joya> >& secondElem);
int perdida(const list<pair<PorcentajePeso,pair<NroJoya,Joya> > > &l);
bool esOptimo(list<pair<PorcentajePeso,pair<NroJoya,Joya> > >& l);
list<list<pair<PorcentajePeso,pair<NroJoya,Joya> > > > permute(list<pair<PorcentajePeso,pair<NroJoya,Joya> > > & L1);

#endif
