#ifndef __FICHA_H__
#define __FICHA_H__

typedef int Color;
typedef int Lado;
#define NO_COLOR 0
#define SUPERIOR 0
#define IZQUIERDA 1
#define DERECHA 2
#define INFERIOR 3

class Ficha {
	
	private:
		int _numero;
		Color _colores[4];

	public:
		Ficha();
		Ficha(const Ficha& otra);
		Ficha(int numero, Color superior, Color izquierda, Color derecha, Color inferior);
		Ficha operator= (const Ficha&);
		~Ficha();
		void print();
		Color getLado(Lado lado);
		int getNumero();
		bool isVacia();
};

#endif
