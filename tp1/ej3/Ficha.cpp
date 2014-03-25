#include "Ficha.h"
#include <iostream>

using namespace std;

Ficha::Ficha() {
	_izquierda = NO_COLOR;
	_derecha = NO_COLOR;
	_superior = NO_COLOR;
	_inferior = NO_COLOR;
}

Ficha::Ficha(Color izquierda, Color superior, Color derecha, Color inferior) {
	_izquierda = izquierda;
	_derecha = derecha;
	_superior = superior;
	_inferior = inferior;
}

Ficha::~Ficha() {
}

void Ficha::print() {
	cout << "Izq: " << _izquierda << " Sup: " << _superior << " Der: " << _derecha << " Inf: " << _inferior << endl;
}

Color Ficha::getIzquierda() {
	return _izquierda;
}

Color Ficha::getDerecha() {
	return _derecha;
}

Color Ficha::getSuperior() {
	return _superior;
}

Color Ficha::getInferior() {
	return _inferior;
}

void Ficha::setIzquierda(Color color) {
	_izquierda = color;
}

void Ficha::setDerecha(Color color) {
	_derecha = color;
}

void Ficha::setSuperior(Color color) {
	_superior = color;
}

void Ficha::setInferior(Color color) {
	_inferior = color;
}
