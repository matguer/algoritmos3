#include "ej1.h"

using namespace std;

/**
 * La función main toma el listado de instancias por std input:
 */
int main(){
		
		LCartas* c = new LCartas();
		int cartaI;
		int cantInicial;

		cin >> cantInicial;
		cin >> cartaI;

		while(!cin.eof()){

			cout << cartaI << endl;
			c->push_back(cartaI);

			cin >> cartaI;
		}

		//Resultado res = Resultado();

		//res = resolver(*c);
		//mostrarResultado(res);

		delete(c);

	return 0;
}


