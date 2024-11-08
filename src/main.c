#include "header.h"

int main(void)
{
    srand(time(NULL));

    int num_webs = 2;
    double pagerank[MAX_DOCS];
    Graph graph;

    generate_text_files(num_webs);
    initialize_graph(&graph);
    build_graph(&graph);
    show_graph(&graph);
    calculate_pagerank(&graph, pagerank);
    display_pagerank(&graph, pagerank);
    release_graph(&graph);

    return 0;
}
