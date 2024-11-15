#include "header.h"

int main(void)
{
    srand(time(NULL));

    double pagerank[MAX_DOCS]; // Array para almacenar los valores de PageRank.
    Graph graph;
    InvertedIndex *index[HASH_TABLE_SIZE];

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
