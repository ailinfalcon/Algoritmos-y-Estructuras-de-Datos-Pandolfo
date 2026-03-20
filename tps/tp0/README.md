<div align="right">
    <img width="32px" src="img/algo2.svg">
</div>

# TP

## Información del estudiante

* Ailin Sofía Falcon
* 112231
* afalcon@fi.uba.ar

---

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
comando
```

### 1.2. Ejecutar las pruebas
```bash
comando
```

### 1.3. Ejecutar el programa con Valgrind
```bash
comando
```

## 2. Funcionamiento
El programa recibe un string y un separador especifíco, y separa las palabras delimitadas por el separador. Para esto, se crea un vector de strings, donde se guarda cada palabra encontrada dentro del string recibido. 

Para separar las palabras del texto recibido, se recorre el string, primero desde el comienzo, y luego a partir del ultimo separador encontrado y se guarda la palabra delimitada por el separador en un nuevo string. 

Cuando se terminan de insertar todas las palabras dentro del vector de strings, se define un struct que contiene la cantidad de palabras y el vector de strings.

<div align="center">
  <img src="img/diagrama_flujo_programa.svg" width="70%">
  <p>Diagrama de flujo del programa explicado con más detalle.</p>
</div>

## 3. Estructura
La estructura proporcionada tiene un vector de strings, donde se guardan las palabras que se separan del string recibido, además tiene un campo llamado 'cantidad' que permite guardar la cantidad de palabras, para luego reservar memoria que se utiliza en el vector de strings. 

### 3.1. Diagrama de memoria

<div align="center">
  <img src="img/diagrama_memoria.png" width="70%">
  <p>Diagrama de memoria de la estructura.</p>
</div>

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
