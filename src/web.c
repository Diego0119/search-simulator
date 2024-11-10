#include "header.h"

// Genera archivos de texto simulando documentos web con contenido aleatorio.
void generate_text_files(int num_webs)
{
    if (num_webs <= 0) // Verifica que se proporcione al menos un documento.
    {
        fprintf(stderr, "El número de archivos web a generar debe ser MAYOR a 0.\n");
        exit(EXIT_FAILURE);
    }

    // Itera para crear el número especificado de archivos de texto.
    for (int i = 1; i <= num_webs; i++)
    {
        char web_name[MAX_NAME_WEB];
        snprintf(web_name, sizeof(web_name), "doc%d.txt", i); // Genera un nombre para el archivo (e.g., "doc1.txt").

        // Crea el archivo en modo escritura. // Termina el programa si no se puede abrir el archivo.
        FILE *web = fopen(web_name, "w");
        if (web == NULL)
        {
            fprintf(stderr, "Error al abrir el archivo web.\n");
            exit(EXIT_FAILURE);
        }

        // Genera contenido aleatorio y enlaces dentro del archivo.
        generate_random_text(web, web_name, num_webs, i);

        fclose(web);
    }
}

// Genera texto aleatorio y enlaces en un archivo web específico.
void generate_random_text(FILE *web, const char *web_name, int num_docs, int current_doc)
{
    // Genera texto aleatorio dentro de cada archivo web.
    for (int i = 0; i < MAX_CHARACTERS_WEB; i++)
    {
        char letter = 'A' + rand() % 26; // Genera una letra aleatoria entre 'A' y 'Z'.
        fprintf(web, "%c", letter);      // Escribe la letra en el archivo.
        if (i < MAX_CHARACTERS_WEB - 1)
            fprintf(web, " "); // Agrega un espacio entre las letras.
    }

    // Incluye aleatoriamente enlaces a otros documentos.
    int num_links = rand() % 3; // Genera hasta 2 enlaces aleatorios.
    for (int i = 0; i < num_links; i++)
    {
        int link_doc = rand() % num_docs + 1;        // Elige un documento aleatorio de 1 a num_docs.
        if (link_doc != current_doc)                 // Evita que un documento enlace a sí mismo.
            fprintf(web, "\nlink: doc%d", link_doc); // Agrega un enlace al archivo.
    }

    fprintf(stdout, "ARCHIVO '%s' generado con ÉXITO con %d letras.\n", web_name, MAX_CHARACTERS_WEB);
}
