main: libgraphula.a
	clang --coverage -fsanitize=undefined main.c -L. -lgraphula -o main

libgraphula.a:	source.o
	ar -cr libgraphula.a source.o
	ranlib libgraphula.a

source.o:      source.c
	clang --coverage -c -O2 -ftrapv -fsanitize=undefined -Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self -Wswitch-default -Wfloat-equal -Wshadow -Wpointer-arith -Wtype-limits -Wempty-body -Wlogical-op -Wstrict-prototypes -Wold-style-declaration -Wold-style-definition -Wmissing-parameter-type -Wmissing-field-initializers -Wnested-externs -Wno-pointer-sign -std=gnu11 -lm source.c

Remove:
	rm -rf source.o
	rm -rf libgraphula.a
