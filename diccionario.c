
#include "diccionario.h"
#include "caracteres.h"

//declaro un vector del tipo diccionario_t con los valores de cada caracteres
const diccionario_t caracteres[] = {
	{'A', 7, caracter_a},
	{'B', 12, caracter_b},
	{'C', 4, caracter_c},
	{'D', 7, caracter_d},
	{'E', 7, caracter_e},
	{'F', 6, caracter_f},
	{'G', 7, caracter_g},
	{'H', 6, caracter_h},
	{'I', 6, caracter_i},
	{'J', 4, caracter_j},
	{'K', 6, caracter_k},
	{'L', 3, caracter_l},
	{'M', 5, caracter_m},
	{'N', 4, caracter_n},
	{'O', 5, caracter_o},
	{'P', 5, caracter_p},
	{'Q', 9, caracter_q},
	{'R', 7, caracter_r},
	{'S', 6, caracter_s},
	{'T', 4, caracter_t},
	{'U', 4, caracter_u},
	{'V', 3, caracter_v},
	{'W', 5, caracter_w},
	{'X', 5, caracter_x},
	{'Y', 5, caracter_y},
	{'Z', 4, caracter_z},

	{'0', 5, caracter_0},
	{'1', 2, caracter_1},
	{'2', 6, caracter_2},
	{'3', 7, caracter_3},
	{'4', 5, caracter_4},
	{'5', 6, caracter_5},
	{'6', 5, caracter_6},
	{'7', 3, caracter_7},
	{'8', 7, caracter_8},
	{'9', 5, caracter_9},

	{'^', 5, caracter_arriba},
	{'v', 5, caracter_abajo},
	{'>', 5, caracter_derecha},

	{'<', 5, caracter_izquierda},

	{' ', 1, caracter_espacio}
};

const size_t tam_caracteres = sizeof(caracteres) / sizeof(caracteres[0]);

caracteres_t buscar_matriz_caracter(char letra, const diccionario_t caracteres[], size_t tam){

	size_t i;
	for (i = 0; i < tam ; i++){
		if(caracteres[i].letra == letra)
			return caracteres[i].caracter;
	}

	return caracteres[i].caracter;
}

size_t buscar_filas_caracter(char letra, const diccionario_t caracteres[], size_t tam){
	
	size_t i;
	for (i = 0; i < tam; ++i){
		if(caracteres[i].letra == letra)
			return caracteres[i].tam_filas;
	}
	return 0;
}




