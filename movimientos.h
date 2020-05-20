#ifndef _MOVIMIENTOS_H_
#define _MOVIMIENTOS_H_

#include <stdio.h>
#include <math.h>
#include "config.h"

//FUNCIONES UTILIZADAS PARA MOVER LA NAVE--------------------------------------------------------------------------
//MOVIMIENTOS.C

//dada la velocidad actual vi, la aceleración a y el paso temporal dt devuelva la velocidad del próximo instante.
float computar_velocidad(float vi, float a, float dt);

//dada la posición actual pi, la velocidad actual vi y el paso temporal dt devuelva la posición del próximo instante.
float computar_posicion(float p,float vi,float dt);

//dado un vector de n coordenadas modifique cada una de sus componentes mediante la adición del par (dx, dy).
void trasladar_vector(float **v, size_t n, float dx, float dy);

//dado un vector de n coordenadas rote cada una de ella un angulo(en radianes) con respecto al origen de coordenadas.
void rotar_vector(float **v, size_t n, float angulo);

//Función utilizada para chequear que la nave no se vaya de los límites de la pantalla (mundo cilindrico)
void verificar_limites_pantalla(float *posicion_x);

//Inicializa las variables de la nave, utilizada al principio y en cada nueva partida.
void inicializar_valores(float *posicion_x, float *posicion_y, float *velocidad_x, float *velocidad_y, float *angulo, float *potencia, float *x_anterior);

//Se modifican los parametros de la nave en cada iteración segun las teclas que se hayan presionado.
void modificar_parametros_nave(float *x_anterior, float *posicion_x, float *posicion_y, float *velocidad_y, float *velocidad_x, float *angulo, float *dt, float *potencia);


#endif // _MOVIMIENTOS_H_