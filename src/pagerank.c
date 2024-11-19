/**
 * @file pagerank.c
 * @date 18-11-2024
 * @authors Miguel Loaiza, Diego Sanhueza, Miguel Maripillan y Felipe Cárcamo
 * @brief Archivo que contiene las funciones de PageRank.
 *
 * Contiene la implementación de las funciones que calculan el PageRank de cada documento en el grafo.
 */
#include "graph.h" ///< Incluye la definición de las estructuras y funciones del grafo.

/**
 * @brief Inicializar PageRank
 * @param pagerank Arreglo de PageRank
 * @param num_docs Número de documentos
 */
void initialize_pagerank(double *pagerank, int num_docs)
{
    /**
     * Inicializa cada documento con el mismo valor de PageRank.
     * @code
     * for (int i = 0; i < num_docs; i++)
     *     pagerank[i] = 1.0 / num_docs;
     * @endcode
     */
    for (int i = 0; i < num_docs; i++)
        pagerank[i] = 1.0 / num_docs;
}

/**
 * @brief Calcular PageRank
 * @param graph Grafo
 * @param pagerank Arreglo de PageRank
 */
void calculate_pagerank(Graph *graph, double *pagerank)
{
    /**
     * Inicializa variables y PageRank.
     * @code
     * int num_docs = graph->total_docs;
     * initialize_pagerank(pagerank, num_docs);
     * double temp_rank[MAX_DOCS];
     * @endcode
     */
    int num_docs = graph->total_docs;
    initialize_pagerank(pagerank, num_docs);
    double temp_rank[MAX_DOCS];

    /**
     * Itera hasta que se cumple el criterio de convergencia.
     * Calcula la contribución de cada nodo a los que apunta.
     * Distribuye la contribución de PageRank a cada nodo de la lista de adyacencia.
     * @code
     * for (int iteration = 0; iteration < MAX_ITERATIONS; iteration++)
     * {
     *      for (int i = 0; i < num_docs; i++)
     *          temp_rank[i] = (1 - DAMPING_FACTOR) / num_docs;
     *      for (int i = 0; i < num_docs; i++)
     *      {
     *          int num_links = count_output_links(graph, i);
     *          if (num_links == 0)
     *              continue;
     *          double rank_contribution = pagerank[i] * DAMPING_FACTOR / num_links;
     *          Node *current = graph->output_adjacent_list[i];
     *          while (current != NULL)
     *          {
     *              temp_rank[current->doc_id] += rank_contribution;
     *              current = current->next;
     *          }
     *      }
     * @endcode
     */
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

        /**
         * Calcula el error y actualiza los valores de PageRank.
         * Si el error es menor al umbral de convergencia, se detiene el algoritmo.
         * @code
         * double error = 0;
         * for (int i = 0; i < num_docs; i++)
         * {
         *      error += fabs(pagerank[i] - temp_rank[i]);
         *      pagerank[i] = temp_rank[i];
         * }
         * if (error < CONVERGENCE_THRESHOLD)
         *    break;
         * @endcode
         */
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

/**
 * @brief Mostrar PageRank
 * @param graph Grafo
 * @param pagerank Arreglo de PageRank
 */
void display_pagerank(Graph *graph, double *pagerank)
{
    /**
     * Muestra los valores de PageRank de cada documento.
     * @code
     * fprintf(stdout, "\nValores de PageRank:\n\n");
     * for (int i = 0; i < graph->total_docs; i++)
     *      fprintf(stdout, "Documento (%s): PageRank = %.6f\n", graph->mapping_docs[i].name, pagerank[i]);
     * @endcode
     */
    fprintf(stdout, "\nValores de PageRank:\n\n");
    for (int i = 0; i < graph->total_docs; i++)
        fprintf(stdout, "Documento (%s): PageRank = %.6f\n", graph->mapping_docs[i].name, pagerank[i]);
}
