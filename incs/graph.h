/**
 * @file graph.h
 * @date 18-11-2024
 * @authors Miguel Loaiza, Diego Sanhueza, Miguel Maripillan y Felipe Cárcamo
 * @brief Prototipos de funciones para la creación de los grafos.
 *
 * Contiene los prototipos de las funciones dedicadas a la creación de grafos, las estructuras generales y macros.
 */
#ifndef GRAPH_H
#define GRAPH_H

/**
 * Librerías utilizadas en el proyecto.
 * @code
 * #include <stdbool.h>
 * #include <string.h>
 * #include <stdlib.h>
 * #include <stdio.h>
 * #include <math.h>
 * #include <ctype.h>
 * #include <dirent.h>
 * #include <unistd.h>
 * #include <time.h>
 * @endcode
 */
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <dirent.h>
#include <unistd.h>
#include <time.h>

/**
 * Macros utilizadas en el proyecto.
 * @code
 * #define CONVERGENCE_THRESHOLD 0.0001
 * #define MAX_CHARACTERS_DOC 50
 * #define DAMPING_FACTOR 0.85
 * #define MAX_ITERATIONS 100
 * #define HASH_TABLE_SIZE 30
 * #define MAX_WORD_SIZE 50
 * #define MAX_NAME_DOC 20
 * #define MAX_DOCS 100
 * @endcode
 */
#define CONVERGENCE_THRESHOLD 0.0001
#define MAX_CHARACTERS_DOC 50
#define DAMPING_FACTOR 0.85
#define MAX_ITERATIONS 100
#define HASH_TABLE_SIZE 30
#define MAX_WORD_SIZE 50
#define MAX_NAME_DOC 20
#define MAX_DOCS 100

/**
 * @struct Node
 * @brief Estrucutra de un nodo.
 * @code
 * typedef struct Node
 * {
 *      int doc_id;
 *      struct Node *next;
 * } Node;
 * @endcode
 */
typedef struct Node
{
    int doc_id;
    struct Node *next;
} Node;

/**
 * @struct DocumentMapping
 * @brief Estrucutra de un mapeo de documentos.
 * @code
 * typedef struct DocumentMapping
 * {
 *      char name[MAX_NAME_DOC];
 *      int doc_id;
 *      int doc_number;
 * } DocumentMapping;
 * @endcode
 */
typedef struct DocumentMapping
{
    char name[MAX_NAME_DOC];
    int doc_id;
    int doc_number;
} DocumentMapping;

/**
 * @struct Graph
 * @brief Estrucutra de un grafo.
 * @code
 * typedef struct Graph
 * {
 *      Node *output_adjacent_list[MAX_DOCS];
 *      Node *input_adjacent_list[MAX_DOCS];
 *      DocumentMapping mapping_docs[MAX_DOCS];
 *      int total_docs;
 * } Graph;
 * @endcode
 */
typedef struct Graph
{
    Node *output_adjacent_list[MAX_DOCS];
    Node *input_adjacent_list[MAX_DOCS];
    DocumentMapping mapping_docs[MAX_DOCS];
    int total_docs;
} Graph;

/**
 * @brief Inicializa el grafo.
 * @param graph Grafo.
 */
void initialize_graph(Graph *);

/**
 * @brief Agrega un enlace dirigido entre dos documentos en el grafo.
 * @param graph Grafo.
 * @param source Documento de origen.
 * @param destination Documento de destino.
 */
void add_edge(Graph *, int, int);

/**
 * @brief Construye el grafo.
 * @param graph Grafo.
 */
void build_graph(Graph *);

/**
 * @brief Libera la memoria del grafo (nodos).
 * @param graph Grafo.
 */
void release_graph(Graph *);

/**
 * @brief Cuenta el número de enlaces salientes de un documento.
 * @param graph Grafo.
 * @param doc_id ID del documento.
 * @return Número de enlaces salientes.
 */
int count_output_links(Graph *, int);

/**
 * @brief Cuenta el número de enlaces entrantes a un documento.
 * @param graph Grafo.
 * @param doc_id ID del documento.
 * @return Número de enlaces entrantes.
 */
int count_input_links(Graph *, int);

/**
 * @brief Obtiene el ID de un documento a partir de su nombre de archivo.
 * @param graph Grafo.
 * @param file_name Nombre del archivo.
 * @return ID del documento.
 */
int get_doc_id(Graph *, char *);

/**
 * @brief Verifica si el nombre del archivo sigue el patrón "docN.txt" con N >= 1.
 * @param file_name Nombre del archivo.
 * @return true si cumple el patrón, false en caso contrario.
 */
bool is_doc_name(char *);

/**
 * @brief Muestra el grafo.
 * @param graph Grafo.
 */
void show_graph(Graph *);

/**
 * @brief Genera un archivo .eps con la representación gráfica del grafo.
 * @param graph Grafo.
 * @param pagerank Arreglo de PageRank.
 * @param file_name Nombre del archivo.
 */
void generate_eps(const Graph *, const double *, const char *);

/**
    Crea un nuevo grafo
    Puntero al grafo creado
*/
Graph* create_graph(void);

#endif
