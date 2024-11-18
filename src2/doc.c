#include "graph.h"
#include "generator.h"

// Genera archivos de texto simulando documentos web con contenido aleatorio.
void generate_text_files(int num_docs)
{
    if (num_docs <= 0 || num_docs >= 100) // Verifica que se proporcione al menos un documento.
    {
        fprintf(stderr, "El número de archivos web a generar debe ser MAYOR a 0 y MENOR a 100.\n\n");
        exit(EXIT_FAILURE);
    }

    // Array para asegurar que cada documento tenga al menos un enlace.
    int *links = malloc(num_docs * sizeof(int));

    for (int i = 0; i < num_docs; i++)
        links[i] = (i + 1) % num_docs + 1; // Crea un ciclo simple para asegurar al menos un enlace por archivo.

    // Itera para crear el número especificado de archivos de texto.
    for (int i = 1; i <= num_docs; i++)
    {
        char doc_name[MAX_NAME_DOC];
        snprintf(doc_name, sizeof(doc_name), "doc%d.txt", i); // Genera un nombre para el archivo (e.g., "doc1.txt").

        // Crea el archivo en modo escritura. // Termina el programa si no se puede abrir el archivo.
        FILE *doc = fopen(doc_name, "w");
        if (doc == NULL)
        {
            fprintf(stderr, "Error al abrir el archivo web.\n");
            free(links);
            exit(EXIT_FAILURE);
        }

        // Genera contenido aleatorio y enlaces dentro del archivo.
        generate_random_text(doc, doc_name, num_docs, i, links);

        fclose(doc);
    }
}

// Genera texto aleatorio y enlaces en un archivo web específico.
void generate_random_text(FILE *doc, const char *doc_name, int num_docs, int current_doc, int *links)
{
    // Genera texto aleatorio dentro de cada archivo web.
    for (int i = 0; i < MAX_CHARACTERS_DOC; i++)
    {
        char letter = 'A' + rand() % 26; // Genera una letra aleatoria entre 'A' y 'Z'.
        fprintf(doc, "%c", letter);      // Escribe la letra en el archivo.
        if (i < MAX_CHARACTERS_DOC - 1)
            fprintf(doc, " "); // Agrega un espacio entre las letras.
    }

    fprintf(doc, "\nlink: doc%d", links[current_doc - 1]); // Asegura al menos un enlace único.

    // Incluye aleatoriamente enlaces a otros documentos.
    int extra_links = rand() % num_docs; // Genera hasta 2 enlaces aleatorios.
    for (int i = 0; i < extra_links; i++)
    {
        int link_doc = rand() % num_docs + 1;                              // Elige un documento aleatorio de 1 a num_docs.
        if (link_doc != current_doc && link_doc != links[current_doc - 1]) // Evita que un documento enlace a sí mismo.
            fprintf(doc, "\nlink: doc%d", link_doc);                       // Agrega un enlace al archivo.
    }

    fprintf(stdout, "ARCHIVO '%s' generado con ÉXITO con %d letras y enlaces.\n", doc_name, MAX_CHARACTERS_DOC);
}
