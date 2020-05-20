#include "renderizar.h"



void dibujar_vector(float **vector, size_t tam_vector, float escala, SDL_Renderer *renderer){
	
	for(int i = 0; i < tam_vector - 1; i++)
					SDL_RenderDrawLine(
						renderer,
						vector[i][0] * escala,
						-vector[i][1] * escala + VENTANA_ALTO,
						vector[i+1][0] * escala,
						-vector[i+1][1] * escala + VENTANA_ALTO
					);	
			
}

void dibujar_caracter(char letra, const diccionario_t caracteres[], size_t tam, SDL_Renderer *renderer, float x, float y, float escala){
	
	caracteres_t caracter = buscar_matriz_caracter(letra, caracteres, tam);
	size_t tam_filas = buscar_filas_caracter(letra, caracteres, tam);

		for(int i = 0; i < tam_filas - 1; i++){
			SDL_RenderDrawLine(
						renderer,
						caracter[i][0] * escala + x,
						-caracter[i][1] * escala + y,
						caracter[i+1][0] * escala + x,
						-caracter[i+1][1] * escala + y
					);	
		}					
}

void dibujar_palabra(char cadena[], const diccionario_t caracteres[], size_t tam, float x_inicial, float y_inicial, float escala, SDL_Renderer *renderer){
	
	size_t tam_cadena = strlen(cadena);
	size_t i;

	for(i = 0; i < tam_cadena; i++)
		dibujar_caracter(cadena[i], caracteres, tam, renderer, x_inicial + i*escala*CARACTER_ANCHO, y_inicial, escala);
}


void dibujar_parametros(float puntos, float tiempo, float combustible, 
						float posicion_x, float posicion_y, 
						float velocidad_y, float velocidad_x, float x_anterior,
						const diccionario_t caracteres[], size_t tam, 
						SDL_Renderer *renderer){

	char aux[30];

	//SCORE
	sprintf(aux, "SCORE %04.f",puntos);
	dibujar_palabra(aux, caracteres, tam_caracteres, COLUM_1, FILA_1, ESCALA_LETRA , renderer);

	//TIME
	sprintf(aux, "TIME  %04.f", tiempo);
	dibujar_palabra(aux, caracteres, tam_caracteres, COLUM_1, FILA_2, ESCALA_LETRA , renderer);

	//FUEL
	sprintf(aux, "FUEL  %04.f", combustible);
	dibujar_palabra(aux, caracteres, tam_caracteres, COLUM_1, FILA_3, ESCALA_LETRA , renderer);
			

	//ALTITUDE
	sprintf(aux, "ALTITUDE         %04.f", posicion_y);
	dibujar_palabra(aux, caracteres, tam_caracteres, COLUM_2, FILA_1, ESCALA_LETRA , renderer);
			
	//VERTICAL SPEED
	sprintf(aux, "VERTICAL SPEED   %04.f", fabs(velocidad_y));
	dibujar_palabra(aux, caracteres, tam_caracteres, COLUM_2, FILA_2, ESCALA_LETRA , renderer);
	if(velocidad_y < 0){
		dibujar_palabra("v", caracteres, tam_caracteres, COLUM_3, FILA_2, ESCALA_FLECHA , renderer);
	}else{
		dibujar_palabra("^", caracteres, tam_caracteres, COLUM_3, FILA_2, ESCALA_FLECHA , renderer);
		}
		
	//HORIZONTAL SPEED
	sprintf(aux, "HORIZONTAL SPEED %04.f", fabs(velocidad_x));
	dibujar_palabra(aux, caracteres, tam_caracteres, COLUM_2, FILA_3, ESCALA_LETRA , renderer);
	if(x_anterior < posicion_x){
		dibujar_palabra(">", caracteres, tam_caracteres, COLUM_3, FILA_3, ESCALA_FLECHA , renderer);
	}else{
		dibujar_palabra("<", caracteres, tam_caracteres, COLUM_3, FILA_3, ESCALA_FLECHA , renderer);
		}

}

