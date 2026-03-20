#include "solucion.h"


pokemon_t pokemon_con_mas_victorias(pokemon_t pokemones[MAX_VECTOR], int tope_vector){
        pokemon_t pokemon;
        strcpy(pokemon.nombre, pokemones[0].nombre);
        pokemon.victorias = pokemones[0].victorias;

        for (int i = 1; i < tope_vector; i++){
                if (pokemones[i].victorias > pokemon.victorias) {
                        strcpy(pokemon.nombre, pokemones[i].nombre);
                        pokemon.victorias = pokemones[i].victorias;
                } else if (pokemones[i].victorias == pokemon.victorias){
                        if (strcmp(pokemones[i].nombre, pokemon.nombre) < 0){
                                strcpy(pokemon.nombre, pokemones[i].nombre);
                                pokemon.victorias = pokemones[i].victorias;
                        }
                }
        }


        return pokemon;
}