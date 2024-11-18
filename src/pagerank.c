#include "graph.h"

// Inicializa el vector de PageRank con valores uniformes para cada documento.
void initialize_pagerank(double *pagerank, int num_docs)
{
    for (int i = 0; i < num_docs; i++)
        pagerank[i] = 1.0 / num_docs; // Inicializa cada documento con el mismo valor de PageRank.
}

// Calcula el PageRank de cada documento en el grafo.
void calculate_pagerank(Graph *graph, double *pagerank)
{
    int num_docs = graph->total_docs;
    initialize_pagerank(pagerank, num_docs);
    double temp_rank[MAX_DOCS];

    for (int iteration = 0; iteration < MAX_ITERATIONS; iteration++)
    {
        for (int i = 0; i < num_docs; i++)
            temp_rank[i] = (1 - DAMPING_FACTOR) / num_docs;

        for (int i = 0; i < num_docs; i++)
        {
            int num_links = count_output_links(graph, i);

            if (num_links == 0)
                continue;

            double rank_contribution = pagerank[i] * DAMPING_FACTOR / num_links;
            Node *current = graph->output_adjacent_list[i];

            while (current != NULL)
            {
                temp_rank[current->doc_id] += rank_contribution;
                current = current->next;
            }
        }

        double error = 0;

        for (int i = 0; i < num_docs; i++)
        {
            error += fabs(pagerank[i] - temp_rank[i]);
            pagerank[i] = temp_rank[i];
        }

        if (error < CONVERGENCE_THRESHOLD)
            break;
    }
}

// Muestra el valor de PageRank de cada documento.
void display_pagerank(Graph *graph, double *pagerank)
{
    fprintf(stdout, "\nValores de PageRank:\n\n");
    for (int i = 0; i < graph->total_docs; i++)
        fprintf(stdout, "Documento (%s): PageRank = %.6f\n", graph->mapping_docs[i].name, pagerank[i]);
}
