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

void agregar_enlace(Grafo *grafo, int id_doc_origen, int id_doc_destino)
{
    if (id_doc_origen < 0 || id_doc_origen >= grafo->numero_docs ||
        id_doc_destino < 0 || id_doc_destino >= grafo->numero_docs)
    {
        printf("Documento no válido: %d o %d\n", id_doc_origen, id_doc_destino);
        return;
    }

    // se crea un nuevo nodo
    Nodo *nuevo_nodo = (Nodo *)malloc(sizeof(Nodo));
    nuevo_nodo->id_doc = id_doc_destino;
    nuevo_nodo->next = grafo->lista_nodos[id_doc_origen];
    grafo->lista_nodos[id_doc_origen] = nuevo_nodo;
}

void mostrar_grafo(Grafo *grafo)
{
    for (int i = 0; i < grafo->numero_docs; i++)
    {
        printf("Documento %d: ", i);
        Nodo *nodo = grafo->lista_nodos[i];
        while (nodo != NULL)
        {
            printf(" -> %d", nodo->id_doc);
            nodo = nodo->next;
        }
        printf("\n");
    }
}