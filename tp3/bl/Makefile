CXX = g++
CXXFLAGS=-g -Wall -std=c++98 -Werror -fno-stack-protector

.PHONY: all
all: main

main: main.o heuristica_BL.o ../algoritmos.o ../graph.o
	$(CXX) $(CXXFLAGS) main.o heuristica_BL.o ../graph.o ../algoritmos.o -o heuristica_BL 
	
test: test.o ../graph.o heuristica_BL.o
	$(CXX) $(CXXFLAGS) test.o ../graph.o heuristica_BL.o ../algoritmos.o -o test 
			
main.o: main.cpp
heuristica_greedy.o: heuristica_BL.cpp ../algoritmos.h ../graph.h
../algoritmos.o: ../algoritmos.cpp ../algoritmos.h
../graph.o: ../graph.cpp ../graph.h

.PHONY: clean
clean:
	rm -f *.o ../*.o heuristica_BL

.PHONY: new
new: clean all
