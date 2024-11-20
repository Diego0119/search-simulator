/**
 * @file doc.c
 * @date 18-11-2024
 * @authors Miguel Loaiza, Diego Sanhueza, Miguel Maripillan y Felipe Cárcamo
 * @brief Archivo que contiene el manejo de archivos y rellenado de estos.
 *
 * Contiene la implementación de las funciones que generan archivos de texto simulando documentos web con contenido aleatorio.
 */

#include "graph.h" ///< Incluye la definición de las estructuras y funciones del grafo.
#include "doc.h"   ///< Incluye la definición de las funciones de generación de archivos.

/**
 * @brief Generar archivos txt
 * @param num_docs Cantidad de archivos a generar
 * @param num_characters Cantidad de caracteres por archivo
 */
void generate_text_files(int num_docs, int num_characters)
{
    /**
     * Verifica que el número de archivos a generar sea válido.
     * Crea un array de enlaces para asegurar que cada documento tenga al menos un enlace.
     * Llama a la función generate_random_text para generar el contenido de cada archivo.
     * @code
     * if (num_docs <= 0 || num_docs >= 100)
     * {
     *      fprintf(stderr, "El número de archivos web a generar debe ser MAYOR a 0 y MENOR a 100.\n\n");
     *      exit(EXIT_FAILURE);
     * }
     * if (num_characters <= 0 || num_characters >= 50)
     * {
     *      fprintf(stderr, "El número de caracteres por archivo debe ser MAYOR a 0 y MENOR a 50.\n\n");
     *      exit(EXIT_FAILURE);
     * }
     * int *links = malloc(num_docs * sizeof(int));
     * for (int i = 0; i < num_docs; i++)
     *      links[i] = (i + 1) % num_docs + 1;
     * for (int i = 1; i <= num_docs; i++)
     * {
     *      char doc_name[MAX_NAME_DOC];
     *      snprintf(doc_name, sizeof(doc_name), "doc%d.txt", i);
     *      FILE *doc = fopen(doc_name, "w");
     *      if (doc == NULL)
     *      {
     *          fprintf(stderr, "Error al abrir el archivo web.\n");
     *          free(links);
     *          exit(EXIT_FAILURE);
     *      }
     *      generate_random_text(doc, doc_name, num_docs, num_characters, i, links);
     *    fclose(doc);
     * }
     * @endcode
     */
    if (num_docs <= 0 || num_docs >= 100)
    {
        fprintf(stderr, "El número de archivos web a generar debe ser MAYOR a 0 y MENOR a 100.\n\n");
        exit(EXIT_FAILURE);
    }

    if (num_characters <= 0 || num_characters >= 51)
    {
        fprintf(stderr, "El número de caracteres por archivo debe ser MAYOR a 0 y MENOR a 50.\n\n");
        exit(EXIT_FAILURE);
    }

    int *links = malloc(num_docs * sizeof(int));

    for (int i = 0; i < num_docs; i++)
        links[i] = (i + 1) % num_docs + 1;

    for (int i = 1; i <= num_docs; i++)
    {
        char doc_name[MAX_NAME_DOC];
        snprintf(doc_name, sizeof(doc_name), "doc%d.txt", i);

        FILE *doc = fopen(doc_name, "w");
        if (doc == NULL)
        {
            fprintf(stderr, "Error al abrir el archivo web.\n");
            free(links);
            exit(EXIT_FAILURE);
        }
        generate_random_text(doc, doc_name, num_docs, num_characters, i, links);
        fclose(doc);
    }
}

/**
 * @brief Generar texto aleatorio
 * @param doc Archivo a escribir
 * @param doc_name Nombre del archivo
 * @param num_docs Número de documentos
 * @param num_characters Número de caracteres
 * @param current_doc Documento actual
 * @param links Conexiones entre documentos
 */
void generate_random_text(FILE *doc, const char *doc_name, int num_docs, int num_characters, int current_doc, int *links)
{
    /**
     * Genera texto aleatorio dentro de cada archivo web (letras entre A y Z).
     * @code
     * for (int i = 0; i < num_characters; i++)
     * {
     *      char letter = 'A' + rand() % 26;
     *      fprintf(doc, "%c", letter);
     *      if (i < num_characters - 1)
     *          fprintf(doc, " ");
     * }
     * @endcode
     */
    for (int i = 0; i < num_characters; i++)
    {
        char letter = 'A' + rand() % 26;
        fprintf(doc, "%c", letter);
        if (i < num_characters - 1)
            fprintf(doc, " ");
    }

    /**
     * Asegura al menos un enlace único en cada archivo web.
     * @code
     * fprintf(doc, "\nlink: doc%d", links[current_doc - 1]);
     * int extra_links = rand() % num_docs;
     * for (int i = 0; i < extra_links; i++)
     * {
     *      int link_doc = rand() % num_docs + 1;
     *      if (link_doc != current_doc && link_doc != links[current_doc - 1])
     *          fprintf(doc, "\nlink: doc%d", link_doc);
     * }
     * @endcode
     */
    fprintf(doc, "\nlink: doc%d", links[current_doc - 1]);

    int extra_links = rand() % num_docs;
    for (int i = 0; i < extra_links; i++)
    {
        int link_doc = rand() % num_docs + 1;
        if (link_doc != current_doc && link_doc != links[current_doc - 1])
            fprintf(doc, "\nlink: doc%d", link_doc);
    }

    fprintf(stdout, "ARCHIVO '%s' generado con ÉXITO con %d letras y enlaces.\n", doc_name, num_characters);
}
