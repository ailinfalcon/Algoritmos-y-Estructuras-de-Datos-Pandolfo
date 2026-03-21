#include "split.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

size_t contar_palabras(char *texto, char separador)
{
	if (strlen(texto) == 0) {
		return 0;
	}

	size_t contador = 1;
	for (int i = 0; texto[i] != '\0'; i++){
		if(texto[i] == separador){
			contador += 1;
		}
	}

	return contador;
}

int longitud_palabra(char *texto, char separador, int posicion)
{
	int contador = 0;
	while(texto[posicion] != separador && texto[posicion] != '\0'){
		contador += 1;
		posicion += 1;
	}

	return contador;
}

char * separar_palabra(char *texto, char separador, int *posicion)
{
	if(texto[*posicion] == separador){
		*posicion += 1;
	}

	int longitud = longitud_palabra(texto, separador, *posicion);
	char* palabra = malloc((longitud + 1)*sizeof(char));

	for(int i = 0; i < longitud; i++){
		palabra[i] = texto[*posicion];
		*posicion += 1;
	}

	palabra[longitud] = '\0';
	longitud ++;

	return palabra;
}

struct vector *split(char *texto, char separador)
{
	size_t cantidad_palabras = contar_palabras(texto, separador);
	char **palabras = malloc((cantidad_palabras + 1)*sizeof(char*));

	int posicion = 0;
	for (int i = 0; i < cantidad_palabras; i++){
		palabras[i] = separar_palabra(texto, separador, &posicion);
	}

	struct vector *v = malloc(sizeof(struct vector));
	v->cantidad = cantidad_palabras;
	v->palabras = palabras;

	return v;
}

void vector_destruir(struct vector *v)
{
	for(int i = 0; i < v->cantidad; i++){
		free(v->palabras[i]);
	}

	free(v->palabras);
	free(v);
}