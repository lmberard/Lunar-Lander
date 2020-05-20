
#ifndef _TERRENO_H_
#define _TERRENO_H_

#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <time.h>
#include "config.h"
#include "vectores.h"
#include "renderizar.h"

//FUNCIONES PARA GENERAR EL TERRENO--------------------------------------------------------------------------------
//TERRENO.C

//dado una matriz v con nv coordenadas de x pero nn-nv espacios libres, me devuelve una nueva coordenadas x random
float generar_x(float **v, size_t nv);

//dado un xrandom busca entre que intervalo de los valores originales de v (de 0 a nv) esta
int buscar_intervalo(float **v, float xrandom, size_t nv);

//dadas las coordenadas del intervalo de xrandom [(xmin,ymin),(xmax,ymax)], devuelve el valor de y que esta en la recta que une los dos puntos del intervalo
float buscar_yrecta(float xmin, float xmax, float ymin,float ymax, float xrandom);

//dado el valor de y que esta en la recta que une los puntos, genera un y aleatorio que este dentro del margen.
float generar_y(float yrecta, float margen);

//dado un vector v de nv coordenadas, devuelve el mismo vector pero con nn-nv nuevas coordenadas aleatorias
float **agregar_datos_random(float **v, size_t nv, size_t nn, float margen);

//dado un vector v de nv coordenadas en R2 devuelve un nuevo vector con nn coordenadas generado con un margen de ±margen con respecto a las rectas definidas por v.
float **densificar_vector(float **v, size_t nv, size_t nn, float margen);

//genera un terreno aleatorio de n nuevas coordenadas
float **crear_terreno(size_t * n);

//Segun la posicion x e y de la nave me dice si llego al terreno. 
bool llego_al_terreno(float **terreno, size_t n, float posicion_x, float posicion_y);

//Función utilizada para calcular la altitud de la nave.
float distancia_al_terreno(float **terreno, size_t tam_terreno, float posicion_x, float posicion_y);

//Analiza como aterriza la nave segun sus parametros. 
void analizar_aterrizaje(float *posicion_x, float *posicion_y, 
						float *puntos, float *combustible,
						float *velocidad_x, float *velocidad_y, float *angulo,
						const size_t tam_caracteres, const diccionario_t caracteres[], SDL_Renderer *renderer);

#endif // _TERRENO_H_