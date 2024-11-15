#include "header.h"

int main(int argc, char *argv[])
{
    char *word_to_search = NULL;
    int opt;

    while ((opt = getopt(argc, argv, "hs:")) != -1)
    {
        switch (opt)
        {
        case 'h':
            fprintf(stdout, "\nPara ingresar la palabra a buscar, por favor coloque el parámetro <-s> <numero_de_archivos>\n\n");
            break;
        case 's':
            word_to_search = optarg;
            break;
        case '?':
            fprintf(stderr, "Opción no reconocida: -%c\n", optopt);
            exit(EXIT_FAILURE);
        default:
            fprintf(stderr, "Uso: %s [-h] [-s palabra_a_buscar]\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }
    srand(time(NULL));

    double pagerank[MAX_DOCS]; // Array para almacenar los valores de PageRank.
    Graph graph;
    InvertedIndex *index[HASH_TABLE_SIZE];

    for (int i = 0; i < HASH_TABLE_SIZE; i++) 
        index[i] = NULL;

    initialize_graph(&graph);
    build_graph(&graph);
    // release_inverted_index(index);
    calculate_pagerank(&graph, pagerank);
    display_pagerank(&graph, pagerank);
    show_graph(&graph);
    build_index(&graph, index);
    print_search_word(index, word_to_search);
    release_graph(&graph);

    return EXIT_SUCCESS;
}
