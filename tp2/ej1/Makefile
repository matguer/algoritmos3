CXX = g++
CXXFLAGS=-g -Wall -std=c++98 -Werror -fno-stack-protector

all: ej1 test

ej1: ej1.o
	$(CXX) $(CXXFLAGS) ej1.o -o ej1
	
test: test.o utils.o
	$(CXX) $(CXXFLAGS) test.o utils.o -o test

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $<

clean:
	rm -f *.o ej1 test
