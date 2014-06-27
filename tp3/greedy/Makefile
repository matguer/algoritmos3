CXX = g++
CXXFLAGS=-g -Wall -std=c++98 -Werror -fno-stack-protector

.PHONY: all
all: main test

main: main.o heuristica_greedy.o ../algoritmos.o ../graph.o
	$(CXX) $(CXXFLAGS) main.o heuristica_greedy.o ../graph.o ../algoritmos.o -o heuristica_greedy 
	
test: test.o ../graph.o heuristica_greedy.o
	$(CXX) $(CXXFLAGS) test.o ../graph.o heuristica_greedy.o ../algoritmos.o -o test 
		
main.o: main.cpp
heuristica_greedy.o: heuristica_greedy.cpp ../algoritmos.h ../graph.h
../algoritmos.o: ../algoritmos.cpp ../algoritmos.h
../graph.o: ../graph.cpp ../graph.h

test.o: test.cpp heuristica_greedy.cpp ../graph.h

.PHONY: clean
clean:
	rm -f *.o ../*.o heuristica_greedy test

.PHONY: new
new: clean all
