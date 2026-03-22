#include "split.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

unsigned int contar_palabras(char *texto, char separador)
{
	if (strlen(texto) == 0) {
		return 0;
	}

	unsigned int contador = 1;
	for (int i = 0; texto[i] != '\0'; i++){
		if(texto[i] == separador){
			contador += 1;
		}
	}

	return contador;
}

size_t longitud_palabra(char *texto, char separador, int posicion)
{
	size_t contador = 0;
	while(texto[posicion] != separador && texto[posicion] != '\0'){
		contador += 1;
		posicion += 1;
	}

	return contador;
}

char *separar_palabra(char *texto, char separador, int *posicion)
{
	if(texto[*posicion] == separador){
		*posicion += 1;
	}

	size_t longitud = longitud_palabra(texto, separador, *posicion);
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
	unsigned int cantidad_palabras = contar_palabras(texto, separador);
	char **palabras = malloc((cantidad_palabras + 1)*sizeof(char*));

	struct vector *v = malloc(sizeof(struct vector));

	if (cantidad_palabras == 0){
		v->cantidad = cantidad_palabras;
		v->palabras = palabras;

		return v;
	}

	int posicion = 0;
	for (int i = 0; i < cantidad_palabras; i++){
		palabras[i] = separar_palabra(texto, separador, &posicion);
	}

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