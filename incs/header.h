#include <stdbool.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#define CONVERGENCE_THRESHOLD 0.0001 // Umbral de convergencia
#define MAX_CHARACTERS_WEB 50
#define DAMPING_FACTOR 0.85 // Factor de amortiguación
#define MAX_ITERATIONS 100  // Máximo de iteraciones para la convergencia
#define MAX_WORD_SIZE 50
#define MAX_NAME_WEB 20
#define MAX_DOCS 100

typedef struct Node
{
    int doc_id;        // indice del documento
    struct Node *next; // siguiente nodo
} Node;

typedef struct DocumentMapping
{
    char name[MAX_NAME_WEB];
    int doc_id;
} DocumentMapping;

typedef struct Graph
{ /* Enlaces del grafo dirigido, entrada y salida para pagerank e indice invertido*/
    Node *output_adjacent_list[MAX_DOCS];
    Node *input_adjacent_list[MAX_DOCS];
    DocumentMapping mapping_docs[MAX_DOCS];
    int total_docs;
} Graph;

typedef struct InvertedIndex
{
    char word[MAX_WORD_SIZE];   // almacena la palabra
    Node *docs_list;            // lista de documentos en los que aparece la palabra (es como la cabeza de la lista)
    struct InvertedIndex *next; // siguiente nodo de la lista enlazada del indice (otra palabra)
} InvertedIndex;

/* NO APLICADA */
void add_link(Graph *graph, int source_doc_id, int destination_doc_id);

/* Grafos */
void initialize_graph(Graph *graph);
void add_edge(Graph *graph, int source, int destination);
void build_graph(Graph *graph);
void release_graph(Graph *graph);
int count_output_links(Graph *graph, int id_doc);
int count_input_links(Graph *graph, int id_doc);
int get_doc_id(Graph *graph, char *file_name);
bool is_doc_name(char *file_name);
void show_graph(Graph *graph);

/* Indice invertido */
InvertedIndex *create_new_node(char *word);
void add_document(InvertedIndex **index, int doc_id, char *word);
void tokenize_text(char *text, int doc_id, InvertedIndex **index);
void print_inverted_index(InvertedIndex *index);
unsigned int hash_function(char *word);
Node *search_word(InvertedIndex **hash_table, char *word);
void release_inverted_index(InvertedIndex **hash_table); // Idea... para liberar el indide invertido...

/* Archivos txt */
void generate_text_files(int num_webs);                                                    // GENERA archivos txt (webs) y les coloca nombre.
void generate_random_text(FILE *web, const char *web_name, int num_docs, int current_doc); // GENERA texto aleatorio en los archivos txt.

/* PageRank */
void initialize_pagerank(double pagerank[], int total_docs);
void calculate_pagerank(Graph *graph, double pagerank[]);
void display_pagerank(Graph *graph, double pagerank[]);
