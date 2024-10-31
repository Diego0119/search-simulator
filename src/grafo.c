#include "header.h"

void inicializar_grafo(Grafo *grafo)
{
    grafo->numero_docs = 0;
    for (int i = 0; i < MAX_DOCS; i++)
    {
        grafo->lista_nodos[i] = NULL;
    }
}

void agregar_documento(Grafo *grafo, int id_doc)
{
    if (grafo->numero_docs < MAX_DOCS)
    {
        grafo->numero_docs++;
    }
    else
    {
        printf("Límite de documentos alcanzado\n");
    }
}
