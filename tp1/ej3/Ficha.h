#ifndef __FICHA_H__
#define __FICHA_H__

typedef int Color;

class Ficha {
	
	private:
		Color _izquierda;
		Color _derecha;
		Color _superior;
		Color _inferior;

	public:
		Ficha();
		Ficha(Color izquierda, Color superior, Color derecha, Color inferior):
		~Ficha();
		
};

#endif
