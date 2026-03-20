#include "solucion.h"

/*
 * Se recibe un vector de letras, su tope y la letra a buscar.
 * Se devuelve la posición de la letra o -1 en caso de que no se encuentre.
*/
int posicion_letra(char vector[MAX_VECTOR], int tope, char letra){
        int posicion = -1;

        for (int i = 0; i < tope; i++){
                if (vector[i] == letra){
                        posicion = i;
                }
        }

        return posicion;
}