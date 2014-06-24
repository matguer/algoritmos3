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
vector<int> switchTramo(vector<int> camino1, vector<int> tramoNuevo, int nodoSource);
void imprimirCamino(vector<int> camino);
void imprimirSolucion(vector<int> camino, vector<vector<double> > pesos1, vector<vector<double> > pesos2);
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

	/* Generacion del camino minimo para w1 */
	vector<int> camino1 = algoritmo->reconstruirPathFloyd(u,v,floyd1);

	/* Si este peso supera el K entonces no voy a encontrar uno menor,
		por lo tanto no hay solucion */
	if(!pesoEnRegla(camino1,pesos1)) {
		cout << "no" << endl;
		return 0;
	}

	cout << "camino1: ";
	imprimirCamino(camino1);
	cout << endl;
	
	vector<vector<double> > pesos2 = grafo->get_weights2();
	vector<vector<int> > floyd2 = algoritmo->floyd(pesos2);
	
	/* Se recorre todo el camino c1 y para cada par de nodos se va reemplazando el tramo por el 
		camino minimo entre ese par de nodos para w2. En cada iteracion si no se supera el 
		valor de K entonces se realiza el reemplazo.*/
	unsigned int j = 0;
	while(j!=camino1.size() - 1) {
		vector<int> tramoCamino2 = algoritmo->reconstruirPathFloyd(camino1[j],camino1[j+1], floyd2);
		cout << "tramo: ";
		imprimirCamino(tramoCamino2);
		cout << endl;
		vector<int> caminoNuevo = switchTramo(camino1, tramoCamino2, j);
		if(pesoEnRegla(caminoNuevo,pesos1)) {
			cout << "entro" << endl;
			camino1 = caminoNuevo;
			j += tramoCamino2.size() - 2;
		}
		j++;
	}

	imprimirSolucion(camino1, pesos1, pesos2);

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

vector<int> switchTramo(vector<int> camino1, vector<int> tramoNuevo, int nodoSource) {
	unsigned int sizeCamino1 = camino1.size();
	unsigned int sizeTramoNuevo = tramoNuevo.size();

	vector<int> caminoNuevo = vector<int>(sizeCamino1 + sizeTramoNuevo - 2, 0);

	/* El caminoNuevo se mantiene igual que camino1 hasta la posicion indicada como nodoSource */
	for(int i=0; i<=nodoSource; i++) {
		caminoNuevo[i] = camino1[i];
	}

	/* A partir del nodoSource en adelante se agrega el tramoNuevo */
	for(int i=nodoSource+1; i<(nodoSource + sizeTramoNuevo - 1); i++) {
		caminoNuevo[i] = tramoNuevo[i-nodoSource];
	}

	/* Una vez que se completo el tramoNuevo se siguen agregando las ultimas posiciones del camino1 */
	for(unsigned int i=nodoSource+sizeTramoNuevo - 1; i<caminoNuevo.size(); i++) {
		caminoNuevo[i] = camino1[i-sizeTramoNuevo+2];
	}
	
	return caminoNuevo;
}

void imprimirCamino(vector<int> camino) {
	for(vector<int>::const_iterator it = camino.begin(); it != camino.end(); ++it)
		cout << *it << " ";
}

void imprimirSolucion(vector<int> camino, vector<vector<double> > pesos1, vector<vector<double> > pesos2) {
	double pesoTotal1 = getPeso(camino, pesos1);
	double pesoTotal2 = getPeso(camino, pesos2);
	
	cout << pesoTotal1 << " " << pesoTotal2 << " " << camino.size() << " ";
	imprimirCamino(camino);
	cout << endl;
}
