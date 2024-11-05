#include "incs/header.h"

IndiceInvertido *crear_nuevo_nodo(char *palabra)
{
    IndiceInvertido *nuevo_nodo = (IndiceInvertido *)malloc(sizeof(IndiceInvertido));
    if (nuevo_nodo == NULL)
    {
        printf("Error al asignar memoria\n");
        exit(EXIT_FAILURE);
    }
    strcpy(nuevo_nodo->palabra, palabra);
    nuevo_nodo->lista_docs = NULL; // se inicializa en NULL porque al crearlo aun no hay docs con esas palabras
    nuevo_nodo->siguiente = NULL;
    return nuevo_nodo;
}

void agregar_documento(IndiceInvertido **indice, int doc_id, char *palabra)
{
    IndiceInvertido *actual = *indice;

    // aca se busca la palabra en el indice
    while (actual != NULL)
    {
        // si la comparacion se cumple, la palabra ya esta en el indice
        if (strcmp(actual->palabra, palabra) == 0)
        {
            // si la palabra ya existe, se crea un nuevo nodo para el documento
            Nodo *nuevo_doc = (Nodo *)malloc(sizeof(Nodo));
            nuevo_doc->id_doc = doc_id;
            nuevo_doc->next = actual->lista_docs;
            actual->lista_docs = nuevo_doc;
            return;
        }
        actual = actual->siguiente;
    }

    // si la palabra no se encuentra en el indice, se agrega al indice para reconocerla
    IndiceInvertido *nuevo_nodo = crear_nuevo_nodo(palabra);
    Nodo *nuevo_doc = (Nodo *)malloc(sizeof(Nodo));
    nuevo_doc->id_doc = doc_id;
    nuevo_doc->next = NULL;

    nuevo_nodo->lista_docs = nuevo_doc;
    nuevo_nodo->siguiente = *indice;
    *indice = nuevo_nodo;
}
