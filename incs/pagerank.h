#ifndef PAGERANK_H
#define PAGERANK_H

#include "graph.h"

/* Funciones de PageRank */
void initialize_pagerank(double *, int);
void calculate_pagerank(Graph *, double *);
void display_pagerank(Graph *, double *);

#endif // PAGERANK_H
