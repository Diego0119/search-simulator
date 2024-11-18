/* Librerías */
#include <stdbool.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

/* Macros */
#define CONVERGENCE_THRESHOLD 0.0001 // Umbral de convergencia del PageRank.
#define MAX_CHARACTERS_DOC 50        // Máximo de caracteres por página.
#define DAMPING_FACTOR 0.85          // Factor de amortiguación del PageRank.
#define MAX_ITERATIONS 100           // Máximo de iteraciones del algoritmo.
#define MAX_WORD_SIZE 50             // Máximo de longitud de palabras.
#define MAX_NAME_DOC 20              // Máximo de longitud de nombres de archivos.
#define MAX_DOCS 100                 // Máximo de documentos soportados.
#define HASH_TABLE_SIZE 30           // Tamaño de la tabla hash

// Estructura Node para la lista enlazada de enlaces en el grafo.
typedef struct Node
{
    int doc_id;        // Identificador del documento enlazado.
    struct Node *next; // Puntero al siguiente nodo.
} Node;

// Estructura para mapear el nombre de documentos a sus identificadores únicos.
typedef struct DocumentMapping
{
    char name[MAX_NAME_DOC]; // Nombre del documento.
    int doc_id;              // Identificador único del documento.
} DocumentMapping;

// Estructura Graph que representa el grafo de documentos con enlaces entrantes y salientes.
typedef struct Graph
{
    Node *output_adjacent_list[MAX_DOCS];   // Lista de enlaces salientes.
    Node *input_adjacent_list[MAX_DOCS];    // Lista de enlaces entrantes.
    DocumentMapping mapping_docs[MAX_DOCS]; // Mapeo de documentos.
    int total_docs;                         // Total de documentos en el grafo.
} Graph;

// Estructura InvertedIndex para el índice invertido, almacenando palabras y los documentos donde aparecen.
typedef struct InvertedIndex
{
    char word[MAX_WORD_SIZE];   // Palabra almacenada.
    Node *docs_list;            // Lista de documentos donde aparece la palabra.
    struct InvertedIndex *next; // Siguiente nodo en la lista enlazada del índice.
} InvertedIndex;

/* NO APLICADA */
void add_link(Graph *graph, int source_doc_id, int destination_doc_id);

/* Funciones Grafos */
void initialize_graph(Graph *);
void add_edge(Graph *, int, int);
void build_graph(Graph *);
void release_graph(Graph *);
int count_output_links(Graph *, int);
int count_input_links(Graph *, int);
int get_doc_id(Graph *, char *);
bool is_doc_name(char *);
void show_graph(Graph *);

/* Funciones Indice invertido */
InvertedIndex *create_new_node(char *);
void add_document(InvertedIndex **, int, char *);
void tokenize_text(char *, int, InvertedIndex **);
void print_inverted_index(InvertedIndex **);
unsigned int hash_function(char *);
Node *search_word(InvertedIndex **, char *);
void print_search_word(InvertedIndex **, char *);
void build_index(Graph *, InvertedIndex **);
void release_inverted_index(InvertedIndex **);

/* Funciones Archivos TXT */
void generate_text_files(int, int);
void generate_random_text(FILE *, const char *, int, int, int, int *);

/* Funciones PageRank */
void initialize_pagerank(double *, int);
void calculate_pagerank(Graph *, double *);
void display_pagerank(Graph *, double *);

/* Imprimir Grafo */
void generate_eps(const Graph *, const double *, const char *);
