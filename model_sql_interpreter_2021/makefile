FLAGS= -g -O2 -ftrapv -fsanitize=undefined,address -Werror -Wignored-qualifiers -Winit-self -Wswitch-default -Wfloat-equal -Wshadow -Wpointer-arith -Wtype-limits -Wempty-body -Wmissing-field-initializers -Wcast-qual -Wwrite-strings -lm -Wno-c++11-extensions
SERVERNAME = server
CLIENTNAME = client

all: main

Table.o:
	gcc -c Table.c

TableWrapper.o:
	g++ -c TableWrapper.cpp

SocketException.o:
	g++ -c SocketException.cpp
SocketWrapper.o:
	g++ -c SocketWrapper.cpp

server: Table.o TableWrapper.o SocketException.o SocketWrapper.o
	g++ $(FLAGS) Table.o TableWrapper.o SocketException.o SocketWrapper.o Server.cpp -o $(SERVERNAME)

client: Table.o TableWrapper.o SocketException.o SocketWrapper.o
	g++ $(FLAGS) Table.o TableWrapper.o SocketException.o SocketWrapper.o Client.cpp -o $(CLIENTNAME)

clear:
	-rm *.o
	-rm *.out
	-rm *.gch
	-rm -r *.dSYM
	-rm $(SERVERNAME)
	-rm $(CLIENTNAME)
