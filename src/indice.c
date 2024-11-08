#include "header.h"

InvertedIndex *create_new_node(char *word)
{
    InvertedIndex *new_node = (InvertedIndex *)malloc(sizeof(InvertedIndex));
    if (new_node == NULL)
    {
        printf("Error al asignar memoria\n");
        exit(EXIT_FAILURE);
    }
    strcpy(new_node->word, word);
    new_node->docs_list = NULL; // se inicializa en NULL porque al crearlo aun no hay docs con esas palabras
    new_node->next = NULL;
    return new_node;
}

void add_document(InvertedIndex **hash_table, int doc_id, char *word)
{
    unsigned int index = hash_function(word); // dara el hash de la palabra
    InvertedIndex *current = hash_table[index];

    // aca se busca la palabra en el indice
    while (current != NULL)
    {
        // si la comparacion se cumple, la palabra ya esta en el indice
        if (strcmp(current->word, word) == 0)
        {
            // si la palabra ya existe, se crea un nuevo nodo para el documento
            Node *new_doc = (Node *)malloc(sizeof(Node));
            new_doc->doc_id = doc_id;
            new_doc->next = current->docs_list;
            current->docs_list = new_doc;
            return;
        }
        current = current->next;
    }

    // si la palabra no se encuentra en el indice, se agrega al indice para reconocerla
    InvertedIndex *new_node = create_new_node(word);
    new_node->next = hash_table[index]; // posicion index es el hash de la palabra
    hash_table[index] = new_node;       // se crea el indice

    Node *new_doc = (Node *)malloc(sizeof(Node));
    if (new_doc == NULL)
    {
        printf("Error al asignar memoria para nuevo documento\n");
        exit(EXIT_FAILURE);
    }

    new_doc->doc_id = doc_id;
    new_doc->next = NULL;
    new_node->docs_list = new_doc;
}

// aca debo tokenizar el input
void tokenize_text(char *text, int doc_id, InvertedIndex **index)
{
    char *token;

    // se convierte el texto en minuscula
    for (int i = 0; text[i]; i++)
        text[i] = tolower(text[i]);

    // se eliminan algunos caracteres especiales
    // la funcion contempla lo siguiente como caracteres especiales:
    //! " # $ % & ' ( ) * + , - . / : ; < = > ? @ [ \ ] ^ _  { | } ~
    for (int i = 0; text[i]; i++)
    {
        if (ispunct(text[i]))
            text[i] = ' '; // Reemplaza la puntuacion por espacios
    }

    // se tokenizan, strtok acepta un string y un delimitador como segundo argumento, en este caso
    // el espacio " ", nos indica que se acaba una palabra y podemos tokenizarla
    token = strtok(text, " ");

    // En caso de que la palabra sobrepase el buffer...
    if (strlen(token) < MAX_WORD_SIZE)
    {
        fprintf(stderr, "La palabra es muy larga\n");
        exit(EXIT_FAILURE);
    }

    while (token != NULL)
    {
        // agregar las palabras de la entrada al indice
        add_document(index, doc_id, token);

        // se realiza esto para pasar a la siguiente palabra
        token = strtok(NULL, " ");
    }
}

void print_inverted_index(InvertedIndex *index)
{
    InvertedIndex *current = index;
    while (current != NULL)
    {
        printf("Palabra: %s\n", current->word);
        printf("Documentos: ");

        Node *doc = current->docs_list;
        while (doc != NULL)
        {
            printf("%d ", doc->doc_id);
            doc = doc->next;
        }
        printf("\n");

        current = current->next;
    }
}

// con esta funcion de hash va a ser mucho mas rapido buscar en el indice la palabra, y ver los
// documentos que estan conectados
unsigned int hash_function(char *word)
{
    unsigned int hash = 0;                // valor del hash inicial
    for (int i = 0; word[i] != '\0'; i++) // recorre todos los caracteres de la palabra
        hash = (hash * 31) + word[i];     // convierte cada letra en su valor ASCII
    return hash % MAX_WORD_SIZE;
}

Node *search_word(InvertedIndex **hash_table, char *word)
{
    unsigned int index = hash_function(word); // se realiza el hash para encontrar la posicion
    InvertedIndex *current = hash_table[index];

    while (current != NULL)
    {
        // se realiza una busqueda lineal
        if (strcmp(current->word, word) == 0)
            return current->docs_list;
        current = current->next;
    }

    return NULL;
}

// Libera la memoria del indice invertido (Esto es una idea....)
void release_inverted_index(InvertedIndex **hash_table)
{
    // se recorre todo el indice
    for (int i = 0; i < MAX_WORD_SIZE; i++)
    {
        InvertedIndex *current = hash_table[i];
        // se libera la memoria de cada palabra
        while (current != NULL)
        {
            Node *doc_node = current->docs_list;
            while (doc_node != NULL)
            {
                Node *temp_doc_node = doc_node;
                doc_node = doc_node->next;
                free(temp_doc_node);
            }
            InvertedIndex *temp = current;
            current = current->next;
            free(temp);
        }
    }
}
