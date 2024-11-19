/**
 * @file inverted_index.h
 * @date 18-11-2024
 * @authors Miguel Loaiza, Diego Sanhueza, Miguel Maripillan y Felipe Cárcamo
 * @brief Prototipos de funciones para la creación y manejo del índice invertido.
 *
 * Contiene los prototipos de las funciones y estructura dedicadas a la creación y manejo del índice invertido.
 */
#ifndef INVERTED_INDEX_H
#define INVERTED_INDEX_H

#include "graph.h" ///< Incluye la definición de las estructuras y funciones del grafo.

/**
 * @struct InvertedIndex
 * @brief Estructura de un nodo en el índice invertido.
 * @code
 * typedef struct InvertedIndex
 * {
 *      char word[MAX_WORD_SIZE];
 *      Node *docs_list;
 *      struct InvertedIndex *next;
 * } InvertedIndex;
 * @endcode
 */
typedef struct InvertedIndex
{
    char word[MAX_WORD_SIZE];
    Node *docs_list;
    struct InvertedIndex *next;
} InvertedIndex;

/**
 * @brief Crea un nuevo nodo en el índice invertido para una palabra específica.
 * @param word La palabra a agregar.
 * @return new_node
 */
InvertedIndex *create_new_node(char *);

/**
 * @brief Agrega un documento al índice invertido, asociándolo con una palabra específica.
 * @param hash_table Tabla hash.
 * @param doc_id ID del documento.
 * @param word Palabra a agregar.
 */
void add_document(InvertedIndex **, int, char *);

/**
 * @brief Convierte todo el texto a minúsculas y reemplaza caracteres de puntuación por espacios.
 * @param token Token a procesar.
 */
bool is_stopword(char *);

/**
 * @brief Tokeniza el texto y agrega las palabras al índice invertido.
 * @param text Texto a tokenizar.
 * @param doc_id ID del documento.
 * @param index Índice invertido.
 */
void tokenize_text(char *, int, InvertedIndex **);

/**
 * @brief Imprime el índice invertido mostrando cada palabra y los documentos asociados.
 * @param index Índice invertido.
 */
void print_inverted_index(InvertedIndex **);

/**
 * @brief Imprime el índice invertido mostrando cada palabra asociada a los documentos.
 * @param index Índice invertido.
 */
void print_search_word(InvertedIndex **, char *);

/**
 * @brief Función hash para obtener un índice basado en el valor ASCII de los caracteres de una palabra.
 * @param word Palabra a procesar.
 * @return hash
 */
unsigned int hash_function(char *);

/**
 * @brief Busca una palabra en el índice invertido.
 * @param index Índice invertido.
 * @param word_to_search Palabra a buscar.
 * @return results
 */
Node *search_word(InvertedIndex **, char *);

/**
 * @brief Lee los archivos que se encuentran guardados en el grafo y crea el índice.
 * @param graph Grafo.
 * @param index Índice invertido.
 */
void build_index(Graph *, InvertedIndex **);

/**
 * @brief Libera la memoria del índice invertido y los nodos de documentos asociados.
 * @param hash_table Tabla hash.
 */
void release_inverted_index(InvertedIndex **);


#endif
