COMPILER2=clang
FLAGS2=--coverage -g
COMPILER=gcc
FLAGS=-O2 -ftrapv -fsanitize=undefined -Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self -Wswitch-default -Wfloat-equal -Wshadow -Wpointer-arith -Wtype-limits -Wempty-body -Wlogical-op -Wstrict-prototypes -Wold-style-declaration -Wold-style-definition -Wmissing-parameter-type -Wmissing-field-initializers -Wnested-externs -Wno-pointer-sign -std=gnu11 -lm
NAME=P4_grep

all: main

tests: test_build

main:
	$(COMPILER) $(FLAGS) $(NAME).c -g -o main

test:
	$(COMPILER2) $(FLAGS2) $(NAME).c -g -o to_test
	-valgrind ./to_test 1 test1.txt
	-valgrind ./to_test -v 1 test1.txt
	-valgrind ./to_test life test2.txt
	-valgrind ./to_test -v life test2.txt
	-valgrind ./to_test -vn life test2.txt
	-valgrind ./to_test 1 < test1.txt
	-valgrind ./to_test 1 test3.txt
	-valgrind ./to_test 1 1
	-valgrind ./to_test
	-valgrind ./to_test ha ha ha
	-valgrind ./to_test -vzp test test1.txt
	-llvm-cov gcov -f -b $(NAME).gcda
	-rm $(NAME).gcno
	-rm $(NAME).c.gcov
	-rm $(NAME).gcda
	-rm to_test

clean:
	rm main

