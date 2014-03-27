#ifndef EJ1_H
#define EJ1_H

#include <list>
#include <utility>
#include <iostream>
#include <stdlib.h>

using namespace std;

typedef list<int> LCamiones;
typedef pair<int, int> intervalo;

// Prototipado de funciones
void mostrarResultado(intervalo);
intervalo resolver(LCamiones& c, int periodo, int totalCamiones);

#endif
