#include "solucion.h"
/*
 * Se devuelve la cantidad de elementos válidos que el string posee
 * o -1 si no se encuentra el caracter '\0' en el vector
 */
int longitud_string(char string[MAX_STRING]){
        int longitud = 0;

        int i = 0;

        if (string[i] == '\0') {
                return -1;
        }

        while (string[i] != '\0') {
            longitud += 1;
            i++;
        }

        return longitud;
}