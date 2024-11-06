#include "header.h"

void generar_archivos_de_texto(int numero_archivos_web)
{
    // El número de archivos web debe ser mayor a 0 para poder pasar de este punto.
    if (numero_archivos_web <= 0)
    {
        fprintf(stderr, "El número de archivos web a generar debe ser MAYOR a 0.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i <= numero_archivos_web; i++)
    {
        char nombre_web[MAX_NOMBRE_WEB];
        snprintf(nombre_web, sizeof(nombre_web), "web%d.txt", i); // Crear un nombre de archivo web.

        // Crear un archivo web, en caso de no poder abrir el archivo sale un error.
        FILE *web = fopen(nombre_web, "w");
        if (web == NULL)
        {
            fprintf(stderr, "Error al abrir el archivo web.");
            exit(EXIT_FAILURE);
        }

        generate_random_text(web, nombre_web);
    }
}

void generar_texto_random(FILE *web, const char *nombre_web)
{
    // Generar texto aleatorio dentro de cada archivo web.
    for (int i = 0; i < MAX_CARACTERES_WEB; i++)
    {
        char letter = 'A' + rand() % 26;
        fprintf(web, "%c", letter);
        if (i < MAX_CARACTERES_WEB - 1)
        {
            fprintf(web, " ");
        }
    }

    fclose(web);
    fprintf(stdout, "ARCHIVO '%s' generado con ÉXITO con %d letras.\n", nombre_web, MAX_CARACTERES_WEB);
}