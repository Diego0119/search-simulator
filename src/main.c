#include "header.h"

int main(void)
{
    srand(time(NULL));

    int num_webs = 2;          // Número de webs a generar.
    double pagerank[MAX_DOCS]; // Array para almacenar los valores de PageRank.
    Graph graph;

    generate_text_files(num_webs);
    initialize_graph(&graph);
    build_graph(&graph);
    show_graph(&graph);
    calculate_pagerank(&graph, pagerank);
    display_pagerank(&graph, pagerank);
    release_graph(&graph);

    return EXIT_SUCCESS;
}
