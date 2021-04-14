COMPILER2=clang++
FLAGS2=--coverage -g
COMPILER=g++
FLAGS=-O2 -ftrapv -fsanitize=undefined,address -Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self -Wswitch-default -Wfloat-equal -Wshadow -Wpointer-arith -Wtype-limits -Wempty-body -Wlogical-op -Wmissing-field-initializers -Wcast-qual -Wwrite-strings -lm

all: main

try:
	-clear
	-clear
	-clear
	-rm main
	$(COMPILER) $(FLAGS) SparseMatrix.cpp SparseMatrix.hpp main.cpp -g -o main
	./main

main: SparseMatrix.o main.o
	$(COMPILER) $(FLAGS) SparseMatrix.o main.o -g -o main

main.o: main.cpp
	g++ -c main.cpp

SparseMatrix.o: SparseMatrix.cpp SparseMatrix.hpp
	g++ -c SparseMatrix.cpp SparseMatrix.hpp

test:
	-rm -rf code_coverage
	-rm main
	-rm a.out
	$(COMPILER2) $(FLAGS2) SparseMatrix.cpp SparseMatrix.hpp test1.cpp -g
	-./a.out
	$(COMPILER2) $(FLAGS2) SparseMatrix.cpp SparseMatrix.hpp test2.cpp -g
	-./a.out
	$(COMPILER2) $(FLAGS2) SparseMatrix.cpp SparseMatrix.hpp test3.cpp -g
	-./a.out
	$(COMPILER2) $(FLAGS2) SparseMatrix.cpp SparseMatrix.hpp test4.cpp -g
	-./a.out
	$(COMPILER2) $(FLAGS2) SparseMatrix.cpp SparseMatrix.hpp test5.cpp -g
	-./a.out
	$(COMPILER2) $(FLAGS2) SparseMatrix.cpp SparseMatrix.hpp test6.cpp -g
	-./a.out
	$(COMPILER2) $(FLAGS2) SparseMatrix.cpp SparseMatrix.hpp test7.cpp -g
	-./a.out
	$(COMPILER2) $(FLAGS2) SparseMatrix.cpp SparseMatrix.hpp test8.cpp -g
	-./a.out
	lcov -t "SPM" --output-file code_coverage.info --capture --directory .
	genhtml --branch-coverage --highlight --legend -o code_coverage code_coverage.info
	-rm a.out
	-rm *.gcda
	-rm *.gcno
	-rm code_coverage.info
	-rm code_coverage/*.png
	-rm *.hpp.gch
	-rm *.gch.tmp
	-rm -rf *.dSYM
	-rm -rf code_coverage/v1

clean:
	-rm
	-rm main
	-rm a.out
	-rm *.gcda
	-rm *.gcno
	-rm -rf code_coverage
	-rm -rf *.o
	-rm *.hpp.gch
	-rm -rf *.dSYM
	-clear
