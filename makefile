FLAGS = -W -pedantic -std=c++17 -O3 

.PHONY = all clean cleanall

all: kompilator

kompilator: parser lexer memory code types machine
	g++ $(FLAGS) -o kompilator parser.o lexer.o memory.o code.o types.o machine.o

lexer: lexer.c
	g++ $(FLAGS) -o lexer.o -c lexer.c

parser: parser.tab.cpp
	g++ $(FLAGS) -o parser.o -c parser.tab.cpp

lexer.c: lexer.l
	flex -o lexer.c lexer.l

parser.tab.cpp: parser.ypp
	bison -d parser.ypp

memory: memory.cpp
	g++ $(FLAGS) -c memory.cpp -o memory.o

code: code.cpp
	g++ $(FLAGS) -c code.cpp -o code.o

types: types.cpp
	g++ $(FLAGS) -c types.cpp -o types.o

machine: machine.cpp
	g++ $(FLAGS) -c machine.cpp -o machine.o

clean:
	rm -f *.o *.tab.cpp *.tab.hpp lexer.c

cleanall: clean
	rm -f kompilator
                                  