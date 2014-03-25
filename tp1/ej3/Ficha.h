#ifndef __FICHA_H__
#define __FICHA_H__

typedef int Color;
#define NO_COLOR 0

class Ficha {
	
	private:
		int _numero;
		Color _izquierda;
		Color _derecha;
		Color _superior;
		Color _inferior;

	public:
		Ficha();
		Ficha(const Ficha& otra);
		Ficha(int numero, Color superior, Color izquierda, Color derecha, Color inferior);
		~Ficha();
		void print();
		int getNumero();
		Color getIzquierda();
		Color getDerecha();
		Color getSuperior();
		Color getInferior();
		void setIzquierda(Color color);
		void setDerecha(Color color);
		void setSuperior(Color color);
		void setInferior(Color color);
};

#endif
