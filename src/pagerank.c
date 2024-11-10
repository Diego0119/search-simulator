#include "header.h"

// Inicializa el vector de PageRank con valores uniformes para cada documento.
void initialize_pagerank(double pagerank[], int total_docs)
{
    for (int i = 0; i < total_docs; i++)
        pagerank[i] = 1.0 / total_docs; // Inicializa cada documento con el mismo valor de PageRank.
}

// Calcula el PageRank para cada documento en el grafo.
void calculate_pagerank(Graph *graph, double pagerank[])
{
    double new_pagerank[MAX_DOCS];                    // Vector temporal para almacenar los nuevos valores de PageRank en cada iteración.
    initialize_pagerank(pagerank, graph->total_docs); // Inicializa el PageRank.

    // Itera para calcular el PageRank hasta que converja o se alcance el máximo de iteraciones.
    for (int iter = 0; iter < MAX_ITERATIONS; iter++)
    {
        bool converged = true;

        // Calcula el nuevo PageRank para cada documento.
        for (int i = 0; i < graph->total_docs; i++)
        {
            double inbound_rank_sum = 0.0;

            // Recorre los documentos que enlazan al documento `i`.
            Node *inbound = graph->input_adjacent_list[i];
            while (inbound != NULL)
            {
                int inbound_doc_id = inbound->doc_id;                      // ID del documento de entrada.
                int out_links = count_output_links(graph, inbound_doc_id); // Número de enlaces salientes desde el documento.

                // Si el documento tiene enlaces salientes, acumula el PageRank proporcional.
                if (out_links > 0)
                    inbound_rank_sum += pagerank[inbound_doc_id] / out_links;

                inbound = inbound->next;
            }

            // Calcula el nuevo valor de PageRank utilizando el factor de amortiguación.
            new_pagerank[i] = (1 - DAMPING_FACTOR) / graph->total_docs + DAMPING_FACTOR * inbound_rank_sum;

            // Verifica si el cambio entre el nuevo y el viejo PageRank supera el umbral de convergencia.
            if (fabs(new_pagerank[i] - pagerank[i]) > CONVERGENCE_THRESHOLD)
                converged = false;
        }

        // Actualiza el vector de PageRank con los nuevos valores calculados.
        for (int i = 0; i < graph->total_docs; i++)
            pagerank[i] = new_pagerank[i];

        // Si todos los valores de PageRank han convergido, finaliza el cálculo.
        if (converged)
        {
            printf("PageRank convergido en %d iteraciones.\n", iter + 1);
            break;
        }
    }
}

// Muestra los resultados del PageRank para cada documento en la consola.
void display_pagerank(Graph *graph, double pagerank[])
{
    printf("\nResultados de PageRank:\n");
    for (int i = 0; i < graph->total_docs; i++)
        printf("Documento %d - PageRank: %.6f\n", i, pagerank[i]); // Imprime el ID del documento y su valor de PageRank.
}
