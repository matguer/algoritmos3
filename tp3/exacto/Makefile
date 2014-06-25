CXX = g++
CXXFLAGS=-g -w -std=c++98 -Werror -fno-stack-protector

.PHONY: all
all: algoritmo_exacto test

algoritmo_exacto: algoritmo_exacto.o ../graph.o
	$(CXX) $(CXXFLAGS) algoritmo_exacto.o ../graph.o -o algoritmo_exacto 
	
test: test.o ../graph.o
	$(CXX) $(CXXFLAGS) test.o ../graph.o -o test 
		
algoritmo_exacto.o: algoritmo_exacto.cpp ../graph.h
../graph.o: ../graph.cpp ../graph.h

test.o: test.cpp ../graph.h

.PHONY: clean
clean:
	rm -f *.o ../*.o algoritmo_exacto test

.PHONY: new
new: clean all
