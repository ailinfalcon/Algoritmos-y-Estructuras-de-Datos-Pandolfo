#include "src/tp1.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define CANTIDAD_ARGUMENTOS 4
#define ERROR -1;

#define BUSCAR "buscar"
#define MOSTRAR "mostrar"
#define BLANCO "\x1b[37;1m"
#define VERDE "\x1b[32;1m"
#define ROJO "\x1b[31;1m"
#define AMARILLO "\x1b[33;1m"
#define NORMAL "\x1b[0m"

/**
 * Devuelve true si el comando recibido es válido, false en caso contrario.
 */
bool es_comando_valido(const char *comando){
	if(strcmp(comando, BUSCAR) == 0){
		return true;
	} else if(strcmp(comando, MOSTRAR) == 0){
		return true;
	}

	return false;
}

/**
 * Devuelve 'tipo_pokemon' convertido en string, en caso de recibir un tipo inválido devuelve un string inválido.
 */
char *pasar_a_char(enum tipo_pokemon tipo){
    switch(tipo){
        case TIPO_ELEC:
            return "ELÉCTRICO";
        case TIPO_FUEG: 
        return "FUEGO";
        case TIPO_PLAN:
        return "PLANTA";
        case TIPO_AGUA:
            return "AGUA";
        case TIPO_NORM:
            return "NORMAL";
        case TIPO_FANT:
            return "FANTASMA";
        case TIPO_PSI:
            return "PSIQUICO";
        case TIPO_LUCH: 
            return "LUCHA";
        default:
        return "";
    }
}

/**
 * Convierte en minúscula el string pasado por párametro.
 */
char * pasar_a_minuscula(char *nombre){
	for(int i = 0; i < strlen(nombre); i++){
		nombre[i] = tolower(nombre[i]);
	}

	return nombre;
}

/**
 * Convierte en mayúscula el string pasado por párametro.
 */
char * pasar_a_mayuscula(char * nombre){
	for(int i = 0; i < strlen(nombre); i++){
		nombre[i] = toupper(nombre[i]);
	}

	return nombre;
}

/**
 * Imprime por pantalla la información del pokemon recibido por parámetro.
 */
void imprimir_informacion_pokemon(struct pokemon *pokemon){
	printf(BLANCO "\n	-------------------------------\n");
	printf(ROJO "	       %s              \n\n", pasar_a_mayuscula(pokemon->nombre));
	printf(VERDE "	       TIPO: %s              \n", pasar_a_char(pokemon->tipo));
	printf(AMARILLO "	       ATAQUE: %d            \n", pokemon->ataque);
	printf("	       DEFENSA: %d           \n", pokemon->defensa);
	printf("	       VELOCIDAD: %d         \n", pokemon->velocidad);
	printf(BLANCO"	-------------------------------\n" NORMAL);
}


/**
 * Muestra por pantalla la información relacionada al nombre del pokemon recibido por parámetro.
 */
void ejecutar_comando_buscar(tp1_t *tp, const char *nombre){
	struct pokemon *pokemon = tp1_buscar_nombre(tp, pasar_a_minuscula((char*)nombre));
	if(pokemon){
		imprimir_informacion_pokemon(pokemon);
	} else {
		printf("El pokemon no existe\n");
	}
}

/**
 * Muestra por pantalla todos lo pokemones existentes, ordenados por orden alfabético (menor a mayor), 
 * y su información completa.
 */
void ejecutar_comando_mostrar_nombre(tp1_t *tp){
	for(int i = 0; i < tp1_cantidad(tp); i++){
		struct pokemon *pokemon =  tp1_buscar_orden(tp, i);
		imprimir_informacion_pokemon(pokemon);
	}
}


/** 
 * Filtra los pokemones según el tipo recibido por parámetro e imprime su información por pantalla. 
*/
void imprimir_tipo(tp1_t *tp, enum tipo_pokemon tipo){
	tp1_t *tp_filtrado = tp1_filtrar_tipo(tp, tipo);
	int cantidad = tp1_cantidad(tp_filtrado);

	if(cantidad == 0){
		tp1_destruir(tp_filtrado);
		return;
	}
	
	for(int i = 0; i < cantidad; i++){
		struct pokemon *pokemon = tp1_buscar_orden(tp_filtrado, i);
		imprimir_informacion_pokemon(pokemon);
	}

	printf("\n");

	tp1_destruir(tp_filtrado);
}

/**
 * Muestra los pokemones de cada tipo válido.
 */
void ejecutar_comando_mostrar_tipo(tp1_t *tp){
	imprimir_tipo(tp, TIPO_ELEC);
	imprimir_tipo(tp, TIPO_FUEG);
	imprimir_tipo(tp, TIPO_PLAN);
	imprimir_tipo(tp, TIPO_AGUA);
	imprimir_tipo(tp, TIPO_NORM);
	imprimir_tipo(tp, TIPO_FANT);
	imprimir_tipo(tp, TIPO_PSI);
	imprimir_tipo(tp, TIPO_LUCH);
}

/**
 * Ejecuta el comando 'mostrar' según el parámetro recibido.
 */
void ejecutar_comando_mostrar(tp1_t *tp, const char *param){
	if(strcmp(param, "nombre") == 0){
		ejecutar_comando_mostrar_nombre(tp);
	} else if(strcmp(param, "tipo") == 0){
		ejecutar_comando_mostrar_tipo(tp);
	}
}

/**
 * Procesa el comándo, lo válida y según lo recibido lo ejecuta.
 */
void procesar_comando(tp1_t *tp, const char *comando, const char *param){
	if(!es_comando_valido(comando)){
		printf("El comando es inválido\n");
		return;
	}

	if(strcmp(BUSCAR, comando) == 0){
		ejecutar_comando_buscar(tp, param);
	} else if(strcmp(MOSTRAR, comando) == 0){
		ejecutar_comando_mostrar(tp, param);
	}
}

int main(int argc, const char *argv[]){
	if(argc < CANTIDAD_ARGUMENTOS){
		printf("Cantidad incorrecta de argumentos\n");
		return ERROR;
	}

	const char *nombre_archivo = argv[1];

	tp1_t *tp = tp1_leer_archivo(nombre_archivo);
	if(!tp){
		printf("Error en la lectura del archivo\n");
		return -1;
	}

	const char *comando = argv[2];
	const char *parametro = argv[3];

	procesar_comando(tp, comando, parametro);

	tp1_destruir(tp);

	return 0;
}
