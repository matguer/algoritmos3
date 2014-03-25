CXX = g++
CXXFLAGS=-g -Wall -std=c++98 -Werror -fno-stack-protector
OBJS=main.o Ficha.o Tablero.o
MAIN=ej3

.PHONY: all
all: $(MAIN)

$(MAIN): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ 

main.o: main.cpp Ficha.h
Ficha.o: Ficha.cpp Ficha.h
Tablero.o: Tablero.cpp Tablero.h Ficha.h

.PHONY: new
clean:
	rm -f ./*.o ej3

.PHONY: new
new: clean all
