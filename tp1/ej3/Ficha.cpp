#include "Ficha.h"
#include <iostream>

using namespace std;

Ficha::Ficha() {
	_numero = 0;
	_superior = NO_COLOR;
	_izquierda = NO_COLOR;
	_derecha = NO_COLOR;
	_inferior = NO_COLOR;
}

Ficha::Ficha(const Ficha& otra) {
	_numero = otra._numero;
	_superior = otra._superior;
	_izquierda = otra._izquierda;
	_derecha = otra._derecha;
	_inferior = otra._inferior;
}

Ficha::Ficha(int numero, Color superior, Color izquierda, Color derecha, Color inferior) {
	_numero = numero;
	_superior = superior;
	_izquierda = izquierda;
	_derecha = derecha;
	_inferior = inferior;
}

Ficha::~Ficha() {
}

void Ficha::print() {
	cout << _numero;
	// cout << "Sup: " << _superior << " Izq: " << _izquierda << " Der: " << _derecha << " Inf: " << _inferior << endl;
}

int Ficha::getNumero() {
	return _numero;
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
