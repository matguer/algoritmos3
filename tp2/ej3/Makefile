CXX = g++
CXXFLAGS=-g -Wall -std=c++98 -Werror -fno-stack-protector
OBJS=ej3.o directed_graph.o
MAIN=ej3

.PHONY: all
all: $(MAIN)

$(MAIN): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ 
	
ej3.o: ej3.cpp directed_graph.h
directed_graph.o: directed_graph.cpp directed_graph.h

.PHONY: clean
clean:
	rm -f *.o ej3

.PHONY: new
new: clean all
