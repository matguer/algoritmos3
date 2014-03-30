#ifndef EJ1_H
#define EJ1_H

#include <list>
#include <utility>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include "vector"

using namespace std;

typedef std::vector<int> LCamiones;
typedef pair<int, int> intervalo;

// Prototipado de funciones
void mostrarResultado(intervalo);
intervalo resolver(LCamiones& c, int periodo);
int primeroMayor(LCamiones& c, int elem, int p, int f, int ultimoEncontrado);

#endif
