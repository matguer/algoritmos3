#ifndef __BACKTRACK__
#define __BACKTRACK__

void backtrack(graph * grafo, int nodo_objetivo, double k, vector<bool> * nodos_visitados, Camino & camino_actual, Camino & mejor_camino, list<pair<double, double> > * posibles_caminos) {
	
	int ultimo_nodo = (*camino_actual.camino).back(); // Ultimo nodo agregado
	list<int> * nodos_adyacentes = grafo->get_adyacentes(ultimo_nodo); // Nodos adyacentes al ultimo nodo recorrido
	
	// Si me pase de la cota K corto esta rama
	if(camino_actual.w1_total > k){
		//cout << "me pase de la cota " << camino_actual.w1_total << " vs " << k << endl;
		return;
	}
	
	// Si ya encontre el nodo final termino
	if(ultimo_nodo == nodo_objetivo){
		/*
		for(list<int>::iterator f = (*camino_actual.camino).begin(); f != (*camino_actual.camino).end(); f++){
			cout << *f << " " << endl;
		}
		cout << endl;
		cout << "w1 total " << camino_actual.w1_total << endl;
		cout << "w2 total " << camino_actual.w2_total << endl << endl;
		*/
		if(camino_actual.w2_total < mejor_camino.w2_total){
			delete mejor_camino.camino;
			mejor_camino.camino = new list<int>((*camino_actual.camino));
			mejor_camino.w1_total = camino_actual.w1_total;
			mejor_camino.w2_total = camino_actual.w2_total;
		}
		
		posibles_caminos->push_back(pair<double, double>(camino_actual.w1_total, camino_actual.w2_total));
		
		return;
	}
	
	// Recorro los adyancentes del ultimo nodo recorrido
	for(list<int>::iterator nodo = nodos_adyacentes->begin(); nodo != nodos_adyacentes->end(); nodo++){
		// Si ya visite el nodo termino
		if((*nodos_visitados)[*nodo] == true){
			continue;
		}

		(*nodos_visitados)[*nodo] = true; // Marco el nodo como visitado para hacer el llamado recursivo
		(*camino_actual.camino).push_back(*nodo);
		camino_actual.w1_total = camino_actual.w1_total + grafo->get_w1(ultimo_nodo, *nodo);
		camino_actual.w2_total = camino_actual.w2_total + grafo->get_w2(ultimo_nodo, *nodo);

		backtrack(grafo, nodo_objetivo, k, nodos_visitados, camino_actual, mejor_camino, posibles_caminos);
		// Restauro el estado para cuando vuelva
		camino_actual.w1_total = camino_actual.w1_total - grafo->get_w1(ultimo_nodo, *nodo);
		camino_actual.w2_total = camino_actual.w2_total - grafo->get_w2(ultimo_nodo, *nodo);
		(*nodos_visitados)[*nodo] = false;
		(*camino_actual.camino).pop_back();
				
		
	}
	
	
}

#endif
