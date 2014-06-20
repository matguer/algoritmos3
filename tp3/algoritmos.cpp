#include "algoritmos.h"

algoritmos::algoritmos(){}

algoritmos::~algoritmos(){}

vector<vector<int> > algoritmos::floyd(graph* grafo, int w) {

	vector<vector<double> > matrizWeight;
	if(w==1) matrizWeight = vector<vector<double> >(grafo->get_weights1());
	else matrizWeight = vector<vector<double> >(grafo->get_weights2());

	int cant_nodos = matrizWeight.size();

	vector<vector<int> > matrizNext = vector<vector<int> >(cant_nodos,vector<int>(cant_nodos,-1));
	
	//Inicializo la matrizNext con los nodos siguientes
	for(int i = 0; i < cant_nodos; i++){
		for(int j = 0; j< cant_nodos; j++){
			if (i != j) (matrizNext)[i][j] = j;
		}
	}
	
	
	for(int k = 0; k < cant_nodos; k++){
		for(int i = 0; i < cant_nodos; i++){
			for(int j = 0; j< cant_nodos; j++){
				if (i != j){
					if ((matrizWeight)[i][j] > (matrizWeight)[i][k] + (matrizWeight)[k][j]){
						(matrizWeight)[i][j] = (matrizWeight)[i][k] + (matrizWeight)[k][j];
						(matrizNext)[i][j] = (matrizNext)[i][k];
					}
				}
			}
		}
	}

	cout << "PESOS: " << endl;
	for(unsigned int i=0; i<matrizWeight.size(); i++) {
		for(unsigned int j=0; j<matrizWeight.size(); j++) {
			cout << matrizWeight[i][j] << " ";
		}
		cout << endl;
	}

	return matrizNext;
}


vector<int> algoritmos::reconstruirPath(int u, int v, vector<vector<int> > matrizNext){
	
	vector<int> path = vector<int>();
	
	while(u != v){
		u = (matrizNext)[u][v];
		path.push_back(u);
	}
	return path;
}

