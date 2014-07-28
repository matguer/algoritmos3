#include "heuristica_grasp.h"

int main(int argc, char* argv[]){
	
	// Leo la entrada
	double k;
	int separador;
	unsigned int n;
	unsigned int m;
	unsigned int u;
	unsigned int v;
	
	unsigned int v1;
	unsigned int v2;
	double w1;
	double w2;
	
	int seed = (int) *argv[1]; // Semilla para los rand()
	int iteraciones = (int) *argv[2]; // Cantidad de iteraciones para grasp


	while(true) {
			
		// Si termine de leer el archivo salgo
		if(cin.eof()){
			break;
		}

		cin >> n;
		cin >> m;
		cin >> u;
		cin >> v;
		
		if(n == 0){
			break;
		}
		
		/* en el input los nodos van de 1 a N y el grafo los trabaja de 0 a N-1 */
		u--;
		v--;
		cin >> k;
		
		graph * grafo = new graph(n);
		
		for(unsigned int i = 0; i<m; i++){
				cin >> v1;
				cin >> v2;
				cin >> w1;
				cin >> w2;
				grafo->add_edge(v1-1,v2-1,w1,w2);
		}
		
		heuristicaGrasp* heuristica = new heuristicaGrasp(k, u, v);
		heuristica->execute(grafo, seed, iteraciones);
		delete heuristica;
		delete grafo;
		
		// Capturo el 0 final
		cin >> separador;
		cout << endl;
		n = 0;
		
	}

	return 0;
}
