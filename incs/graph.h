#ifndef GRAPH_H
#define GRAPH_H

/* Librerías estándar */
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <dirent.h>
#include <unistd.h>
#include <time.h>

/* Macros generales */
#define CONVERGENCE_THRESHOLD 0.0001 // Umbral de convergencia del PageRank.
#define MAX_CHARACTERS_DOC 50        // Máximo de caracteres por página.
#define DAMPING_FACTOR 0.85          // Factor de amortiguación del PageRank.
#define MAX_ITERATIONS 100           // Máximo de iteraciones del algoritmo.
#define MAX_WORD_SIZE 50             // Máximo de longitud de palabras.
#define MAX_NAME_DOC 20              // Máximo de longitud de nombres de archivos.
#define MAX_DOCS 100                 // Máximo de documentos soportados.
#define HASH_TABLE_SIZE 30           // Tamaño de la tabla hash.

/* Estructuras comunes */
typedef struct Node
{
    int doc_id;
    struct Node *next;
} Node;

typedef struct DocumentMapping
{
    char name[MAX_NAME_DOC];
    int doc_id;
} DocumentMapping;

typedef struct Graph
{
    Node *output_adjacent_list[MAX_DOCS];
    Node *input_adjacent_list[MAX_DOCS];
    DocumentMapping mapping_docs[MAX_DOCS];
    int total_docs;
} Graph;

/* Funciones del grafo */
void initialize_graph(Graph *);
void add_edge(Graph *, int, int);
void build_graph(Graph *);
void release_graph(Graph *);
int count_output_links(Graph *, int);
int count_input_links(Graph *, int);
int get_doc_id(Graph *, char *);
bool is_doc_name(char *);
void show_graph(Graph *);
void generate_eps(const Graph *, const double *, const char *);

#endif // GRAPH_H
