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
Para implementar la estructura `'tp1_t'` decidí definir dos vectores de `struct pokemon`, uno llamado `pokemones` que mantiene el orden original de los pokemones, y otro `pokemones_ordenados` que tiene los pokemones ordenados alfábeticamente. Ambos vectores me facilitan la implementación de las funciones de la biblioteca. Además agregue un campo `cantidad_pokemones` que me facilita el manejo de memoria y la implementación de la función `tp1_cantidad`.

### 3.1. Diagrama de memoria
Realizar un diagrama de memoria de la estructura de memoria durante la ejecución del programa, esto debe incluir el stack y el heap con las estructuras contenidas en ellos.

<div align="center">
  <img src="img/diagrama de memoria.svg" width="70%">
  <p>Diagrama de memoria de la estructura.</p>
</div>

### 3.2. Análisis de complejidades

- `tp1_leer_archivo`: $O(n)$. Esta complejidad se obtiene por que se utiliza la función `leer_linea_completa` que es O(m), siendo m la cantidad de caracteres de la linea y siendo k la cantidad de lineas del archivo, queda O(m * k), como m*k es una constante, tomando n = m * k, queda O(n).
- `tp1_cantidad`: Es $O(1)$. La estructura `tp1_t` tiene un campo llamado `cantidad_pokemones` que me permite acceder en tiempo $O(1)$.
- `tp1_guardar_archivo`: Es $O(n)$. Esta función depende de la cantidad de pokemones (n) que contenga la estructura `tp1_t`, ya que se recorre pokemon por pokemon y se guarda en el archivo.
- `tp1_filtrar_tipo`: Es $O(n)$. La función recorre todos los pokemones que contenga la estructura `tp1_t` y compara con el tipo a filtrar. En el peor de los casos, recorro todos los elementos ya que todos cumplen con el requisito.
- `tp1_buscar_nombre`: Es $O(log n)$. Esto se obtiene por que se utiliza el campo `pokemones_ordenados` de la estructura `tp1_t` en la función `buscar_nombre_bb` que utiliza búsqueda binaria, que es $O(log(n))$.
- `tp1_buscar_orden`: Es $O(1)$. Esto se obtiene por que se utiliza el campo `pokemones_ordenados` de la estructura `tp1_t` y se devuelve el pokemon dentro del vector ordenado en la posicion recibida por parámetro.
- `tp1_con_cada_pokemon`: $O(n)$. Esto se obtiene por que recorro todos los pokemones del vector de pokemones de la estructura `tp1_t` hasta que la función pasada por parámetro me de false o haya recorrido todos los pokemones. Entonces, en el peor de los casos, recorro todos los pokemones.
- `tp1_destruir`: $O(n)$. Recorro el vector de pokemones liberando la memoria reservada para cada uno y su nombre, esto es $O(n)$. Una vez liberada esa memoria, libero la memoria reservada para el vector de pokemones, y finalmente la reservada para la estructura `tp1_t`

## 4. Decisiones de diseño y/o complejidades de implementación (EJEMPLO)
Para la estructura `tp1_t` decidi definir un campo `struct pokemon **pokemones_ordenados` que me facilita las funciones `tp1_buscar_nombre`, `tp1_buscar_orden` y `tp1_con_cada_pokemon`, en las cuales necesito tener los pokemones ordenados alfábeticamente. Además, tener el orden original de los pokemones, me permitió desarrollar con más facilidad la función `tp1_guardar_archivo`.

## 5. Respuestas a las preguntas teóricas

### 5.1. Explicar la elección de la estructura para implementar la funcionalidad pedida. Justifique el uso de cada uno de los campos de la estructura.
Respondido en su respectiva sección.
### 5.2 Dar una definición de complejidad computacional y explique cómo se calcula.
La complejidad computacional permite analizar y determinar cuantos recursos computacionales consume cierto algoritmo. AL hablar de recursos, se hace referencia a tiempo o espacio que el algoritmo necesita y utiliza durante su ejecución. La complejidad computacional, sirve para determinar y comparar algoritmos para saber cúal será mejor en la resolución de un problema. 

Para calcular la complejidad se deben contabilizar las instrucciones ejecutadas:
Para las iteraciones, el tiempo de ejecución es: tiempo de ejecución de las instrucción dentro de la iteración * la cantidad de iteraciones.
Para las iteraciones anidadas, se deben analizar de adentro hacia afuera, el tiempo de una instrucción dentro de un iteración anidada será: tiempo de la instrucción * cantidad iteraciones de cada iteracion.
Para las condionales, el tiempo nuna será: mayor al tiempo de ejecución de la condición + el mayor tiempo entre las instrucciones de cada condicional.

Para algoritmos recursivos, se utiliza el teorema maestro: T(n) = AT(n/B) + f(n)
DOnde A es la cantidad de llamados recursivos ejecutados, B es cuanto se divide el problema en cada llamado recursivo y f(n) es el costo de dividir y combinarlo.

### 5.3 Explicar con diagramas cómo quedan dispuestas las estructuras y elementos en memoria.
Respondido en su respectiva sección.

### 5.4 Justificar la complejidad computacional temporal de **cada una** de las funciones que se piden implementar.
Respondido en su respectiva sección.

### 5.5 Explique qué dificultades tuvo para implementar las funcionalidades pedidas en el main (si tuvo alguna) y explique si alguna de estas dificultades se podría haber evitado modificando la definición del .h
No tuve dificultades para implementar el main.