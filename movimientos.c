#include "movimientos.h"

float computar_velocidad(float vi, float a, float t){
    return vi + t*a;
}

float computar_posicion(float p,float vi,float t){
    return p + t*vi;
}

void trasladar_vector(float **v, size_t n, float dx, float dy){
	for (int i = 0; i < n; i++) {
		v[i][0] += dx;
		v[i][1] += dy;
	}
}

void rotar_vector(float **v, size_t n, float angulo){
	
	float c = cos(angulo);
	float s = sin(angulo);
	float xs, yc, xc, ys;
	
	for (int i = 0; i < n ; i++) {
	
		xs = v[i][0]*s;
		yc = v[i][1]*c;
		xc = v[i][0]*c;
		ys = v[i][1]*s;	

		v[i][1] = xs + yc;
		v[i][0] = xc - ys;
	}
}

void verificar_limites_pantalla(float *posicion_x){
	if(*posicion_x >= VENTANA_ANCHO)
		*posicion_x = 10;
				
	if(*posicion_x <= 0)
		*posicion_x = VENTANA_ANCHO-10;
}

//void inicializar_variables(float posicion_x, float posicion_y, float velocidad_x, float velocidad_y, float angulo, float x_anterior){}
void inicializar_valores(float *posicion_x, float *posicion_y, float *velocidad_x, float *velocidad_y, float *angulo, float *potencia, float *x_anterior){
	
	*potencia = (float) NAVE_POTENCIA_INICIAL;
	*posicion_x = (float) NAVE_X_INICIAL;
	*posicion_y = (float) NAVE_Y_INICIAL;
	*velocidad_x = (float) NAVE_VX_INICIAL;
	*velocidad_y = (float) NAVE_VY_INICIAL;
	*angulo = (float) NAVE_ANGULO_INICIAL;
	*x_anterior = 0;
}

void modificar_parametros_nave(float *x_anterior, float *posicion_x, float *posicion_y, float *velocidad_y, float *velocidad_x, float *angulo, float *dt, float *potencia){
			
			*x_anterior = *posicion_x;
			
			*velocidad_y = computar_velocidad(*velocidad_y, -(float)G + *potencia*cos(*angulo), *dt);
			*velocidad_x = computar_velocidad(*velocidad_x, *potencia*sin(-*angulo), *dt);

			*posicion_y = computar_posicion(*posicion_y, *velocidad_y, *dt);
			*posicion_x = computar_posicion(*posicion_x, *velocidad_x, *dt);
}