# Simulador de Sistema de Recuperación de Información

Este proyecto implementa un **simulador de un sistema de recuperación de información**, utilizando estructuras de datos como grafos, listas enlazadas y tablas hash. El sistema combina dos técnicas principales: **índice invertido** y **PageRank**, para gestionar datos de manera eficiente.

## Resumen

El simulador permite:  
- Construir un grafo dirigido que representa la conexión entre documentos.
- Crear un índice invertido que facilita búsquedas rápidas por términos en los documentos.
- Calcular la relevancia de los documentos mediante el algoritmo de PageRank.
- Realizar búsquedas de términos con resultados ordenados por relevancia.

Este trabajo fue programado en **C**.

## Características

- **Generación automática de documentos simulados.**  
  Se crean archivos de texto con contenido generado dinámicamente.

- **Construcción de un grafo dirigido.**  
  Cada documento es un nodo, y los enlaces entre ellos representan las conexiones.  

- **Índice invertido para búsquedas eficientes.**  
  Permite localizar documentos que contienen un término específico.

- **Algoritmo PageRank.**  
  Calcula la importancia relativa de los documentos basándose en las conexiones entre ellos.

- **Visualización de resultados.**  
  Los resultados de PageRank y las búsquedas se imprimen en consola.  

## Uso del Programa

Antes de ejecutar el programa, es necesario compilarlo y prepararlo mediante las siguientes instrucciones en la línea de comandos:  

## Compilación del proyecto

1. **Compilación del programa**:  
   Ejecute el comando `make` en el directorio raíz del proyecto. Esto utilizará el `Makefile`.

   `make`

2. **Ejecución del programa**
    Ahora, una vez hecho el `make`, debe ejecutar `make run`, que tiene definido
    parametros adicionales (esto se encuentra en el Makefile), estos parametros adicionales
    nos permiten colocar la cantidad `-d` y una ayuda del programa `-h`.

## Generación de documentación con Doxygen

1. **Generar la documentación**

    Ejecute el comando `make dxygn` en el directorio raíz del proyecto para generar la documentación automática en formato HTML y LaTeX.

2. **Compilar en formato PDF**

    Una vez generados los archivos con Doxygen, puede convertir la documentación en un archivo PDF utilizando LaTeX. Para hacerlo, ejecute  `make ltx`.

3.  **Ubicación del archivo PDF**

    El archivo PDF generado estará disponible en el directorio docs/latex/ o en la ubicación configurada en el `Makefile`.

4. **Visualización de la documentación HTML**

    Los archivos HTML generados se encontrarán en el directorio docs/html/. Para visualizar la documentación, abra el archivo index.html con su navegador.

## Opción de vista adicional

1. Dentro del programa, hay una vista adicional que permite   visualizar las palabras almacenadas en el índice invertido, junto con la cantidad de veces que se repiten. Esto se puede lograr mediante la función `print_inverted_index(index);`. Idealmente, esta función puede añadirse antes o después de la función print_search_word.

## Stopwords

1. En el programa se utilizan palabras comunes que no aportan significado relevante para la búsqueda y el cálculo de PageRank. Estas palabras son conocidas como stopwords y son excluidas en el proceso. Las stopwords son las siguientes: "a", "e", "i", "o", "u", "link".

## Salida del programa

Al ejecutar `make run`, el programa generará una salida en consola que incluye:

- El **índice invertido** construido, mostrando en qué documentos se encuentra cada palabra.
- El **grafo de enlaces**, indicando cómo están conectados los documentos entre sí.
- Los valores de **PageRank** calculados para cada documento, reflejando su relevancia.
