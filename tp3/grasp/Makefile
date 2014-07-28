CXX = g++
CXXFLAGS=-g -Wall -std=c++98 -Werror -fno-stack-protector

.PHONY: all
all: main test

main: main.o heuristica_grasp.o ../Algoritmos.o ../graph.o heuristica_greedy.o heuristica_BL.o
	$(CXX) $(CXXFLAGS) main.o heuristica_grasp.o ../graph.o ../Algoritmos.o heuristica_greedy.o heuristica_BL.o -o heuristica_grasp 
	
test: test.o ../graph.o heuristica_grasp.o
	$(CXX) $(CXXFLAGS) test.o ../graph.o heuristica_grasp.o ../Algoritmos.o heuristica_greedy.o heuristica_BL.o -o test 
		
main.o: main.cpp
heuristica_grasp.o: heuristica_grasp.cpp ../Algoritmos.h ../graph.h
heuristica_greedy.o: heuristica_greedy.cpp
heuristica_BL.o: heuristica_BL.cpp
../Algoritmos.o: ../Algoritmos.cpp ../Algoritmos.h
../graph.o: ../graph.cpp ../graph.h

test.o: test.cpp heuristica_grasp.cpp ../graph.h

.PHONY: clean
clean:
	rm -f *.o ../*.o heuristica_grasp test

.PHONY: new
new: clean all
