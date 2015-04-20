# Makefile for yang.cpp

CC = g++

# Flags to the compiler

CFLAGS = -Wall

all: yang

yang: main.o btree.o
	${CC} -o yang main.o btree.o

main.o: main.cpp
	${CC} -c ${CFLAGS} main.cpp

btree.o: btree.cpp
	${CC} -c ${CFLAGS} btree.cpp

clean:
	rm -rf *.o
