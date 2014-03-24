CXX = g++
CXXFLAGS=-g -Wall -std=c++98 -Werror -fno-stack-protector

BINARY=ej2
OBJECTS=ej2.o

.PHONY: clean all libs

all: $(OBJECTS) ej2

$(BINARY): ej2.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $<

clean:
	rm -f $(OBJECTS)
	rm -f $(BINARY)
