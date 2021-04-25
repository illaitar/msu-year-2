FLAGS= -g -O2 -ftrapv -fsanitize=undefined,address -Werror -Wignored-qualifiers -Winit-self -Wswitch-default -Wfloat-equal -Wshadow -Wpointer-arith -Wtype-limits -Wempty-body -Wmissing-field-initializers -Wcast-qual -Wwrite-strings -lm
SERVERNAME = server
CLIENTNAME = client

all: main

Table.o:
	gcc -c Table.h Table.c

TableWrapper.o:
	g++ -c TableWrapper.hpp TableWrapper.cpp

SocketException.o:
	g++ -c SocketException.hpp SocketException.cpp

SocketWrapper.o:
	g++ -c SocketWrapper.hpp SocketWrapper.cpp

ConsoleGraphics.o:
	g++ -c ConsoleGraphics.hpp ConsoleGraphics.cpp

SQLServer.o:
	g++ -c SQLServer.hpp SQLServer.cpp

SQLClient.o:
	g++ -c SQLClient.hpp SQLClient.cpp

server: Table.o TableWrapper.o SocketException.o SocketWrapper.o SQLServer.o
	g++ $(FLAGS) Table.o TableWrapper.o SocketException.o SocketWrapper.o SQLServer.o Server.cpp -o $(SERVERNAME)

gclient: Table.o TableWrapper.o SocketException.o SocketWrapper.o ConsoleGraphics.o SQLClient.o
	g++ $(FLAGS) Table.o TableWrapper.o SocketException.o SocketWrapper.o ConsoleGraphics.o SQLClient.o GClient.cpp -o $(CLIENTNAME)

client: Table.o TableWrapper.o SocketException.o SocketWrapper.o SQLClient.o
	g++ $(FLAGS) Table.o TableWrapper.o SocketException.o SocketWrapper.o SQLClient.o Client.cpp -o $(CLIENTNAME)

clear:
	-rm *.o
	-rm *.out
	-rm *.gch
	-rm -r *.dSYM
	-rm $(SERVERNAME)
	-rm $(CLIENTNAME)
