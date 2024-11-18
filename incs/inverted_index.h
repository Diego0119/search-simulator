
// #ifndef INVERTED_INDEX
// #define INVERTED_INDEX

// #include "graph.h"
// /* Funciones Archivos TX */

// // Estructura Node para la lista enlazada de enlaces en el grafo.
// typedef struct Node
// {
//     int doc_id;        // Identificador del documento enlazado.
//     struct Node *next; // Puntero al siguiente nodo.
// } Node;

// // Estructura InvertedIndex para el índice invertido, almacenando palabras y los documentos donde aparecen.
// typedef struct InvertedIndex
// {
//     char word[MAX_WORD_SIZE];   // Palabra almacenada.
//     Node *docs_list;            // Lista de documentos donde aparece la palabra.
//     struct InvertedIndex *next; // Siguiente nodo en la lista enlazada del índice.
// } InvertedIndex;

// /* Funciones Indice invertido */
// InvertedIndex *create_new_node(char *);
// void add_document(InvertedIndex **, int, char *);
// void tokenize_text(char *, int, InvertedIndex **);
// void print_inverted_index(InvertedIndex **);
// unsigned int hash_function(char *);
// Node *search_word(InvertedIndex **, char *);
// void print_search_word(InvertedIndex **, char *);
// void build_index(Graph *, InvertedIndex **);
// void release_inverted_index(InvertedIndex **);

// #endif
