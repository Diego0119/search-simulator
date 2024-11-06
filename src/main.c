#include "header.h"

int main()
{
    srand(time(NULL));

    int num_webs = 2;
    generate_text_files(num_webs);

    Grafo grafo;
    inicializar_grafo(&grafo);

    agregar_documento(&grafo, 1);
    agregar_documento(&grafo, 2);
    agregar_documento(&grafo, 3);

    agregar_enlace(&grafo, 0, 1); // documento 0 enlaza a Documento 1
    agregar_enlace(&grafo, 1, 2); // documento 1 enlaza a Documento 2
    agregar_enlace(&grafo, 0, 2); // documento 0 enlaza a Documento 2

    mostrar_grafo(&grafo);

    return 0;
}
