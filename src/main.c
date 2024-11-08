#include "header.h"

int main(void)
{
    srand(time(NULL));

    int num_webs = 2;
    generate_text_files(num_webs);

    Graph graph;
    initialize_graph(&graph);
    build_graph(&graph);
    show_graph(&graph);

    double pagerank[MAX_DOCS];
    calculate_pagerank(&graph, pagerank);
    display_pagerank(&graph, pagerank);

    release_graph(&graph);

    return 0;
}
