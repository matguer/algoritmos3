#include "algoritmos.h"

algoritmos::algoritmos(){}

algoritmos::~algoritmos(){}

vector<vector<int> > algoritmos::floyd(vector<vector<double> >& matrizWeight) {

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

	return matrizNext;
}


vector<int> algoritmos::reconstruirPathFloyd(int u, int v, vector<vector<int> > matrizNext){
	
	vector<int> path = vector<int>();
	
	while(u != v){
		u = (matrizNext)[u][v];
		path.push_back(u);
	}
	return path;
}

