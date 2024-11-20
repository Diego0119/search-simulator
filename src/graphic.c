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
 * @brief Función que genera un archivo EPS con la representación gráfica del grafo (No se incluyen los enlaces, solo los nodos).
 * @param graph Grafo
 * @param pagerank Arreglo de PageRank
 * @param filename Nombre del archivo EPS
 */
void generate_eps(const Graph *graph, const double *pagerank, const char *filename)
{
    /**
     * Se verifica que el archivo se abra correctamente y se crear las variables base para crear la generación de la imagen EPS.
     * @code
     * FILE *file = fopen(filename, "w");\
     * if (!file)
     * {
     *      fprintf(stderr, "No se pudo crear el archivo EPS para el grafo.\n");
     *      exit(EXIT_FAILURE);
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
     * @endcode
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

    double positions[MAX_DOCS][2];

    /**
     * Se recorre el grafo, se asigna una posición a cada nodo y se dibuja.
     * @code
     * for (int i = 0; i < graph->total_docs; i++)
     * {
     *      double angle = i * scale;
     *      positions[i][0] = centerX + (centerX - margin) * cos(angle);
     *      positions[i][1] = centerY + (centerY - margin) * sin(angle);
     *      double red = (rand() % 256) / 255.0;
     *      double green = (rand() % 256) / 255.0;
     *      double blue = (rand() % 256) / 255.0;
     *      fprintf(file, "%f %f %f setrgbcolor\n", red, green, blue);
     *      fprintf(file, "newpath\n");
     *      fprintf(file, "%.2f %.2f %d 0 360 arc fill\n", positions[i][0], positions[i][1], radius);
     *      fprintf(file, "0 setgray\n");
     *      fprintf(file, "%.2f %.2f moveto (%d: %.3f) show\n", positions[i][0] - radius, positions[i][1] - 2 * radius, i, pagerank[i]);
     * }
     * @endcode
     */
    for (int i = 0; i < graph->total_docs; i++)
    {
        double angle = i * scale;
        positions[i][0] = centerX + (centerX - margin) * cos(angle);
        positions[i][1] = centerY + (centerY - margin) * sin(angle);

        double red = (rand() % 256) / 255.0;
        double green = (rand() % 256) / 255.0;
        double blue = (rand() % 256) / 255.0;
        fprintf(file, "%f %f %f setrgbcolor\n", red, green, blue);

        fprintf(file, "newpath\n");
        fprintf(file, "%.2f %.2f %d 0 360 arc fill\n", positions[i][0], positions[i][1], radius);

        fprintf(file, "0 setgray\n");
        fprintf(file, "%.2f %.2f moveto (%d: %.3f) show\n", positions[i][0] - radius, positions[i][1] - 2 * radius, i, pagerank[i]);
    }

    fprintf(file, "showpage\n");
    fclose(file);

    fprintf(stdout, "\nArchivo EPS generado: %s\n\n", filename);

    /**
     * Se convierte el archivo EPS a PNG con GHOSTSCRIPT.
     * @code
     * char comando[256];
     * snprintf(comando, sizeof(comando), "gs -dSAFER -dBATCH -dNOPAUSE -dEPSCrop -sDEVICE=png16m -r300 -sOutputFile=%s.png %s", filename, filename);
     * int resultado = system(comando);
     * if (resultado != 0)
     * {
     *      fprintf(stderr, "ERROR al convertir el archivo EPS a PNG, saliendo...\n");
     *      exit(EXIT_FAILURE);
     * }
     * fprintf(stdout, "\nArchivo EPS convertido a PNG en el archivo %s.png\n\n", filename);
     * @endcode
     */
    char comando[256];
    snprintf(comando, sizeof(comando), "gs -dSAFER -dBATCH -dNOPAUSE -dEPSCrop -sDEVICE=png16m -r300 -sOutputFile=%s.png %s", filename, filename);
    int resultado = system(comando);
    if (resultado != 0)
    {
        fprintf(stderr, "ERROR al convertir el archivo EPS a PNG, saliendo...\n");
        exit(EXIT_FAILURE);
    }
    fprintf(stdout, "\nArchivo EPS convertido a PNG en el archivo %s.png\n\n", filename);
}
