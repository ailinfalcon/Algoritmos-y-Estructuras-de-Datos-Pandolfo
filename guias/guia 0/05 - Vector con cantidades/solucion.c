#include "solucion.h"


/*
 * Se recibe un vector con las características mencionadas en el ejercicio y su tope.
 * También se recibe un segundo vector, que utilizaremos para almacenar el número de entrenador que posee más de la cantidad mínima de pokemones (pasada por parámetro).
 */
int entrenadores_con_cantidad_pokemones(int entrenadores_y_pokemones[MAX_ENTRENADORES], int tope, int cantidad_pokemones, int entrenadores_con_pokemones[MAX_ENTRENADORES]) {
        int cantidad_entrenadores = 0;
        for (int i = 0; i < tope - 1; i++){
                int pokemones = entrenadores_y_pokemones[i + 1];
                int entrenador = entrenadores_y_pokemones[i];

                if (pokemones > cantidad_pokemones){
                        entrenadores_con_pokemones[cantidad_entrenadores] = entrenador;
                        cantidad_entrenadores ++;
                }
        } 

        return cantidad_entrenadores;
}