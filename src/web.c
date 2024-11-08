#include "header.h"

void generate_text_files(int num_webs)
{
    if (num_webs <= 0)
    {
        fprintf(stderr, "El número de archivos web a generar debe ser MAYOR a 0.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i <= num_webs; i++)
    {
        char web_name[MAX_NAME_WEB];
        snprintf(web_name, sizeof(web_name), "doc%d.txt", i);

        FILE *web = fopen(web_name, "w");
        if (web == NULL)
        {
            fprintf(stderr, "Error al abrir el archivo web.\n");
            exit(EXIT_FAILURE);
        }

        generate_random_text(web, web_name, num_webs, i);
        fclose(web);
    }
}

void generate_random_text(FILE *web, const char *web_name, int num_docs, int current_doc)
{
    // Generar texto aleatorio dentro de cada archivo web.
    for (int i = 0; i < MAX_CHARACTERS_WEB; i++)
    {
        char letter = 'A' + rand() % 26;
        fprintf(web, "%c", letter);
        if (i < MAX_CHARACTERS_WEB - 1)
            fprintf(web, " ");
    }

    /* Incluir aleatoriamente enlaces a otros documentos*/
    int num_links = rand() % 3; /* Hasta 2 enlaces*/
    for (int i = 0; i < num_links; i++)
    {
        int link_doc = rand() % num_docs + 1; /* Documento aleatorio de 1 a num_docs*/
        if (link_doc != current_doc)          /* No enlazar a sí mismo */
            fprintf(web, "\nlink: doc%d", link_doc);
    }
    fprintf(stdout, "ARCHIVO '%s' generado con ÉXITO con %d letras.\n", web_name, MAX_CHARACTERS_WEB);
}
