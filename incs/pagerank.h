/**
 * @file pagerank.h
 * @date 18-11-2024
 * @authors Miguel Loaiza, Diego Sanhueza, Miguel Maripillan y Felipe Carcamo
 * @brief Prototipos de funciones para la creación del PageRank.
 *
 * Contiene los prototipos de las funciones dedicadas a la creación del PageRank.
 */

#ifndef PAGERANK_H
#define PAGERANK_H

#include "graph.h" ///< Incluye la definición de las estructuras y funciones del grafo.

/**
 * @brief Inicializar PageRank
 * @param pagerank Arreglo de PageRank
 * @param num_docs Número de documentos
 */
void initialize_pagerank(double *, int);

/**
 * @brief Calcular PageRank
 * @param graph Grafo
 * @param pagerank Arreglo de PageRank
 */
void calculate_pagerank(Graph *, double *);

/**
 * @brief Mostrar PageRank
 * @param graph Grafo
 * @param pagerank Arreglo de PageRank
 */
void display_pagerank(Graph *, double *);

#endif
