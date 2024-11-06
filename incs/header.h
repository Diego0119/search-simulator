#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>
#include <ctype.h>

#define MAX_DOCS 100
#define MAX_TAMANO_PALABRA 50
#define MAX_NAME_WEB 20
#define MAX_CHARACTERS_WEB 50

typedef struct Node
{
    int doc_id;        // indice del documento
    struct Node *next; // siguiente nodo
} Node;

typedef struct Graph
{ /* Enlaces del grafo dirigido, entrada y salida para pagerank e indice invertido*/

    Node *output_adyacent_list[MAX_DOCS];
    Node *input_adyacent_list[MAX_DOCS];
} Graph;

typedef struct InvertedIndex
{
    char word[MAX_TAMANO_PALABRA];
    Node *docs_list;
    struct InvertedIndex *next;
} InvertedIndex;

void add_document(Graph *graph, int id_doc);
void add_link(Graph *graph, int source_doc_id, int destination_doc_id);
void show_graph(Graph *graph);
/* Variables globales*/

extern MapeoDocumento mapeo_docs[MAX_DOCS];
extern int total_docs;

void initialize_graph(Graph *graph);
void add_edge(Graph *graph, int source, int destination);
void build_graph(Graph *graph);
void release_graph(Graph *graph);
int count_output_links(Graph *graph, int id_doc);
int count_input_links(Graph *graph, int id_doc);
int get_doc_id(char *file_name);
bool is_doc_name(char *file_name);

/* Generar archivos txt */
void generate_text_files(int *);                 // GENERA archivos txt (webs) y les coloca nombre.
void generar_texto_random(FILE *, const char *); // GENERA texto aleatorio en los archivos txt.