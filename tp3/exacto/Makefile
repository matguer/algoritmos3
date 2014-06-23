CXX = g++
CXXFLAGS=-g -Wall -std=c++98 -Werror -fno-stack-protector

.PHONY: all
all: algoritmo_exacto

algoritmo_exacto: algoritmo_exacto.o ../graph.o
	$(CXX) $(CXXFLAGS) algoritmo_exacto.o ../graph.o -o algoritmo_exacto 
		
algoritmo_exacto.o: algoritmo_exacto.cpp ../graph.h
../graph.o: ../graph.cpp ../graph.h

.PHONY: clean
clean:
	rm -f *.o ../*.o algoritmo_exacto

.PHONY: new
new: clean all
