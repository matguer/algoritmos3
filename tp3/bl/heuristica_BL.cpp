#include <iostream>
#include <stdlib.h>
#include <list>
#include <cmath>
#include <vector>
#include "../graph.h"
#include "../algoritmos.h"

using namespace std;

bool pesoEnRegla(vector<int> camino, vector<vector<double> > pesos);
double getPeso(vector<int> camino, vector<vector<double> > pesos);
vector<int> switchTramo(vector<int> camino1, vector<int> tramoNuevo, int nodoSource, int nodoTarget);
void imprimirCamino(vector<int> camino);
double k;
graph* grafo;

int main(int argc, char* argv[]) {

	// Leo la entrada
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
	cin >> k;
	
	grafo = new graph(n);
	
	for(unsigned int i = 0; i<m; i++){
			cin >> v1;
			cin >> v2;
			cin >> w1;
			cin >> w2;
			grafo->add_edge(v1,v2,w1,w2);
	}

	algoritmos* algoritmo = new algoritmos();

	vector<vector<double> > pesos1 = grafo->get_weights1();
	vector<vector<int> > floyd1 = algoritmo->floyd(pesos1);
	//cout << "PESOS: " << endl;
	//for(unsigned int i=0; i<pesos1.size(); i++) {
	//	for(unsigned int j=0; j<pesos1.size(); j++) {
	//		cout << pesos1[i][j] << " ";
	//	}
	//	cout << endl;
	//}

	vector<int> camino1 = algoritmo->reconstruirPathFloyd(u,v,floyd1);

	if(!pesoEnRegla(camino1,pesos1)) {
		cout << "no" << endl;
		return 0;
	}

	vector<vector<double> > pesos2 = grafo->get_weights2();
	vector<vector<int> > floyd2 = algoritmo->floyd(pesos2);

	unsigned int j = 0;
	while(j!=camino1.size() - 1) {
		vector<int> tramoCamino2 = algoritmo->reconstruirPathFloyd(camino1[j],camino1[j+1], floyd2);
		vector<int> caminoNuevo = switchTramo(camino1, tramoCamino2, j, j+1);
		if(pesoEnRegla(caminoNuevo,pesos1)) {
			camino1 = caminoNuevo;
			j += tramoCamino2.size() - 1;
		}
		j++;
	}

	imprimirCamino(camino1);

	return 0;
}


bool pesoEnRegla(vector<int> camino, vector<vector<double> > pesos) {
	return k >= getPeso(camino, pesos);
}

double getPeso(vector<int> camino, vector<vector<double> > pesos) {
	double pesoTotal = 0.0;
	for(unsigned int i=0; i<camino.size()-1; i++) {
		pesoTotal += pesos[camino[i]][camino[i+1]];
	}
	return pesoTotal;
}

vector<int> switchTramo(vector<int> camino1, vector<int> tramoNuevo, int nodoSource, int nodoTarget) {
	unsigned int sizeCamino1 = camino1.size();
	unsigned int sizeTramoNuevo = tramoNuevo.size();

	vector<int> caminoNuevo = vector<int>(sizeCamino1 + sizeTramoNuevo - 1, 0);
	for(int i=0; i<=nodoSource; i++) {
		caminoNuevo[i] = camino1[i];
	}

	for(int i=nodoSource+1; i<(nodoSource + sizeTramoNuevo); i++) {
		caminoNuevo[i] = tramoNuevo[i-nodoSource-1];
	}

	for(unsigned int i=nodoSource+sizeTramoNuevo; i<caminoNuevo.size(); i++) {
		caminoNuevo[i] = camino1[i-sizeTramoNuevo+1];
	}
	
	return caminoNuevo;
}

void imprimirCamino(vector<int> camino) {
	for(vector<int>::const_iterator it = camino.begin(); it != camino.end(); ++it)
		cout << *it << " ";
	cout << endl;
}


