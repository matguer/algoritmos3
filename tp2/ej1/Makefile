CXX = g++
CXXFLAGS=-g -Wall -std=c++98 -Werror -fno-stack-protector

all: ej1

ej1: ej1.o
	$(CXX) $(CXXFLAGS) ej1.o -o ej1

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $<

clean:
	rm -f *.o ej1
