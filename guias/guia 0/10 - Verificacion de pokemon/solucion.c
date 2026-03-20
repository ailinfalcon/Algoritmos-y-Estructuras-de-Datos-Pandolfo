#include "solucion.h"
#include <stdio.h>

int verificar_pokemon(pokemon_t pokemon, char nombre[MAX_NOMBRE_POKEMON], int cantidad_victorias){
        if (strcmp(pokemon.nombre, nombre) == 0 && (pokemon.victorias == cantidad_victorias)) {
                return EXITO;
        }

        return ERROR;
}