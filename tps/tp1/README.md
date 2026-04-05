# TP1

## Información del estudiante

* Ailin Falcón
* 112231
* afalcon@fi.uba.ar

## Índice
* [1. Instrucciones](#1-Instrucciones)
  * [1.1. Compilar el proyecto](#11-Compilar-el-proyecto)
  * [1.2. Ejecutar proyecto](#12-Ejecutar-proyecto)
  * [1.3. Acciones posibles](#13-Ejecutar-el-programa-con-Valgrind)
  * [1.4. Ejecutar el programa con Valgrind](#14-Ejecutar-el-programa-con-Valgrind)
  * [1.5. Compilar pruebas](#15-Compilar-pruebas)
  * [1.6. Ejecutar pruebas](#16-Ejecutar-pruebas)
  * [1.7. Ejecutar pruebas con Valgrind](#13-Ejecutar-pruebas-con-Valgrind)
* [2. Funcionamiento](#2-Funcionamiento)
* [3. Estructura](#3-Estructura)
  * [3.1. Diagrama de memoria](#31-Diagrama-de-memoria)
  * [3.2. Análisis de complejidades](#32-Análisis-de-complejidades)
* [4. Decisiones de diseño y/o complejidades de implementación](#4-Decisiones-de-diseño-yo-complejidades-de-implementación)
* [5. Respuestas a las preguntas teóricas](#5-Respuestas-a-las-preguntas-teóricas)

## 1. Instrucciones

### 1.1. Compilar el proyecto
```bash
 gcc main.c src/tp1.c ../tp0/src/split.c -o main
```

### 1.2. Ejecutar proyecto
```bash
./main archivo acción
```

### 1.3. Acciones posibles:

  - **./tp1 pokedex.csv buscar pikachu**: Busca un pokemon con el nombre pikachu y muestra sus datos por pantalla.
  - **./tp1 pokedex.csv mostrar nombre**: Muestra todos los pokemon por orden alfabetico.
  - **./tp1 pokedex.csv mostrar tipo**: Muestra todos los pokemon ordenados por tipo.

### 1.4. Ejecutar el programa con Valgrind
```bash
valgrind --leak-check=full ./main archivo accion
```

### 1.5. Compilar pruebas
```bash
gcc pruebas/pruebas_alumno.c  src/tp1.c ../tp0/src/split.c -o tp1
```

### 1.6. Ejecutar pruebas
```bash
./tp1
```

### 1.7. Ejecutar pruebas con Valgrind
```bash
valgrind --leak-check=full ./tp1
```

## 2. Funcionamiento

### `tp1_leer_archivo:` 
Lee el archivo CSV linea por linea y guarda los pokemones en una estructura `'tp1_t'`, verifica que el pokemon no exista dentro de la misma y lo guarda, pero no verifica que los datos sean inválidos. Al finalizar, devuelve un puntero a la estructura `'tp1_t'` o `NULL` si no se pudo leer correctamente el archivo.
<div align="left">
  <img src="img/diagrama de flujo_leer archivo.svg" width="100%">
  <p>Diagrama de flujo tp1_leer_archivo</p>
</div>


`leer_linea_completa:`
<div align="left">
  <img src="img/diagrama de flujo_leer linea completa.svg" width="100%">
</div>


`existe_pokemon:`
<div align="left">
  <img src="img/diagrama de flujo_existe pokemon.svg" width="80%">
</div>


`guardar_pokemon:`
<div align="left">
  <img src="img/diagrama de flujo_guardar pokemon.svg" width="80%">
</div>


### `tp1_guardar_archivo:` 
Guarda todos los pokemones de la estructura `tp1_t` pasada por parámetro en un archivo también pasado por parámetro, de manera tal que tp1_leer_archivo pueda leerlo correctamente. Devuelve NULL en caso de error, o en caso contrario devuelve `tp1_t`.

<div align="left">
  <img src="img/diagrama de flujo_guardar archivo.svg" width="100%">
  <p>Diagrama de flujo tp1_guardar_archivo</p>
</div>


### `tp1_filtrar_tipo:`
Ordena y filtra los pokemones del tp según el tipo recibido por parámetro. En caso de error devuelve NULL, en caso contrario devuelve una nueva estructura tp solamente con los pokemones filtrados.

<div align="left">
  <img src="img/diagrama de flujo_filtrar tipo.svg" width="100%">
  <p>Diagrama de flujo tp1_filtrar_tipo</p>
</div>



### `tp1_buscar_nombre:` 
Busca el nombre recibido por parámetro dentro de los pokemones del tp, también recibido por parámetro, con busqueda binaria. En caso de error, o no encontrarlo devuelve NULL.

<div align="left">
  <img src="img/diagrama de flujo_buscar nombre.svg" width="80%">
  <p>Diagrama de flujo tp1_buscar_nombre</p>
</div>


`ordenar_pokemones:`
<div align="left">
  <img src="img/diagrama de flujo_ordenar pokemones.svg" width="100%">
</div>



### `tp1_buscar_orden:`
Busca el pokemon numero n recibido por parámetro dentro de los pokemones del tp también recibido por parámetro, que están ordenados alfábeticamente. En caso de ingresar un número negativo o mayor igual a la cantidad de pokemones que contiene el tp, devuelve NULL. Si no hay errores devuelve `struct pokemon`.

<div align="left">
  <img src="img/diagrama de flujo_con cada pokemon.svg" width="100%">
  <p>Diagrama de flujo tp1_buscar_orden</p>
</div>



### `tp1_destruir:` 
Libera la memoria reservada para el tp, el vector de pokemones, cada pokemon y su nombre.

<div align="left">
  <img src="img/diagrama de flujo_destruir tp.svg" width=100%">
  <p>Diagrama de flujo tp1_destruir</p>
</div>


## 3. Estructura
Para implementar la estructura `'tp1_t'` decidí definir un campo llamado `pokemones`, que es un vector de `struct pokemones`, para guardar todos lo pokemones que contiene el archivo. Además agrege un campo `cantidad_pokemones` que me facilita el manejo de memoria y la implementación de las funciones de `tp1.h`.

### 3.1. Diagrama de memoria
Realizar un diagrama de memoria de la estructura de memoria durante la ejecución del programa, esto debe incluir el stack y el heap con las estructuras contenidas en ellos.

<div align="center">
  <img src="img/diagrama de memoria.svg" width="70%">
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
