#include "header.h"

void generate_text_files(int num_webs)
{
    // El número de archivos web debe ser mayor a 0 para poder pasar de este punto.
    if (num_webs <= 0)
    {
        fprintf(stderr, "El número de archivos web a generar debe ser MAYOR a 0.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i <= num_webs; i++)
    {
        char web_name[MAX_NAME_WEB];
        snprintf(web_name, sizeof(web_name), "web%d.txt", i); // Crear un nombre de archivo web.

        // Crear un archivo web, en caso de no poder abrir el archivo sale un error.
        FILE *web = fopen(web_name, "w");
        if (web == NULL)
        {
            fprintf(stderr, "Error al abrir el archivo web.");
            exit(EXIT_FAILURE);
        }

        generate_random_text(web, web_name);
    }
}

void generate_random_text(FILE *web, const char *web_name)
{
    // Generar texto aleatorio dentro de cada archivo web.
    for (int i = 0; i < MAX_CHARACTERS_WEB; i++)
    {
        char letter = 'A' + rand() % 26;
        fprintf(web, "%c", letter);
        if (i < MAX_CHARACTERS_WEB - 1)
        {
            fprintf(web, " ");
        }
    }

    fclose(web);
    fprintf(stdout, "ARCHIVO '%s' generado con ÉXITO con %d letras.\n", web_name, MAX_CHARACTERS_WEB);
}