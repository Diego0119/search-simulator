#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DOCS 100

typedef struct Nodo
{
    int id_doc;        // indice del documento
    struct Nodo *next; // siguiente nodo
} Nodo;

typedef struct Grafo
{
    int numero_docs;             // numero de documentos del grafo
    Nodo *lista_nodos[MAX_DOCS]; // arreglo con la lista

} Grafo;

void inicializar_grafo(Grafo *grafo);

void agregar_documento(Grafo *grafo, int id_doc);
