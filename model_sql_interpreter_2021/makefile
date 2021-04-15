COMPILER2=clang++
FLAGS2=--coverage -g
COMPILER=g++
FLAGS= -O2 -ftrapv -fsanitize=undefined,address -Werror -Wignored-qualifiers -Winit-self -Wswitch-default -Wfloat-equal -Wshadow -Wpointer-arith -Wtype-limits -Wempty-body -Wmissing-field-initializers -Wcast-qual -Wwrite-strings -lm -Wno-c++11-extensions

all: main

server:
	gcc -c Table.h Table.c
	g++ -c socket.cpp server.cpp
	g++ Table.o socket.o server.cpp -o server.out

client:
	gcc -c Table.h Table.c
	g++ -c socket.cpp client.cpp
	g++ Table.o socket.o server.cpp -o client.out


clear:
	-rm *.o
	-rm *.out
	-rm *.gch
