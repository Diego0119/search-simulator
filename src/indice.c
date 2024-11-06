#include "../incs/header.h"

InvertedIndex *crear_nuevo_nodo(char *word)
{
    InvertedIndex *new_node = (InvertedIndex *)malloc(sizeof(InvertedIndex));
    if (new_node == NULL)
    {
        printf("Error al asignar memoria\n");
        exit(EXIT_FAILURE);
    }
    strcpy(new_node->word, word);
    new_node->docs_list = NULL; // se inicializa en NULL porque al crearlo aun no hay docs con esas words
    new_node->next = NULL;
    return new_node;
}

void agregar_documento(InvertedIndex **index, int doc_id, char *word)
{
    InvertedIndex *current = *index;

    // aca se busca la word en el index
    while (current != NULL)
    {
        // si la comparacion se cumple, la word ya esta en el index
        if (strcmp(current->word, word) == 0)
        {
            // si la word ya existe, se crea un nuevo nodo para el documento
            Node *new_doc = (Node *)malloc(sizeof(Node));
            new_doc->doc_id = doc_id;
            new_doc->next = current->docs_list;
            current->docs_list = new_doc;
            return;
        }
        current = current->next;
    }

    // si la word no se encuentra en el index, se agrega al index para reconocerla
    InvertedIndex *new_node = crear_nuevo_nodo(word);
    Node *new_doc = (Node *)malloc(sizeof(Node));
    new_doc->doc_id = doc_id;
    new_doc->next = NULL;

    new_node->docs_list = new_doc;
    new_node->next = *index;
    *index = new_node;
}
