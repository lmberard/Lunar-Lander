#include "naves.h"
#include "caracteres.h"
#include "movimientos.h"
#include "vectores.h"
#include "terreno.h"
#include "diccionario.h"
#include "renderizar.h"

int main() {
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event event;

	SDL_CreateWindowAndRenderer(VENTANA_ANCHO, VENTANA_ALTO, 0, &window, &renderer);
	SDL_SetWindowTitle(window, "Lunar Lander");

	int dormir = 0;

	// BEGIN código del alumno----------------------------------------------
	// El chorro de la nave:
	const float chorro[3][2] = {
		{-NAVE_GRANDE_TOBERA_X, NAVE_GRANDE_TOBERA_Y},
		{0, NAVE_GRANDE_TOBERA_Y},
		{NAVE_GRANDE_TOBERA_X, NAVE_GRANDE_TOBERA_Y}
	};
	
	float **vector_chorro = NULL;
	size_t tam_chorro = sizeof(chorro) / sizeof(chorro[0]);

	float **vector_nave = NULL;
	size_t nave_tam = sizeof(nave_grande) / sizeof(nave_grande[0]);
/*
	float **terreno = NULL;
	size_t tam_terreno = 0;
*/
	float dt = 1/(float)JUEGO_FPS;
	float tiempo = 0;
	float puntos = 0;
	float combustible = JUEGO_COMBUSTIBLE_INICIAL;
	float angulo, velocidad_x, velocidad_y, posicion_y, posicion_x, x_anterior, potencia;
	inicializar_valores(&posicion_x, &posicion_y, &velocidad_x, &velocidad_y, &angulo, &potencia, &x_anterior);			

	/*srand(time(NULL));
	if(!(terreno = crear_terreno(&tam_terreno)))
		return EXIT_FAILURE;
*/
	// END código del alumno--------------------------------------------------
	unsigned int ticks = SDL_GetTicks();
	while(1) {
		if(SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				break;
	    		if (event.type == SDL_KEYDOWN) {
				// BEGIN código del alumno------------------------------------
				switch(event.key.keysym.sym) {
					case SDLK_UP:
						
						potencia +=3;		
						break;

					/*case SDLK_DOWN:	
						if(potencia <= NAVE_POTENCIA_INICIAL)
							break;
						potencia --;
						break;*/

					case SDLK_RIGHT:				
						angulo -= NAVE_ROTACION_PASO;
						combustible -= JUEGO_COMBUSTIBLE_RADIANES * NAVE_ROTACION_PASO;
						break;

					case SDLK_LEFT:					
						angulo += NAVE_ROTACION_PASO;
						combustible -= JUEGO_COMBUSTIBLE_RADIANES * NAVE_ROTACION_PASO;
					break;
				}
				// END código del alumno--------------------------------------------------
			}
			continue;
		}
        	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        	SDL_RenderClear(renderer);
        	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);

		// BEGIN código del alumno-------------------------------------
        	//paso la nave y el chorro a un vector dinamico
			if(!(vector_chorro = matriz_a_vector(chorro, tam_chorro)))
				return EXIT_FAILURE;
			if(!(vector_nave = matriz_a_vector(nave_grande, nave_tam)))
				return EXIT_FAILURE;

			vector_chorro[1][1] -= potencia; 
			combustible -= JUEGO_COMBUSTIBLE_POT_X_SEG *potencia *dt;

			
			if(potencia >= 15) potencia = 15;
			potencia -=potencia*0.1*dt; 


			fprintf(stderr, "Potencia: %f\n", potencia );

			rotar_vector(vector_nave, nave_tam, angulo);
			rotar_vector(vector_chorro, tam_chorro, angulo);

			modificar_parametros_nave(&x_anterior, &posicion_x, &posicion_y, &velocidad_y, &velocidad_x, &angulo, &dt, &potencia);
			verificar_limites_pantalla(&posicion_x);

			trasladar_vector(vector_nave, nave_tam, posicion_x, posicion_y);
			trasladar_vector(vector_chorro, tam_chorro, posicion_x, posicion_y);

			tiempo += dt;

			////////////////ZONA DE DIBUJO/////////////////
			dibujar_palabra("LUNAR LANDER BY LUCIA BERARD", caracteres, tam_caracteres, 400, 15, ESCALA, renderer);

			dibujar_vector(vector_nave, nave_tam, ESCALA, renderer);
			dibujar_vector(vector_chorro, tam_chorro, ESCALA, renderer);

			dibujar_parametros(puntos, tiempo, combustible, posicion_x, posicion_y/*distancia_al_terreno(terreno, tam_terreno, posicion_x, posicion_y)*/,velocidad_y, velocidad_x, x_anterior, caracteres, tam_caracteres, renderer);
			////////////////////////////////////////////////

			if(combustible <= 0){
				printf("GAME OVER\n TOTAL SCORE: %4.0f\n", puntos);
				destruir_vector(vector_chorro, tam_chorro);
				destruir_vector(vector_nave, nave_tam);
				//destruir_vector(terreno, tam_terreno);

				break;
			}
			
			destruir_vector(vector_chorro, tam_chorro);
			destruir_vector(vector_nave, nave_tam);

		// END código del alumno----------------------------------------------
        SDL_RenderPresent(renderer);
		ticks = SDL_GetTicks() - ticks;
		if(dormir) {
			SDL_Delay(dormir);

			dormir = 0;
		}
		else if(ticks < 1000 / JUEGO_FPS)
			SDL_Delay(1000 / JUEGO_FPS - ticks);
		ticks = SDL_GetTicks();
	}
	// BEGIN código del alumno------------------------------------------------

	// END código del alumno--------------------------------------------------

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
}

