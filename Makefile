CC=gcc
CFLAGS=-Wall -Wextra -std=gnu17 -Wgnu-binary-literal -pedantic -ggdb -O2

BINARY=csgc
SOURCE=src/csgc.c

use-clang:
	$(CC) $(CFLAGS) -o $(BINARY) $(SOURCE) -DuseClang

use-gcc:
	$(CC) $(CFLAGS) -o $(BINARY) $(SOURCE)

For-Loop:
	./$(BINARY) examples/For-Loop.csg
	./a.out

Hello-World:
	./$(BINARY) examples/Hello-World.csg
	./a.out

If-Statements:
	./$(BINARY) examples/If-Statements.csg
	./a.out

Struct:
	./$(BINARY) examples/Struct.csg
	./a.out

Typedef-and-Define:
	./$(BINARY) examples/Typedef-and-Define.csg
	./a.out

Vector:
	./$(BINARY) examples/Vector.csg
	./a.out

While-Loop:
	./$(BINARY) examples/While-Loop.csg
	./a.out

CLI-Args:
	./$(BINARY) examples/CLI-Args.csg
	./a.out 1 2 3 "Hello World" "This is a test"
