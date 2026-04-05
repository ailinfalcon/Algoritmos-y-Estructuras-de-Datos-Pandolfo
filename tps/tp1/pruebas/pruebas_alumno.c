#include "pa2m.h"
#include "../src/tp1.h"
#include <stdio.h>
#include <string.h>

#define ARCHIVO_PRUEBA "pokemones.csv"
#define ARCHIVO_PRUEBA_GRANDE "pokemones-35.csv"
#define ARCHIVO_VACIO "pokemones-vacio.csv"
#define ARCHIVO_RESULTADO "resultado.csv"

#define MODO_LECTURA "r"

void probar_tp1_lectura_archivo_null(){
	tp1_t *tp1 = tp1_leer_archivo(NULL);
	pa2m_afirmar(tp1 == NULL, "Abrir un archivo NULL devuelve NULL");
}

void probar_tp1_lectura_archivo_no_null(){
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_PRUEBA);
	pa2m_afirmar(tp1 != NULL, "Abrir un archivo no NULL devuelve TP1");
	tp1_destruir(tp1);
}

void probar_tp1_lectura_archivo_vacio(){
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_VACIO);
	pa2m_afirmar(tp1 != NULL, "Abrir un archivo vacio no devuelve NULL");
	tp1_destruir(tp1);
}

void probar_tp1_agrandar_bloque(){
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_PRUEBA_GRANDE);
	pa2m_afirmar(tp1 != NULL, "El bloque de memoria se agranda correctamente");
	tp1_destruir(tp1);
} 

void probar_tp1_guardar_archivo_null_devuelve_null(){
	tp1_t *tp = tp1_leer_archivo(ARCHIVO_PRUEBA);

	tp1_t *tp1 = tp1_guardar_archivo(tp, NULL);
	pa2m_afirmar(tp1 == NULL, "Recibe un archivo NULL y devuelve NULL");
	tp1_destruir(tp);

	tp1_t *tp2 = tp1_guardar_archivo(NULL, NULL);
	pa2m_afirmar(tp2 == NULL, "Recibe NULL y devuelve NULL");
}

void probar_tp1_guardar_archivo_valido(){
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_PRUEBA);
	tp1_t *tp_resultado = tp1_guardar_archivo(tp1, ARCHIVO_RESULTADO);

	pa2m_afirmar(tp_resultado != NULL, "Recibe un tp y devuelve tp");

	tp1_destruir(tp1);
}

void probar_tp1_filtrar_tipo_null(){
	tp1_t *tp1_filtrado = tp1_filtrar_tipo(NULL, TIPO_ELEC);
	pa2m_afirmar(tp1_filtrado == NULL, "Recibe un tp1 NULL y devuelve NULL");
	tp1_destruir(tp1_filtrado);
}

void probar_tp1_filtrar_tipo_cantidad_correcta(){
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_PRUEBA);

	tp1_t *tp1_filtrado_agua = tp1_filtrar_tipo(tp1, TIPO_AGUA);
	int cantidad_filtrada_agua = tp1_cantidad(tp1_filtrado_agua);
	int cantidad_esperada_agua = 1;

	tp1_t *tp1_filtrado_norm = tp1_filtrar_tipo(tp1, TIPO_NORM);
	int cantidad_filtrada_norm = tp1_cantidad(tp1_filtrado_norm);
	int cantidad_esperada_norm = 3;


	pa2m_afirmar(cantidad_filtrada_agua == cantidad_esperada_agua, "La cantidad de pokemones filtradas es la esperada. (obtenida: %d, esperada: %d)", cantidad_filtrada_agua, cantidad_esperada_agua);
	pa2m_afirmar(cantidad_filtrada_norm == cantidad_esperada_norm, "La cantidad de pokemones filtradas es la esperada. (obtenida: %d, esperada: %d)", cantidad_filtrada_norm, cantidad_esperada_norm);

	tp1_destruir(tp1_filtrado_norm);
	tp1_destruir(tp1_filtrado_agua);
	tp1_destruir(tp1);
}

/**
 * 
 */
char *pasar_a_char(enum tipo_pokemon tipo){
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

void probar_tp1_buscar_nombre_no_existe(){
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_PRUEBA_GRANDE);
	char *nombre = "Dratini";
	struct pokemon *pokemon = tp1_buscar_nombre(tp1, nombre);
	pa2m_afirmar(pokemon == NULL, "Buscar un nombre no existente devuelve NULL");
	tp1_destruir(tp1);
}

void probar_tp1_buscar_nombre(){
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_PRUEBA_GRANDE);
	char *nombre = "pikachu";
	struct pokemon *pokemon = tp1_buscar_nombre(tp1, nombre);

	int ataque_esperado = 55;
	int defensa_esperada = 40;
	int velocidad_esperada = 90;

	if(pokemon){
		pa2m_afirmar(strcmp(pokemon->nombre, nombre) == 0, "El nombre del pokemon es %s", pokemon->nombre);
		pa2m_afirmar(pokemon->tipo == TIPO_ELEC, "El tipo es el esperado. (obtenido: %s, esperado: %s)", pasar_a_char(pokemon->tipo), pasar_a_char(TIPO_ELEC));
		pa2m_afirmar(pokemon->ataque == ataque_esperado, "El ataque es el esperado. (obtenido: %d, esperado: %d)", pokemon->ataque, ataque_esperado);
		pa2m_afirmar(pokemon->defensa == defensa_esperada, "La defensa es la esperada. (obtenido: %d, esperado: %d)", pokemon->defensa, defensa_esperada);
		pa2m_afirmar(pokemon->velocidad == velocidad_esperada, "La velocidad es la esperada. (obtenido: %d, esperado: %d)", pokemon->velocidad, velocidad_esperada);
	}

	tp1_destruir(tp1);
}

void probar_tp1_buscar_orden_mayor_a_cantidad_pokemones(){
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_PRUEBA_GRANDE);
	int n = 30;

	struct pokemon *pokemon = tp1_buscar_orden(tp1, 30);
	pa2m_afirmar(pokemon == NULL, "No debería poder buscar un orden mayor a la cantidad de pokemones");
	tp1_destruir(tp1);
}

void probar_tp1_buscar_orden_negativo(){
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_PRUEBA_GRANDE);
	int n = -4;

	struct pokemon *pokemon = tp1_buscar_orden(tp1, n);
	pa2m_afirmar(pokemon == NULL, "No debería poder buscar un orden negativo de pokemones");
	tp1_destruir(tp1);
}

void probar_tp1_buscar_orden_valido(){
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_PRUEBA);
	int n = 5;

	struct pokemon *pokemon = tp1_buscar_orden(tp1, n);
	char *nombre_esperado = "machop";
	int ataque_esperado = 80;
	int defensa_esperada = 50;
	int velocidad_esperada = 35;

	if(pokemon){
		pa2m_afirmar(strcmp(pokemon->nombre, nombre_esperado) == 0, "El nombre del pokemon es correcto. (obtenido: %s, esperado: %s)", pokemon->nombre, nombre_esperado);
		pa2m_afirmar(pokemon->tipo == TIPO_LUCH, "El tipo es el esperado. (obtenido: %s, esperado: %s)", pasar_a_char(pokemon->tipo), pasar_a_char(TIPO_LUCH));
		pa2m_afirmar(pokemon->ataque == ataque_esperado, "El ataque es el esperado. (obtenido: %d, esperado: %d)", pokemon->ataque, ataque_esperado);
		pa2m_afirmar(pokemon->defensa == defensa_esperada, "La defensa es la esperada. (obtenido: %d, esperado: %d)", pokemon->defensa, defensa_esperada);
		pa2m_afirmar(pokemon->velocidad == velocidad_esperada, "La velocidad es la esperada. (obtenido: %d, esperado: %d)", pokemon->velocidad, velocidad_esperada);
	}

	tp1_destruir(tp1);
}

bool velocidad_mayor_a_n(struct pokemon *pokemon, void *n){
	if(!pokemon || !n){
		return false;
	}

	return pokemon->velocidad > *((int*)n);
}

void probar_tp1_con_cada_pokemon_funcion_null(){
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_PRUEBA);
	int n = 15;

	pa2m_afirmar(tp1_con_cada_pokemon(NULL, velocidad_mayor_a_n, &n) == -1, "Recibe tp NULL, devuelve cantidad = -1 (obtenido: %d)", tp1_con_cada_pokemon(NULL, velocidad_mayor_a_n, &n));
	pa2m_afirmar(tp1_con_cada_pokemon(tp1, NULL, &n) == -1, "Recibe funcion NULL, devuelve cantidad = -1 (obtenido: %d)", tp1_con_cada_pokemon(tp1, NULL, &n));

	tp1_destruir(tp1);
}

void probar_tp1_con_cada_pokemon(){
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_PRUEBA);
	int n = 10;

	int cantidad_pokemones_aplicada = tp1_con_cada_pokemon(tp1, velocidad_mayor_a_n, &n);
	int cantidad_esperada = 7;
	pa2m_afirmar(cantidad_pokemones_aplicada == cantidad_esperada, "La cantidad de pokemones a los que se le aplicó la función es correcta. (obtenida: %d, esperada: %d)", cantidad_pokemones_aplicada, cantidad_esperada);

	tp1_destruir(tp1);
}

void pruebas_unitarias_tp1_leer_archivo()
{
	probar_tp1_lectura_archivo_null();
	probar_tp1_lectura_archivo_no_null();
	probar_tp1_lectura_archivo_vacio();
	probar_tp1_agrandar_bloque();
}

void pruebas_unitarias_tp1_guardar_archivo(){
	probar_tp1_guardar_archivo_null_devuelve_null();
	probar_tp1_guardar_archivo_valido();
}

void pruebas_unitarias_tp1_filtrar_tipo(){
	probar_tp1_filtrar_tipo_null();
	probar_tp1_filtrar_tipo_cantidad_correcta();
}

void pruebas_unitarias_tp1_buscar_nombre(){
	probar_tp1_buscar_nombre_no_existe();
	probar_tp1_buscar_nombre();
}

void pruebas_unitarias_tp1_buscar_orden(){
	probar_tp1_buscar_orden_mayor_a_cantidad_pokemones();
	probar_tp1_buscar_orden_negativo();
	probar_tp1_buscar_orden_valido();
}

void pruebas_unitarias_tp1_con_cada_pokemon(){
	probar_tp1_con_cada_pokemon_funcion_null();
	probar_tp1_con_cada_pokemon();
}

/**
 * Main: Conjunto de grupos de pruebas
 */

int main()
{
	pa2m_nuevo_grupo("============== PRUEBAS DEL TP1 ===============");

	pa2m_nuevo_grupo("Pruebas de tp1_leer_archivo");
	pruebas_unitarias_tp1_leer_archivo();

	pa2m_nuevo_grupo("Pruebas de tp1_guardar_archivo");
	pruebas_unitarias_tp1_guardar_archivo();

	pa2m_nuevo_grupo("Pruebas de tp1_filtrar_tipo");
	pruebas_unitarias_tp1_filtrar_tipo();
	
	pa2m_nuevo_grupo("Pruebas de tp1_buscar_nombre");
	pruebas_unitarias_tp1_buscar_nombre();

	pa2m_nuevo_grupo("Pruebas de tp1_buscar_orden");
	pruebas_unitarias_tp1_buscar_orden();

	pa2m_nuevo_grupo("Pruebas de tp1_con_cada_pokemon");
	pruebas_unitarias_tp1_con_cada_pokemon();

	return pa2m_mostrar_reporte();
}
