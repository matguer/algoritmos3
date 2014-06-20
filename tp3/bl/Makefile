CXX = g++
CXXFLAGS=-g -Wall -std=c++98 -Werror -fno-stack-protector

.PHONY: all
all: main

main: heuristica_BL.o ../algoritmos.o ../graph.o
	$(CXX) $(CXXFLAGS) heuristica_BL.o ../graph.o ../algoritmos.o -o heuristica_BL 
		
heuristica_BL.o: heuristica_BL.cpp ../algoritmos.h ../graph.h
../algoritmos.o: ../algoritmos.cpp ../algoritmos.h
../graph.o: ../graph.cpp ../graph.h

.PHONY: clean
clean:
	rm -f *.o ../*.o heuristica_BL

.PHONY: new
new: clean all
