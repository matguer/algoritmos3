#include "ej1.h"

using namespace std;

/**
 * La función main toma el listado de instancias por std input:
 */
int main()
{
	int periodo;
	int totalCamiones;
	int camionI;
	int separador;

	while(true) {
		
		// Si termine de leer el archivo salgo
		if(cin.eof()){
			break;
		}

		// Primer int es la cantidad de dias que puedo contratar al inspector
		cin >> periodo;

		if(periodo==0){
			break;
		}
		cout << "periodo contratacion: " << periodo << endl;

		// Segundo int es la cantidad total de camiones
		cin >> totalCamiones;
		cout << "total camiones: " << totalCamiones << endl;
		
		LCamiones c = LCamiones();
		intervalo res = intervalo();

		// Armo la lista de camiones
		for(int i=0;i<totalCamiones;i++){
			cin >> camionI;
			cout << camionI << endl;
			c.push_back(camionI);
		}

		//return 0;

		// Capturo el 0 final
		cin >> separador;
		
		res = resolver(c, periodo, totalCamiones);
		mostrarResultado(res);
		
		periodo = 0;
		
	}

	return 0;
}


