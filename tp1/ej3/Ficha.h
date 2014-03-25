#ifndef __FICHA_H__
#define __FICHA_H__

typedef int Color;
#define NO_COLOR 0

class Ficha {
	
	private:
		Color _izquierda;
		Color _derecha;
		Color _superior;
		Color _inferior;

	public:
		Ficha();
		Ficha(Color izquierda, Color superior, Color derecha, Color inferior);
		~Ficha();
		void print();
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
