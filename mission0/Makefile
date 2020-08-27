CC=gcc
CFLAGS=-c -Wall

all: main.o util.o
	$(CC) main.o util.o -o main

main.o: main.c
	$(CC) $(CFLAGS) main.c

util.o: util.c
	$(CC) $(CFLAGS) util.c
