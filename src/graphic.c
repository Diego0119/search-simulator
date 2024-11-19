/**
 * @file graphic.c
 * @date 18-11-2024
 * @authors Miguel Loaiza, Diego Sanhueza, Miguel Maripillan y Felipe Cárcamo
 * @brief Archivo que contiene las funciones de generación de dibujos eps.
 *
 * Contiene la implementación de las funciones que generan un archivo EPS con los grafos.
 */
#include "graph.h" ///< Incluye la definición de las estructuras y funciones del grafo.

/**
 * @brief Generar archivo EPS con el grafo.
 * @param graph Grafo
 * @param pagerank Arreglo de PageRank
 * @param filename Nombre del archivo EPS
 */
void generate_eps(const Graph *graph, const double *pagerank, const char *filename)
{
    /**
     * Crear archivo EPS, en caso de no poder abrir el archivo, tira error.
     * Inicia parámetros para ajustar el tamaño y la posición de los nodos.
     * Dibuja los nodos con el PageRank e Identificador.
     * @code
     * FILE *file = fopen(filename, "w");
     * if (!file)
     * {
     *    fprintf(stderr, "No se pudo crear el archivo EPS para el grafo.\n");
     *   exit(EXIT_FAILURE);
     * }
     * const int width = 800;
     * const int height = 800;
     * const int radius = 30;
     * const int margin = 100;
     * const int centerX = width / 2;
     * const int centerY = height / 2;
     * const double scale = 2 * M_PI / graph->total_docs;
     * fprintf(file, "%%!PS-Adobe-3.0 EPSF-3.0\n");
     * fprintf(file, "%%%%BoundingBox: 0 0 %d %d\n", width, height);
     * fprintf(file, "/Courier findfont 10 scalefont setfont\n");
     * fprintf(file, "1 setlinecap\n");
     * fprintf(file, "0.5 setlinewidth\n");
     * fprintf(file, "newpath\n");
     * double positions[MAX_DOCS][2];
     * for (int i = 0; i < graph->total_docs; i++)
     *      *Dibuja el Nodo*
     * @endcode
     *
     */
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        fprintf(stderr, "No se pudo crear el archivo EPS para el grafo.\n");
        exit(EXIT_FAILURE);
    }

    const int width = 800;
    const int height = 800;
    const int radius = 30;
    const int margin = 100;
    const int centerX = width / 2;
    const int centerY = height / 2;
    const double scale = 2 * M_PI / graph->total_docs;

    fprintf(file, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(file, "%%%%BoundingBox: 0 0 %d %d\n", width, height);
    fprintf(file, "/Courier findfont 10 scalefont setfont\n");
    fprintf(file, "1 setlinecap\n");
    fprintf(file, "0.5 setlinewidth\n");
    fprintf(file, "newpath\n");

    // Coordenadas de los nodos.
    double positions[MAX_DOCS][2];

    // Dibujar nodos con PageRank e Identificador.
    for (int i = 0; i < graph->total_docs; i++)
    {
        double angle = i * scale;
        positions[i][0] = centerX + (centerX - margin) * cos(angle);
        positions[i][1] = centerY + (centerY - margin) * sin(angle);

        // Asignar colores al nodo.
        double red = (rand() % 256) / 255.0;
        double green = (rand() % 256) / 255.0;
        double blue = (rand() % 256) / 255.0;
        fprintf(file, "%f %f %f setrgbcolor\n", red, green, blue);

        // Dibujar nodo.
        fprintf(file, "newpath\n");
        fprintf(file, "%.2f %.2f %d 0 360 arc fill\n", positions[i][0], positions[i][1], radius);

        // Texto Identificador del Nodo y PageRank.
        fprintf(file, "0 setgray\n");
        fprintf(file, "%.2f %.2f moveto (%d: %.3f) show\n", positions[i][0] - radius, positions[i][1] - 2 * radius, i, pagerank[i]);
    }

    // Dibujar enlaces entre nodos. ESTO NO SE PUEDE VISUALIZAR, *ARREGLAR*
    fprintf(file, "0 0 0 setrgbcolor\n"); // Color negro para las líneas.
    for (int i = 0; i < graph->total_docs; i++)
    {
        Node *current = graph->output_adjacent_list[i];
        while (current)
        {
            int destination = current->doc_id;
            fprintf(file, "newpath\n");
            fprintf(file, "%.2f %.2f moveto %.2f %.2f lineto stroke\n", positions[i][0], positions[i][1], positions[destination][0], positions[destination][1]);
            current = current->next;
        }
    }

    fprintf(file, "showpage\n");
    fclose(file);

    fprintf(stdout, "\nArchivo EPS generado: %s\n\n", filename);
}
