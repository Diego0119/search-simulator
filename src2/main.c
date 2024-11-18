#include "graph.h"
#include "doc.h"

int main(int argc, char *argv[])
{
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

    // Verifica que se hayan proporcionado valores válidos para -d y -c.
    if (num_docs <= 0 || num_characters <= 0)
    {
        fprintf(stderr, "Error: Debes especificar valores positivos para -d y -c.\n");
        fprintf(stderr, "Uso: %s [-h] [-d numero_de_archivos] [-c numero_de_caracteres]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));

    generate_text_files(num_docs, num_characters);

    return EXIT_SUCCESS;
}
