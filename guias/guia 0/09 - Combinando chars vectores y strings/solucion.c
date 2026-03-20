#include "solucion.h" 
#include <stdio.h>

#define PRIMER_STRING 'C'
#define TERCER_STRING 'S'

char ejercicio(char string1[MAX_STRING], char string2[MAX_STRING], char string3[MAX_STRING]){
        strcat(string1, string2);
        int resultado = strcmp(string1, string3);

        if (resultado <= 0){
            return PRIMER_STRING;
        } else {
            return TERCER_STRING;
        }
}