
#ifndef _DICCIONARIO_H_
#define _DICCIONARIO_H_

#include <SDL2/SDL.h>

#define COLUMNAS 2

typedef const int(* caracteres_t)[2];

typedef struct diccionario{
	char letra;
	int tam_filas ;
	caracteres_t caracter;
}diccionario_t;

extern const diccionario_t caracteres[];
extern const size_t tam_caracteres;

caracteres_t buscar_matriz_caracter(char letra, const diccionario_t caracteres[], size_t tam);

size_t buscar_filas_caracter(char letra, const diccionario_t caracteres[], size_t tam);


#endif // _DICCIONARIO_H_