#include "header.h"

int main()
{
    srand(time(NULL));

    int num_webs = 2;
    generate_text_files(num_webs);

    Graph graph;
    initialize_graph(&graph);

    add_document(&graph, 1);
    add_document(&graph, 2);
    add_document(&graph, 3);

    add_link(&graph, 0, 1); // documento 0 enlaza a Documento 1
    add_link(&graph, 1, 2); // documento 1 enlaza a Documento 2
    add_link(&graph, 0, 2); // documento 0 enlaza a Documento 2

    show_graph(&graph);

    return 0;
}
