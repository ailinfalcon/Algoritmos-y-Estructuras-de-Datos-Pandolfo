#include "split.h"
#include <stdlib.h>
#include <string.h>

/**
 * Cuenta la cantidad de palabras de un string delimitadas por un separador específico
*/
unsigned int contar_palabras(char *texto, char separador)
{
	unsigned int contador = 1;
	for (int i = 0; texto[i] != '\0'; i++) {
		if (texto[i] == separador) {
			contador++;
		}
	}

	return contador;
}

/**
 * Calcula la longitud de la palabra delimitada por el separador.
*/
size_t longitud_palabra(char *texto, char separador, int posicion)
{
	size_t contador = 0;
	while (texto[posicion] != separador && texto[posicion] != '\0') {
		contador++;
		posicion++;
	}

	return contador;
}

/**
 * Copia caracter por caracter desde la posición recibida por párametro hasta encontrar un separador o '\0' y devuelve un string.
*/
char *separar_palabra(char *texto, char separador, int *posicion)
{
	size_t longitud = longitud_palabra(texto, separador, *posicion);
	char *palabra = malloc((longitud + 1) * sizeof(char));

	for (int i = 0; i < longitud; i++) {
		palabra[i] = texto[*posicion];
		(*posicion)++;
	}

	palabra[longitud] = '\0';
	longitud++;

	if (texto[*posicion] == separador) {
		(*posicion)++;
	}

	return palabra;
}

/**
 * Divide un texto en palabras utilizando un separador específico.
 * 
 * Por ejemplo, si el texto es "Hola;1;2;3;mundo" y el separador es ';',
 * la función devolverá un vector con las palabras ["Hola", "1", "2", "3", "mundo"].
 */
struct vector *split(char *texto, char separador)
{
	if (texto == NULL) {
		return NULL;
	}

	unsigned int cantidad_palabras = contar_palabras(texto, separador);
	char **palabras = malloc((cantidad_palabras + 1) * sizeof(char *));
	struct vector *v = malloc(sizeof(struct vector));

	int posicion = 0;
	for (int i = 0; i < cantidad_palabras; i++) {
		palabras[i] = separar_palabra(texto, separador, &posicion);
	}

	v->cantidad = cantidad_palabras;
	v->palabras = palabras;

	return v;
}

/**
 * Libera la memoria utilizada por el vector de palabras.
 */
void vector_destruir(struct vector *v)
{
	for (int i = 0; i < v->cantidad; i++) {
		free(v->palabras[i]);
	}

	free(v->palabras);
	free(v);
}