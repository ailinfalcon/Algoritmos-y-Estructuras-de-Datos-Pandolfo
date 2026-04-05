# TP1

## Información del estudiante

* Ailin Falcón
* 112231
* afalcon@fi.uba.ar

## Índice
* [1. Instrucciones](#1-Instrucciones)
  * [1.1. Compilar el proyecto](#11-Compilar-el-proyecto)
  * [1.2. Ejecutar las pruebas](#12-Ejecutar-las-pruebas)
  * [1.3. Ejecutar el programa con Valgrind](#13-Ejecutar-el-programa-con-Valgrind)
* [2. Funcionamiento](#2-Funcionamiento)
* [3. Estructura](#3-Estructura)
  * [3.1. Diagrama de memoria](#31-Diagrama-de-memoria)
  * [3.2. Análisis de complejidades](#32-Análisis-de-complejidades)
* [4. Decisiones de diseño y/o complejidades de implementación](#4-Decisiones-de-diseño-yo-complejidades-de-implementación)
* [5. Respuestas a las preguntas teóricas](#5-Respuestas-a-las-preguntas-teóricas)

## 1. Instrucciones

> [!TIP]
> Se recomienda usar un Makefile y colocar en esta sección los comandos Make.

### 1.1. Compilar el proyecto
```bash
 gcc main.c src/tp1.c ../tp0/src/split.c -o main
```

### 1.2. Ejecutar las pruebas
```bash
gcc pruebas/pruebas_alumno.c  src/tp1.c ../tp0/src/split.c -o tp1
```

### 1.3. Ejecutar el programa con Valgrind
```bash
valgrind --leak-check=full ./main
```

## 1.4. Acciones posibles que se pueden realizar:

  - **./tp1 pokedex.csv buscar pikachu**: Busca un pokemon con el nombre pikachu y muestra sus datos por pantalla.
  - **./tp1 pokedex.csv mostrar nombre**: Muestra todos los pokemon por orden alfabetico.
  - **./tp1 pokedex.csv mostrar tipo**: Muestra todos los pokemon ordenados por tipo.

## 2. Funcionamiento

### `tp1_leer_archivo:` 
Lee el archivo CSV linea por linea y guarda los pokemones en una estructura `'tp1_t'`, verifica que el pokemon no exista dentro de la misma y lo guarda, pero no verifica que los datos sean inválidos. Al finalizar, devuelve un puntero a la estructura `'tp1_t'` o `NULL` si no se pudo leer correctamente el archivo.
<div align="center">
  <img src="img/diagrama de flujo_leer archivo.svg" width="100%">
  <p>Diagrama de flujo tp1_leer_archivo</p>
</div>


`leer_linea_completa:`
<div align="center">
  <img src="img/diagrama de flujo_leer linea completa.svg" width="100%">
</div>


`existe_pokemon:`
<div align="center">
  <img src="img/diagrama de flujo_existe pokemon.svg" width="80%">
</div>


`guardar_pokemon:`
<div align="center">
  <img src="img/diagrama de flujo_guardar pokemon.svg" width="80%">
</div>


### `tp1_guardar_archivo:` 
Guarda todos los pokemones de la estructura `tp1_t` pasada por parámetro en un archivo también pasado por parámetro, de manera tal que tp1_leer_archivo pueda leerlo correctamente. Devuelve NULL en caso de error, o en caso contrario devuelve `tp1_t`.

<div align="center">
  <img src="img/diagrama de flujo_guardar archivo.svg" width="100%">
  <p>Diagrama de flujo tp1_guardar_archivo</p>
</div>


### `tp1_filtrar_tipo:` 

<div align="center">
  <img src="img/diagrama de flujo_filtrar tipo.svg" width="100%">
  <p>Diagrama de flujo tp1_filtrar_tipo</p>
</div>



### `tp1_buscar_nombre:` 

<div align="center">
  <img src="img/diagrama de flujo_buscar nombre.svg" width="80%">
  <p>Diagrama de flujo tp1_buscar_nombre</p>
</div>


`ordenar_pokemones:`
<div align="center">
  <img src="img/diagrama de flujo_ordenar pokemones.svg" width="100%">
</div>



### `tp1_buscar_orden:` 

<div align="center">
  <img src="img/diagrama de flujo_con cada pokemon.svg" width="80%">
  <p>Diagrama de flujo tp1_buscar_orden</p>
</div>



### `tp1_destruir:` 

<div align="center">
  <img src="img/diagrama de flujo_destruir tp.svg" width=100%">
  <p>Diagrama de flujo tp1_destruir</p>
</div>


## 3. Estructura
Explicar cómo se implementó la/s estructura/s pedida/s en el [enunciado](./ENUNCIADO.md). En esta sección el objetivo es explicar en líneas generales, no técnicas, qué contiene la estructura, para qué y por qué.

## 3. Estructura (EJEMPLO)
Para implementar la estructura decidí hacerlo con un campo..., además tiene un puntero que... y eso permite que....

### 3.1. Diagrama de memoria
Realizar un diagrama de memoria de la estructura de memoria durante la ejecución del programa, esto debe incluir el stack y el heap con las estructuras contenidas en ellos.

### 3.1 Diagrama de memoria (EJEMPLO)
<div align="center">
  <img src="img/diagrama_memoria__1.svg" width="70%">
  <p>Diagrama de memoria de la estructura.</p>
</div>

### 3.2. Análisis de complejidades (EJEMPLO 2)
|      Función      |Complejidad|                 Justificación                  |
|:-----------------:|:---------:|:----------------------------------------------:|
|      `fun1`       |  $O(1)$   |Tiene como parámetro... y, al leer una línea....|
|      `fun2`       |  $O(n)$   |Tiene como parámetro..., la cual....            |
|      `fun3`       |  $O(n^2)$ |Tiene como parámetro... y se encarga de....     |

## 4. Decisiones de diseño y/o complejidades de implementación
Explicar las decisiones de diseño y/o las complejidades de implementación que hubo durante la resolución del TP.

## 4. Decisiones de diseño y/o complejidades de implementación (EJEMPLO)
La mayor complejidad en el TP se encuentra en la función `foo` que requiere hacer...; es por esto que decidí.... Además, decidí que el programa haga... para mejorar la implementación.

## 5. Respuestas a las preguntas teóricas
Deberás incluir en esta sección las respuestas a las preguntas teóricas indicadas en el [enunciado](./ENUNCIADO.md) del TP.

## 5. Respuestas a las preguntas teóricas (EJEMPLO)

### 5.1. ¿Porqué...?
Respondido en su respectiva sección.

### 5.2 ¿Cómo...?
Para implementar el....

### 5.3 ¿Cuál fue el...?
El motivo fue....
