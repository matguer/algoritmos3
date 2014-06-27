#include "heuristica_greedy.h"

int main(int argc, char* argv[]){
	
	// Leo la entrada
	double k;
	unsigned int n;
	unsigned int m;
	unsigned int u;
	unsigned int v;
	
	unsigned int v1;
	unsigned int v2;
	double w1;
	double w2;

	cin >> n;
	cin >> m;
	cin >> u;
	cin >> v;
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
	
	heuristicaGreedy* heuristica = new heuristicaGreedy(k, n, m, u, v);
	heuristica->execute(grafo);
	delete heuristica;
}
