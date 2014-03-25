CXX = g++
CXXFLAGS=-g -Wall -std=c++98 -Werror -fno-stack-protector

all: ej2 test

ej2: ej2.o utils.o
	$(CXX) $(CXXFLAGS) ej2.o utils.o -o ej2
	
test: test.o utils.o
	$(CXX) $(CXXFLAGS) test.o utils.o -o test

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $<

clean:
	rm -f *.o ej2 test
