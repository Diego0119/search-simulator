/**
 * @file main.c
 * @date 18-11-2024
 * @authors Miguel Loaiza, Diego Sanhueza, Miguel Maripillan y Felipe Cárcamo
 * @brief Función principal de menejo de funciones (grafos, pagerank e indice invertido).
 *
 * Contiene la función principal del programa que manipula los grafos y genera el PageRank y el Índice Invertido.
 */
#include "graph.h"          ///< Librería que contiene las funciones del grafo.
#include "inverted_index.h" ///< Librería que contiene las funciones del índice invertido.
#include "pagerank.h"       ///< Librería que contiene las funciones del PageRank.
#include "doc.h"            ///< Librería que contiene las funciones para generar archivos.

/**
 * @brief Función principal del programa.
 * @param argc Cantidad de argumentos.
 * @param argv Argumentos.
 * @return EXIT_SUCCESS si el programa termina correctamente.
 */
int main(int argc, char *argv[])
{
    /**
     * Se LEEN los ARGUMENTOS de la TERMINAL y se guardan en la variable word_to_search. Mientras se LEEN los ARGUMENTOS, se VALIDAN y se IMPRIMEN MENSAJES de AYUDA o ERROR.
     * @code
     * int opt;
     * char *word_to_search = NULL;
     * while ((opt = getopt(argc, argv, "hs:")) != -1)
     * {
     *   switch (opt)
     *      *Casos como 'h' que es la ayuda*
     *      *Casos como 's' que es la palabra buscada*
     *      *Casos como '?' que es un error*
     * }
     * @endcode
     */
    int opt;
    char *word_to_search1 = NULL;
    char *word_to_search2 = NULL;

    while ((opt = getopt(argc, argv, "hs:")) != -1)
    {
        switch (opt)
        {
        case 'h':
            fprintf(stdout, "\nPara ingresar la palabra a buscar, por favor coloque el parámetro <-s> <numero_de_archivos>\n\n");
            break;
        case 's':
            // Verifica si hay al menos un argumento disponible después de la opción `-s`
            if (optarg)
            {
                word_to_search1 = strdup(optarg); // Copia el argumento proporcionado con `-s`
            }

            // Verifica si hay un segundo argumento disponible después de `-s`
            if (optind < argc)
            {
                word_to_search2 = strdup(argv[optind]); // Copia la siguiente palabra en `argv`
            }
            else
            {
                word_to_search2 = NULL; // Si no hay segunda palabra, ponlo como NULL
            }
            break;
        case '?':
            fprintf(stderr, "Opción no reconocida: -%c\n", optopt);
            exit(EXIT_FAILURE);
        default:
            fprintf(stderr, "Uso: %s [-h] [-s palabra_a_buscar]\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    /**
     * Se inicializan las variables necesarias para el cálculo del PageRank, la construcción del índice invertido y la creación del grafo. Se llaman a las funciones primordiales.
     * @code
     * srand(time(NULL));
     * double pagerank[MAX_DOCS];
     * Graph graph;
     * InvertedIndex *index[HASH_TABLE_SIZE];
     * for (int i = 0; i < HASH_TABLE_SIZE; i++)
     *     index[i] = NULL;
     * initialize_graph(&graph);
     * build_graph(&graph);
     * calculate_pagerank(&graph, pagerank);
     * display_pagerank(&graph, pagerank);
     * show_graph(&graph);
     * build_index(&graph, index);
     * print_search_word(index, word_to_search);
     * release_inverted_index(index);
     * release_graph(&graph);
     * generate_eps(&graph, pagerank, "graph.eps");
     * return EXIT_SUCCESS;
     * @endcode
     */
    srand(time(NULL));

    double pagerank[MAX_DOCS]; // Array para almacenar los valores de PageRank.
    Graph graph;
    InvertedIndex *index[HASH_TABLE_SIZE];

    initialize_graph(&graph);
    build_graph(&graph);
    calculate_pagerank(&graph, pagerank);
    display_pagerank(&graph, pagerank);
    show_graph(&graph);
    build_index(&graph, index);
    print_search_word(index, word_to_search1);

    free(word_to_search1);
    free(word_to_search2);
    release_inverted_index(index);
    release_graph(&graph);
    generate_eps(&graph, pagerank, "graph.eps");

    return EXIT_SUCCESS;
}
