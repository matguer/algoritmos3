#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <assert.h>
#include "graph.h"

using namespace std;

int main(int argc, char* argv[]){
		

		// Leo la entrada
		unsigned int n;
		unsigned int m;
		unsigned int u;
		unsigned int v;
		unsigned int k;
		
		unsigned int v1;
		unsigned int v2;
		unsigned int w1;
		unsigned int w2;

		cin >> n;
		cin >> m;
		cin >> u;
		cin >> v;
		cin >> k;
		
		graph * grafo = new graph(n);
		
		for(unsigned int i = 0; i<n; i++){
				cin >> v1;
				cin >> v2;
				cin >> w1;
				cin >> w2;
				grafo->add_edge(v1,v2,w1,w2);
		}

		

}
