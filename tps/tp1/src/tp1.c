#include "tp1.h"
#include "../../tp0/src/split.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MODO_LECTURA "r"
#define MODO_ESCRITURA "w"
#define FORMATO_ESCRITURA "%s,%s,%d,%d,%d\n"

#define TAMANIO_INICIAL 10
#define TIPO_INVALIDO -1
#define ERROR -1

#define POSICION_NOMBRE 0
#define POSICION_TIPO 1
#define POSICION_ATAQUE 2
#define POSICION_DEFENSA 3
#define POSICION_VELOCIDAD 4


struct tp1 {
    int cantidad_pokemones;
    struct pokemon **pokemones;
};

/**
 * Lee una línea hasta encontrar '\n' del archivo pasado por párametro. Devuelve NULL en caso de error o EOF.
 */
char *leer_linea_completa(FILE *archivo){
    char *linea = malloc(TAMANIO_INICIAL*sizeof(char));
    if(!linea){
        return NULL;
    }

    char *leida = fgets(linea, TAMANIO_INICIAL, archivo);
    if(!leida){
        free(linea);
        return NULL;
    }

    size_t leido = strlen(leida);

    char *linea_completa = malloc(TAMANIO_INICIAL * sizeof(char));
    if(!linea_completa){
        free(linea);
        return NULL;
    }

    strcpy(linea_completa, leida);

    size_t i = 2;

    while(leida[leido - 1] != '\n'){
        leida = fgets(linea, TAMANIO_INICIAL, archivo);
        if(!leida){
            free(linea_completa);
            free(linea);
            return NULL;
        }

        leido = strlen(leida);

        void* nuevo = realloc(linea_completa, TAMANIO_INICIAL * i * sizeof(char));
        if(!nuevo){
            free(linea_completa);
            free(linea);
            return NULL;
        }

        linea_completa = nuevo;

        strcat(linea_completa, leida);
        i++;
    }

    free(linea);
    return linea_completa;
}

/**
 * Devuelve true si el pokemon existe, o false en caso contrario.
 */
bool existe_pokemon(struct pokemon **pokemones, int cantidad, char *pokemon){
    for(int i = 0; i < cantidad; i++){
        if(strcmp(pokemones[i]->nombre, pokemon) == 0){
            return true;
        }
    }

    return false;
}

/**
 * Devuelve el tipo de pokemon recibido en string como 'tipo_pokemon'.
 * Si no existe devuelve -1.
 */
enum tipo_pokemon definir_tipo_pokemon(char *tipo){
    if(strcmp(tipo, "ELEC") == 0){ 
        return TIPO_ELEC; 
    } else if(strcmp(tipo, "FUEG") == 0){ 
        return TIPO_FUEG; 
    } else if(strcmp(tipo, "PLAN") == 0){ 
        return TIPO_PLAN; 
    } else if(strcmp(tipo, "AGUA") == 0){ 
        return TIPO_AGUA; 
    } else if(strcmp(tipo, "NORM") == 0){ 
        return TIPO_NORM; 
    } else if(strcmp(tipo, "FANT") == 0){ 
        return TIPO_FANT; 
    } else if(strcmp(tipo, "PSI") == 0){ 
        return TIPO_PSI; 
    } else if(strcmp(tipo, "LUCH") == 0){ 
        return TIPO_LUCH; 
    }

    return TIPO_INVALIDO;
}

/**
 * Convierte en minúscula el string pasado por párametro.
 */
char * pasar_a_minus(char *nombre){
	for(int i = 0; i < strlen(nombre); i++){
		nombre[i] = tolower(nombre[i]);
	}

	return nombre;
}

/**
 * Guarda los datos del pokemon (nombre, tipo, ataque, defensa y velocidad) en un struct pokemon. 
 * Devuelve 0 si se guardo con éxito, -1 en caso de error.
 */

int guardar_pokemon(struct pokemon **pokemones, int i, char *nombre_pokemon, char *tipo, int ataque, int defensa, int velocidad){
    pokemones[i] = malloc(sizeof(struct pokemon));
    if(!pokemones[i]){
        return ERROR;
    }

    size_t longitud_nombre = strlen(nombre_pokemon);

    pokemones[i]->nombre = malloc((longitud_nombre + 1)*sizeof(char));
    if(!pokemones[i]->nombre){
        free(pokemones[i]);
        return ERROR;
    }

    strcpy(pokemones[i]->nombre, pasar_a_minus(nombre_pokemon));
    pokemones[i]->tipo = definir_tipo_pokemon(tipo);
    pokemones[i]->ataque = ataque;
    pokemones[i]->defensa = defensa;
    pokemones[i]->velocidad = velocidad;

    return 0;
}

/**
 * Ordena los pokemones por orden alfabético (de menor a mayor) según el nombre.
 */
void ordenar_pokemones(struct pokemon **pokemones, int cantidad_pokemones){
    int i, j, minimo;
    struct pokemon *tmp;

    for(i = 0; i < (cantidad_pokemones - 1); i++){
        minimo = i;

        for(j = i + 1; j < cantidad_pokemones; j++){
            if(strcmp(pokemones[minimo]->nombre, pokemones[j]->nombre) > 0){
                minimo = j;
            }
        }

        tmp = pokemones[i];
        pokemones[i] = pokemones[minimo];
        pokemones[minimo] = tmp;
    }
}

/**
 * Lee el archivo indicado y devuelve la estructura tp1 con los pokemones.
 * En caso de error devuelve NULL.
*/
tp1_t *tp1_leer_archivo(const char *nombre){
    if(!nombre){
        return NULL;
    }

    FILE* archivo = fopen(nombre, MODO_LECTURA);
    if(!archivo){
        return NULL;
    }

    tp1_t *tp1 = malloc(sizeof(tp1_t));
    if(!tp1){
        fclose(archivo);
        return NULL;
    }

    struct pokemon **pokemones = malloc(TAMANIO_INICIAL*sizeof(struct pokemon*));
    if(!pokemones){
        free(tp1);
        fclose(archivo);
        return NULL;
    }

    int cantidad_pokemones = 0;
    char * leida = leer_linea_completa(archivo);

    size_t tamanio_bloque = TAMANIO_INICIAL;

    while(leida){
        if(cantidad_pokemones == tamanio_bloque){
            tamanio_bloque = tamanio_bloque * 2;
            void* nuevo_bloque = realloc(pokemones, tamanio_bloque * sizeof(struct pokemon*));

            if(!nuevo_bloque){
                free(pokemones);
                free(leida);
                tp1_destruir(tp1);
                fclose(archivo);
                return NULL;
            }

            pokemones = nuevo_bloque;
        }

        struct vector *vector = split(leida, ',');
        char *nombre_pokemon = vector->palabras[POSICION_NOMBRE];

        if(!existe_pokemon(pokemones, cantidad_pokemones, nombre_pokemon)){
            int retorno = guardar_pokemon(pokemones, cantidad_pokemones, nombre_pokemon, vector->palabras[POSICION_TIPO], atoi(vector->palabras[POSICION_ATAQUE]), atoi(vector->palabras[POSICION_DEFENSA]), atoi(vector->palabras[POSICION_VELOCIDAD]));

            if(retorno != 0){
                free(pokemones);
                free(leida);
                tp1_destruir(tp1);
                fclose(archivo);
                return NULL;
            }

            cantidad_pokemones++;
        }

        vector_destruir(vector);
        free(leida);
        leida = leer_linea_completa(archivo);
    }

    free(leida);
    tp1->cantidad_pokemones = cantidad_pokemones;
    tp1->pokemones = pokemones;

    fclose(archivo);

    return tp1;
}

/**
 * Devuelve la cantidad de pokemones leidos correctamente.
 * En caso de error devuelve 0.
 */
size_t tp1_cantidad(tp1_t *tp1){
    if(!tp1){
        return ERROR;
    }

    return tp1->cantidad_pokemones;
}

/**
 * Devuelve 'tipo_pokemon' convertido en string. En caso de error, devuelve un string vacio.
 */
char *pasar_tipo_a_string(enum tipo_pokemon tipo){
    switch(tipo){
        case TIPO_ELEC:
            return "ELEC";
        case TIPO_FUEG: 
        return "FUEG";
        case TIPO_PLAN:
        return "PLAN";
        case TIPO_AGUA:
            return "AGUA";
        case TIPO_NORM:
            return "NORM";
        case TIPO_FANT:
            return "FANT";
        case TIPO_PSI:
            return "PSI";
        case TIPO_LUCH: 
            return "LUCH";
        default:
        return "";
    }
}

/**
 * Guarda en el archivo indicado los pokemones contenidos en la estructura tp1 
 * de manera tal que tp1_leer_archivo pueda volver a leerlo correctamente.
 *
 * Devuelve NULL en caso de error o el tp1 pasado por parámetro en caso de exito.
 */
 tp1_t *tp1_guardar_archivo(tp1_t *tp1, const char *nombre){
    if(!nombre){
        return NULL;
    }

    FILE *archivo = fopen(nombre, MODO_ESCRITURA);
    if(!archivo){
        return NULL;
    }

    if(!tp1){
        fclose(archivo);
        return NULL;
    }
    
    for(int i = 0; i < tp1->cantidad_pokemones; i++){
        fprintf(archivo, FORMATO_ESCRITURA, tp1->pokemones[i]->nombre, pasar_tipo_a_string(tp1->pokemones[i]->tipo), tp1->pokemones[i]->ataque, tp1->pokemones[i]->defensa, tp1->pokemones[i]->velocidad);
    }
    
    fclose(archivo);
    
    return tp1;
}

/**
* Dado un tp1 y un tipo, devuelve otro tp1 conteniendo solamente los pokemons de dicho tipo.
*
* En caso de error devuelve NULL.
*/
tp1_t *tp1_filtrar_tipo(tp1_t *un_tp, enum tipo_pokemon tipo){
    if(!un_tp){
        return NULL;
    }

    tp1_t *nuevo_tp1 = malloc(sizeof(tp1_t));
    if(!nuevo_tp1){
        return NULL;
    }
    
    int contador_pokemones = 0;
    nuevo_tp1->pokemones = malloc(un_tp->cantidad_pokemones * sizeof(struct pokemon*));
    if(!nuevo_tp1->pokemones){
        free(nuevo_tp1);
        return NULL;
    }
    
    for(int i = 0; i < un_tp->cantidad_pokemones; i++){
        if(un_tp->pokemones[i]->tipo == tipo){
            int retorno = guardar_pokemon(nuevo_tp1->pokemones, contador_pokemones, un_tp->pokemones[i]->nombre, pasar_tipo_a_string(un_tp->pokemones[i]->tipo), un_tp->pokemones[i]->ataque, un_tp->pokemones[i]->defensa, un_tp->pokemones[i]->velocidad);

            if (retorno != 0){
                free(nuevo_tp1->pokemones);
                free(nuevo_tp1);
                return NULL;
            }
            
            contador_pokemones++;
        }
    }
    
    nuevo_tp1->cantidad_pokemones = contador_pokemones;
    
    return nuevo_tp1;
}

/**
 * Busca el nombre de un pokemon pasado por parámetro con búsqueda binaria.
 */
struct pokemon *buscar_nombre_bb(tp1_t *tp, const char *nombre, int inicio, int fin){
    if(inicio > fin){
        return NULL;
    }
    
    int medio = (fin+inicio)/2;
    
    if(strcmp(nombre, tp->pokemones[medio]->nombre) == 0){
        return tp->pokemones[medio];
    } else if(strcmp(nombre, tp->pokemones[medio]->nombre) > 0){
        return buscar_nombre_bb(tp, nombre, medio + 1, fin);
    } else {
        return buscar_nombre_bb(tp, nombre, inicio, medio - 1);
    }
}

/**
* Busca un pokemon por nombre.
* En caso de no encontrarlo devuelve NULL.
*/
struct pokemon *tp1_buscar_nombre(tp1_t *tp, const char *nombre){
    if(!existe_pokemon(tp->pokemones, tp->cantidad_pokemones, (char*)nombre)){
        return NULL;
    }
    
    ordenar_pokemones(tp->pokemones, tp->cantidad_pokemones);
    return buscar_nombre_bb(tp, nombre, 0, tp->cantidad_pokemones - 1);
}


/**
* Devuelve el n-esimo pokemon por orden alfabetico (de menor a mayor).
* En caso de no encontrarlo devuelve NULL.
*/
struct pokemon *tp1_buscar_orden(tp1_t *tp, int n){
    if(n < 0){
        return NULL;
    }
    
    if (n >= tp->cantidad_pokemones){
        return NULL;
    }

    ordenar_pokemones(tp->pokemones, tp->cantidad_pokemones);
    
    return tp->pokemones[n];
}

/**
 * Aplica la función f a cada pokemon por orden alfabetico (de menor a mayor).
 * La función deja de aplicarse si f devuelve false o se terminaron los pokemones.
 * 
 * Devuelve la cantidad de pokemones sobre los cuales se aplicó la función f.
 */
 size_t tp1_con_cada_pokemon(tp1_t *un_tp, bool (*f)(struct pokemon *, void *), void *extra)
 {
    if(!un_tp || !f){
        return ERROR;
    }

    ordenar_pokemones(un_tp->pokemones, un_tp->cantidad_pokemones);
    size_t contador = 0;
    for(int i = 0; i < un_tp->cantidad_pokemones; i++){
        if(!f(un_tp->pokemones[i], extra)){
            return contador;
        }
        
        contador ++;
    }
    
    return contador;
}

/**
 * Libera toda la memoria asociada al tp1
 */
 void tp1_destruir(tp1_t *tp1){
    if(tp1 == NULL){
        return;
    }

    for(int i = 0; i < tp1->cantidad_pokemones; i++){
        free(tp1->pokemones[i]->nombre);
        free(tp1->pokemones[i]);
    }

    free(tp1->pokemones);
    free(tp1);
}