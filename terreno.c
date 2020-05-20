#include "terreno.h"
#include "vectores.h"

#define COLUMNAS 2
#define PI 3.14159265358979323846


float generar_x(float **v, size_t nv){
	
	float xmax = v[nv - 1][0];
	float xmin = v[0][0];

	return rand() % (int)((xmax - xmin) + 1) + xmin;
}



int buscar_intervalo(float **v, float x, size_t nv){

	int i;

	for (i = 0; i < nv-1; i++) { 
		
		if(x > v[i][0] && x < v[i+1][0])
			return i;

	}

	return EXIT_FAILURE;
}


float buscar_yrecta(float xmin, float xmax, float ymin,float ymax, float xrandom){

	float pendiente, ordenada;

	pendiente = (ymax - ymin) / (xmax - xmin);
	ordenada = ymax - pendiente * xmax;

	return pendiente * xrandom + ordenada;
}


float generar_y(float yrecta, float margen){
	float maximo= yrecta + margen;
	float minimo= yrecta - margen;

	return (float)(rand()%(int)( (maximo - minimo) + 1) + minimo);
}


float **agregar_datos_random(float **v, size_t nv, size_t nn, float margen){

	float xmin, xmax, ymin, ymax,yrecta;
	size_t posicion;

	for(size_t i = nv; i < nn; i++){
		
		v[i][0] = generar_x(v, nv);

		posicion = buscar_intervalo(v, v[i][0], nv);
		
		xmin = v[posicion][0];
		ymin = v[posicion][1];
		xmax = v[posicion +1][0];
		ymax = v[posicion +1][1];

		yrecta = buscar_yrecta(xmin, xmax, ymin,ymax, v[i][0]);


		v[i][1] = generar_y(yrecta, margen);

	}

	return v;
}



float **densificar_vector(float **v, size_t nv, size_t nn, float margen){
	
	float **aux = NULL;
	
	if(!(aux = crear_vector(nn)))
		return NULL;

	//copio los valores de v a aux:
	copiar_valores_a_vector(aux, v, nv);

	agregar_datos_random(aux, nv, nn, margen);

	ordenar_v(aux, nn);
	
	return aux;	
}


float ** crear_terreno(size_t * n){
	* n = 0;

	const float terreno_estatico [][2] = {
		{0 , 100} ,							//izquierda
		{ -1 , VENTANA_ALTO * 2.0 / 4} ,	//"medio"
		{ VENTANA_ANCHO , 100}				//derecha
	};

	size_t nt = 3;
	float **terreno = matriz_a_vector(terreno_estatico , nt);
	if ( terreno == NULL ) return NULL ;

	// Asignamos la coordenada del medio aleatoriamente :
	terreno [1][0] = rand () % VENTANA_ANCHO;

	// Iterativamente densificamos 30 veces achicando el margen cada vez :
	for (size_t i = 1; i < 20; i ++) {
		float ** aux = densificar_vector(terreno, nt , 2 * ( i + 5) , 100 / i);
		destruir_vector(terreno , nt);
		if ( aux == NULL ) return NULL ;
		terreno = aux;
		nt = 2 * ( i + 5);
	}

	* n = nt ;
	return terreno ;
}


bool llego_al_terreno(float **terreno, size_t n, float posicion_x, float posicion_y){

	for(size_t i = 0; i < n-1; i++){

		float xmin = 0, ymin = 0, xmax = 0, ymax = 0, yrecta = 0;
		size_t posicion;
		
		//Dada la posicion_x busca entre que intervalos de x de las coordenadas del terreno esta
		posicion = buscar_intervalo(terreno, posicion_x, n);
		
		xmin = terreno[posicion][0];
		ymin = terreno[posicion][1];
		xmax = terreno[posicion +1][0];
		ymax = terreno[posicion +1][1];

		//segun la posicion obtenida anteriormente me devuelve si la posicion_y 
		//esta en la recta que une esos puntos o no(llego al terreno)
		yrecta = buscar_yrecta(xmin, xmax, ymin,ymax, posicion_x);

		if(posicion_y <= yrecta){
			return true;
		}

		return false;
	}
	return false;
}

float distancia_al_terreno(float **terreno, size_t tam_terreno, float posicion_x, float posicion_y){
	
	float xmin = 0, ymin = 0, xmax = 0, ymax = 0, yrecta = 0;
	size_t posicion;
		
	//Dada la posicion_x busca entre que intervalos de x de las coordenadas del terreno esta
	posicion = buscar_intervalo(terreno, posicion_x, tam_terreno);
		
	xmin = terreno[posicion][0];
	ymin = terreno[posicion][1];
	xmax = terreno[posicion +1][0];
	ymax = terreno[posicion +1][1];

	//segun la posicion obtenida anteriormente me devuelve si la posicion_y 
	//esta en la recta que une esos puntos o no(llego al terreno)
	yrecta = buscar_yrecta(xmin, xmax, ymin,ymax, posicion_x);

	float altitud = posicion_y - yrecta;
	
	return altitud;
}

void analizar_aterrizaje(float *posicion_x, float *posicion_y, 
						float *puntos, float *combustible,
						float *velocidad_x, float *velocidad_y, float *angulo,
						const size_t tam_caracteres, const diccionario_t caracteres[], SDL_Renderer *renderer){

	float vx_modulo = fabs(*velocidad_x);
	float vy_modulo =fabs(*velocidad_y);
	float angulo_modulo = fabs(*angulo);
				
	if( vx_modulo < 1 && vy_modulo < 10 && angulo_modulo < 0.01){
	 	puntos += 50;
	 	SDL_SetRenderDrawColor(renderer, 0x00, 0x50, 0x00, 0x00);
	 	dibujar_palabra(MSJ_LANDED, caracteres, tam_caracteres, VENTANA_ANCHO/3, VENTANA_ALTO/3, ESCALA_MSJ,renderer);
	}
		else if( vx_modulo< 2 && vy_modulo < 20 && angulo_modulo < 0.01){
		 	*puntos += 15;
		 	SDL_SetRenderDrawColor(renderer, 0x50, 0x50, 0x00, 0x00);
		 	dibujar_palabra(MSJ_LANDED_HARD, caracteres, tam_caracteres, VENTANA_ANCHO/3, VENTANA_ALTO/3, ESCALA_MSJ,renderer);
		}
		else{
			*puntos += 5;
			*combustible -= 250;
			SDL_SetRenderDrawColor(renderer, 0x50, 0x00, 0x00, 0x00);
			dibujar_palabra(MSJ_DESTROYED, caracteres, tam_caracteres, 350, VENTANA_ALTO/3, ESCALA_MSJ,renderer);
		}
}
			

			