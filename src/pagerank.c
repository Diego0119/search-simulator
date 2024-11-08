#include "header.h"

void initialize_pagerank(double pagerank[], int total_docs)
{
    for (int i = 0; i < total_docs; i++)
    {
        pagerank[i] = 1.0 / total_docs; // Inicializar PageRank uniformemente.
    }
}

void calculate_pagerank(Graph *graph, double pagerank[])
{
    double new_pagerank[MAX_DOCS];
    initialize_pagerank(pagerank, graph->total_docs);

    for (int iter = 0; iter < MAX_ITERATIONS; iter++)
    {
        bool converged = true;

        // Calcular el nuevo PageRank para cada documento.
        for (int i = 0; i < graph->total_docs; i++)
        {
            double inbound_rank_sum = 0.0;

            // Recorrer los documentos que tienen un enlace hacia el documento `i`.
            Node *inbound = graph->input_adjacent_list[i];
            while (inbound != NULL)
            {
                int inbound_doc_id = inbound->doc_id;
                int out_links = count_output_links(graph, inbound_doc_id);

                if (out_links > 0)
                {
                    inbound_rank_sum += pagerank[inbound_doc_id] / out_links;
                }

                inbound = inbound->next;
            }

            // Calcular el nuevo valor de PageRank.
            new_pagerank[i] = (1 - DAMPING_FACTOR) / graph->total_docs + DAMPING_FACTOR * inbound_rank_sum;

            // Verificar la convergencia.
            if (fabs(new_pagerank[i] - pagerank[i]) > CONVERGENCE_THRESHOLD)
            {
                converged = false;
            }
        }

        // Actualizar el valor de PageRank y verificar.
        for (int i = 0; i < graph->total_docs; i++)
        {
            pagerank[i] = new_pagerank[i];
        }

        if (converged)
        {
            printf("PageRank convergido en %d iteraciones.\n", iter + 1);
            break;
        }
    }
}

void display_pagerank(Graph *graph, double pagerank[])
{
    printf("\nResultados de PageRank:\n");
    for (int i = 0; i < graph->total_docs; i++)
    {
        printf("Documento %d - PageRank: %.6f\n", i, pagerank[i]);
    }
}
