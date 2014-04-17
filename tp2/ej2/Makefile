CXX = g++
CXXFLAGS=-g -Wall -std=c++98 -Werror -fno-stack-protector -O3
OBJS=main.o Pueblo.o Region.o
MAIN=ej2

.PHONY: all
all: $(MAIN)

$(MAIN): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ 

main.o: main.cpp Pueblo.h Region.h
Pueblo.o: Pueblo.cpp Pueblo.h
Region.o: Region.cpp Region.h Pueblo.h

.PHONY: new
clean:
	rm -f ./*.o ej3

.PHONY: new
new: clean all
