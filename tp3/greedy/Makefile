CXX = g++
CXXFLAGS=-g -Wall -std=c++98 -Werror -fno-stack-protector

.PHONY: all
all: main

main: heuristica_greedy.o ../algoritmos.o ../graph.o
	$(CXX) $(CXXFLAGS) heuristica_greedy.o ../graph.o ../algoritmos.o -o heuristica_greedy 
		
heuristica_greedy.o: heuristica_greedy.cpp ../algoritmos.h ../graph.h
../algoritmos.o: ../algoritmos.cpp ../algoritmos.h
../graph.o: ../graph.cpp ../graph.h

.PHONY: clean
clean:
	rm -f *.o ../*.o heuristica_greedy

.PHONY: new
new: clean all
