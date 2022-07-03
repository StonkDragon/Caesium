CC=gcc
CFLAGS=-Wall -Wextra -std=gnu17 -Wgnu-binary-literal -pedantic -ggdb -O2

BINARY=csgc
SOURCE=src/csgc.c

use-clang:
	$(CC) $(CFLAGS) -o $(BINARY) $(SOURCE) -DuseClang

use-gcc:
	$(CC) $(CFLAGS) -o $(BINARY) $(SOURCE)
