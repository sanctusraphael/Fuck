CC=gcc
CFLAGS=-Wall -g
SRC=src/*.c
OUTPUT=-o bin/fuck
C11=-std=c11

all:
	$(CC) $(SRC) $(CFLAGS) $(OUTPUT) $(C11)

clean:
	rm -f bin/fuck
