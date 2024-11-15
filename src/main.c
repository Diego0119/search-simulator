#include "header.h"

int main(int argc, char *argv[])
{
    int opt;
    int num_docs = 0;

    while ((opt = getopt(argc, argv, "hd:")) != -1)
    {
        switch (opt)
        {
        case 'h':
            fprintf(stdout, "\nPara ingresar la cantidad de archivos a crear, por favor coloque el parámetro <-d> <numero_de_archivos>\n\n");
            break;
        case 'd':
            num_docs = atoi(optarg);
            fprintf(stdout, "\nNúmero de archivos: %d\n\n", num_docs);
            break;
        case '?':
            fprintf(stderr, "Opción no reconocida: -%c\n", optopt);
            exit(EXIT_FAILURE);
        default:
            fprintf(stderr, "Uso: %s [-h] [-d numero_de_archivos]\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    srand(time(NULL));

    double pagerank[MAX_DOCS]; // Array para almacenar los valores de PageRank.
    Graph graph;
    InvertedIndex *index[HASH_TABLE_SIZE];

    generate_text_files(num_docs);
    initialize_graph(&graph);
    build_graph(&graph);
    build_index(&graph, index);
    print_inverted_index(index);
    // release_inverted_index(index);
    show_graph(&graph);
    calculate_pagerank(&graph, pagerank);
    display_pagerank(&graph, pagerank);
    release_graph(&graph);

    return EXIT_SUCCESS;
}
