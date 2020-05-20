CC := gcc
CFLAGS := -Wall -c -pedantic -std=c99 -g -O3
LFLAGS := -lm -lSDL2
INSTALL_DIR := /usr/sbin

all: tp1

naves.o: naves.c naves.h 
	$(CC) $(CFLAGS) naves.c

caracteres.o: caracteres.c caracteres.h naves.h
	$(CC) $(CFLAGS) caracteres.c

movimientos.o: movimientos.c movimientos.h
	$(CC) $(CFLAGS) movimientos.c

vectores.o: vectores.c vectores.h
	$(CC) $(CFLAGS) vectores.c

diccionario.o: diccionario.h diccionario.c
	$(CC) $(CFLAGS) diccionario.c

renderizar.o: renderizar.c renderizar.h diccionario.h
	$(CC) $(CFLAGS) renderizar.c

terreno.o: terreno.c terreno.h vectores.h renderizar.h
	$(CC) $(CFLAGS) terreno.c

main.o: main.c config.h naves.h movimientos.h diccionario.h vectores.h terreno.h renderizar.h
	$(CC) $(CFLAGS) main.c

tp1: main.o naves.o caracteres.o movimientos.o vectores.o terreno.o diccionario.o renderizar.o 
	$(CC) $(LFLAGS) $^ -o tp1 -lSDL2 -lm

clean:
	rm *.o

install: tp1
	cp $^ $(INSTALL_DIR)

valgrind: tp1
	valgrind --leak-check=full ./tp1
