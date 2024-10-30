# Search Simulator 💻🔍

Este repositorio contiene el desarrollo de un **simulador de búsqueda de archivos** utilizando **estructuras de datos avanzadas** para la recuperación de información.

## 👨‍💻 Desarrollado por:

### 1. Diego Sanhueza 🙋‍♂️
- Estudiante de Ingeniería Infomatica
- [Diego Sanhueza](https://github.com/Diego0119)

### 2. Miguel Loaiza 👨‍💻
- Estudiante de Ingeniería Informatica
- [Miguel Loaiza](https://github.com/EhMigueh)

### 3. Felipe Carcamo 🙋
- Estudiante de Ingeniería Informatica
- [Felipe Carcamo](https://github.com/FeLipe-133)

### 4. Miguel 🤔
- Estudiante de Ingeniería Informatica
- [Miguel Malipillan](https://github.com/mihel1)
---

## Objetivo

El objetivo de este proyecto es implementar un sistema avanzado de recuperación de información, integrando dos técnicas clave en el manejo de datos estructurados: **el índice invertido** y **el algoritmo PageRank**. Con este proyecto, buscamos comprender en profundidad los mecanismos de los motores de búsqueda modernos.

## Descripción del Proyecto

Este simulador de búsqueda simplificado indexará un conjunto de documentos web que contienen enlaces entre ellos, simulando hipervínculos. El proyecto se divide en dos componentes principales:

1. **Índice Invertido:** Implementación de un índice invertido para realizar búsquedas rápidas de palabras clave en los documentos.
2. **PageRank:** Uso de un grafo para modelar las relaciones entre documentos mediante enlaces. Se implementará el algoritmo de PageRank para calcular la importancia de cada documento en la web, y se mostrarán los resultados en orden de relevancia.

---

## Funcionalidades

### 1. Carga de Documentos
   - Los documentos estarán en archivos de texto plano y contendrán enlaces a otros documentos, representados como `link: docN`.
   - El sistema procesará estos documentos para extraer palabras clave y construir el grafo de enlaces.

### 2. Construcción del Índice Invertido
   - Cada palabra relevante en el documento (excluyendo "stopwords" comunes) se añadirá al índice invertido con su ID de documento.
   - Al realizar una consulta, el sistema devolverá los documentos que contienen la palabra clave.

### 3. Construcción del Grafo y Cálculo de PageRank
   - El sistema construirá un grafo dirigido donde cada documento es un nodo, y cada enlace entre documentos es una arista.
   - Implementación del algoritmo de **PageRank** para calcular la importancia de cada documento, considerando enlaces entrantes y salientes.

### 4. Búsqueda y Ordenación de Resultados
   - Al realizar una búsqueda, los documentos que contienen la palabra clave serán recuperados del índice invertido.
   - Los resultados estarán ordenados de acuerdo con el puntaje de PageRank, mostrando primero los documentos más relevantes.

---

## Requisitos del Proyecto

- **Estructuras de Datos:**
  - Implementación del índice invertido usando **listas enlazadas** o **tablas hash**.
  - Representación del grafo mediante **listas de adyacencia**.
- **Algoritmos:**
  - Implementación del algoritmo de **PageRank** en iteraciones, usando un factor de amortiguación (damping factor).
  - Algoritmos de búsqueda eficientes en el índice invertido.
- **Resultados:**
  - El sistema mostrará una lista de documentos ordenados por relevancia para una palabra o frase dada.
