/**
 * @file main.c
 * @date 18-11-2024
 * @authors Miguel Loaiza, Diego Sanhueza, Miguel Maripillan y Felipe Carcamo
 * @brief Función principal de creación de archivos.
 *
 * Contiene la función principal del programa que crea los archivos de texto.
 */

#include "graph.h" ///< Librería que contiene las funciones del grafo.
#include "doc.h"   ///< Librería que contiene las funciones para generar archivos.

/**
 * @brief Función principal del programa.
 * @param argc Cantidad de argumentos.
 * @param argv Argumentos.
 * @return EXIT_SUCCESS si el programa termina correctamente.
 */

int main(int argc, char *argv[])
{
    /**
     * Se LEEN los ARGUMENTOS de la TERMINAL y se guardan en las variables num_docs y num_characters. Mientras se LEEN los ARGUMENTOS, se VALIDAN y se IMPRIMEN MENSAJES de AYUDA o ERROR.
     * @code
     * int opt;
     * int num_docs = 0;
     * int num_characters = 0;
     * while ((opt = getopt(argc, argv, "hd:c:")) != -1)
     * {
     *   switch (opt)
     *      *Casos como 'h' que es la ayuda*
     *      *Casos como 'd' que es el numero de archivos*
     *      *Casos como 'c' que es el numero de caracteres*
     *      *Casos como '?' que es un error*
     * }
     * @endcode
     */

    int opt;
    int num_docs = 0;
    int num_characters = 0;

    while ((opt = getopt(argc, argv, "hd:c:")) != -1)
    {
        switch (opt)
        {
        case 'h':
            fprintf(stdout, "\nUso del programa:\n");
            fprintf(stdout, "  -d <numero_de_archivos> : Número de archivos a crear.\n");
            fprintf(stdout, "  -c <numero_de_caracteres> : Número de caracteres por archivo.\n");
            fprintf(stdout, "  -h : Muestra esta ayuda.\n\n");
            exit(EXIT_SUCCESS);
            break;
        case 'd':
            num_docs = atoi(optarg);
            break;
        case 'c':
            num_characters = atoi(optarg);
            break;
        case '?':
            fprintf(stderr, "Opción no reconocida: -%c\n", optopt);
            exit(EXIT_FAILURE);
        default:
            fprintf(stderr, "Uso: %s [-h] [-d numero_de_archivos] [-c numero_de_caracteres]\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    /**
     * Se VALIDAN los ARGUMENTOS de la TERMINAL. Se verifica que se hayan proporcionado valores válidos para -d y -c. Se llama a la función para crear archivo de texto.
     * @code
     * if (num_docs <= 0 || num_characters <= 0)
     * {
     *      fprintf(stderr, "Error: Debes especificar valores positivos para -d y -c.\n");
     *      fprintf(stderr, "Uso: %s [-h] [-d numero_de_archivos] [-c numero_de_caracteres]\n", argv[0]);
     *      exit(EXIT_FAILURE);
     * }
     * srand(time(NULL));
     * generate_text_files(num_docs, num_characters);
     * return EXIT_SUCCESS;
     * @endcode
     */

    if (num_docs <= 0 || num_characters <= 0)
    {
        fprintf(stderr, "Error: Debes especificar valores positivos para -d y -c.\n");
        fprintf(stderr, "Uso: %s [-h] [-d numero_de_archivos] [-c numero_de_caracteres]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));

    fprintf(stdout, "\nCREANDO %d archivos de texto con %d caracteres cada uno...\n\n", num_docs, num_characters);
    generate_text_files(num_docs, num_characters);
    fprintf(stdout, "\nArchivos de texto creados con ÉXITO.\n\n");

    return EXIT_SUCCESS;
}
