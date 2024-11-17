#include "header.h"

// Función para generar un archivo EPS con los grafos.
void generate_eps_with_graphs(const Graph *graph, const double *pagerank, const char *filename)
{
    // Crear archivo EPS, en caso de no poder abrir el archivo, tira error.
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        fprintf(stderr, "No se pudo crear el archivo EPS para el grafo.\n");
        exit(EXIT_FAILURE);
    }

    // Parámetros para ajustar el tamaño y la posición de los nodos.
    const int width = 800;  // Ancho del canvas.
    const int height = 800; // Alto del canvas.
    const int radius = 30;  // Radio de los nodos.
    const int margin = 100; // Margen en el canvas.
    const int centerX = width / 2;
    const int centerY = height / 2;
    const double scale = 2 * M_PI / graph->total_docs; // Espaciado entre los nodos.

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
            fprintf(file, "%.2f %.2f moveto %.2f %.2f lineto stroke\n",
                    positions[i][0], positions[i][1],
                    positions[destination][0], positions[destination][1]);
            current = current->next;
        }
    }

    fprintf(file, "showpage\n");
    fclose(file);

    printf("Archivo EPS generado: %s\n", filename);
}
