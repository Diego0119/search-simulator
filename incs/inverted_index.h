#ifndef INVERTED_INDEX_H
#define INVERTED_INDEX_H

#include "graph.h"

/* Estructura InvertedIndex */
typedef struct InvertedIndex
{
    char word[MAX_WORD_SIZE];
    Node *docs_list;
    struct InvertedIndex *next;
} InvertedIndex;

/* Funciones del índice invertido */
InvertedIndex *create_new_node(char *);
void add_document(InvertedIndex **, int, char *);
void tokenize_text(char *, int, InvertedIndex **);
void print_inverted_index(InvertedIndex **);
unsigned int hash_function(char *);
Node *search_word(InvertedIndex **, char *);
void print_search_word(InvertedIndex **, char *);
void build_index(Graph *, InvertedIndex **);
void release_inverted_index(InvertedIndex **);
bool is_stopword(char *token)

#endif // INVERTED_INDEX_H
