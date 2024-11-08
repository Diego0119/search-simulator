#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>
#include <ctype.h>
#include <time.h>

#define MAX_DOCS 100
#define MAX_WORD_SIZE 50
#define MAX_NAME_WEB 20
#define MAX_CHARACTERS_WEB 50

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

void add_document(InvertedIndex **index, int doc_id, char *word);
void add_link(Graph *graph, int source_doc_id, int destination_doc_id);
void show_graph(Graph *graph);

Node *search_word(InvertedIndex **hash_table, char *word);
unsigned int hash_function(char *word);
void print_inverted_index(InvertedIndex *index);
void tokenize_text(char *text, int doc_id, InvertedIndex **index);
InvertedIndex *create_new_node(char *word);
void initialize_graph(Graph *graph);
void add_edge(Graph *graph, int source, int destination);
void build_graph(Graph *graph);
void release_graph(Graph *graph);
int count_output_links(Graph *graph, int id_doc);
int count_input_links(Graph *graph, int id_doc);
int get_doc_id(Graph *graph, char *file_name);
bool is_doc_name(char *file_name);

/* Generar archivos txt */
void generate_text_files(int num_webs);                 // GENERA archivos txt (webs) y les coloca nombre.
void generate_random_text(FILE *web, const char *web_name, int num_docs, int current_doc); // GENERA texto aleatorio en los archivos txt.
