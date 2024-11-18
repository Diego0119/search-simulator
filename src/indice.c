#include "graph.h"
#include "inverted_index.h"

// Crea un nuevo nodo en el índice invertido para una palabra específica.
InvertedIndex *create_new_node(char *word)
{
    // Asigna memoria para el nuevo nodo del índice invertido.
    InvertedIndex *new_node = (InvertedIndex *)malloc(sizeof(InvertedIndex));
    if (new_node == NULL)
    {
        fprintf(stderr, "Error al asignar memoria\n");
        exit(EXIT_FAILURE);
    }

    // Copia la palabra en el nodo y establece la lista de documentos y el puntero siguiente a NULL.
    strcpy(new_node->word, word);
    new_node->docs_list = NULL; // Inicializa en NULL porque aún no hay documentos con esta palabra.
    new_node->next = NULL;
    return new_node;
}

// Agrega un documento al índice invertido, asociándolo con una palabra específica.
void add_document(InvertedIndex **hash_table, int doc_id, char *word)
{
    // Calcula el índice en la tabla hash para la palabra.
    unsigned int index = hash_function(word);
    InvertedIndex *current = hash_table[index];

    // Busca la palabra en el índice.
    while (current != NULL)
    {
        if (strcmp(current->word, word) == 0)
        {
            // si la comparacion se cumple, la palabra ya esta en el indice
            Node *new_doc = (Node *)malloc(sizeof(Node));
            new_doc->doc_id = doc_id;
            new_doc->next = current->docs_list;
            current->docs_list = new_doc;
            return;
        }
        current = current->next;
    }

    // Si la palabra no se encuentra en el índice, crea un nuevo nodo en el índice.
    InvertedIndex *new_node = create_new_node(word);
    new_node->next = hash_table[index]; // Posiciona el nuevo nodo en el índice calculado.
    hash_table[index] = new_node;

    // Crea y asigna el nodo de documento.
    Node *new_doc = (Node *)malloc(sizeof(Node));
    if (new_doc == NULL)
    {
        fprintf(stderr, "Error al asignar memoria para nuevo documento\n");
        exit(EXIT_FAILURE);
    }
    new_doc->doc_id = doc_id;
    new_doc->next = NULL;
    new_node->docs_list = new_doc;
}

// Verifica si un token es una palabra irrelevante (stopword) que debe ignorarse en el índice.
bool is_stopword(char *token)
{
    static const char *stopwords[] = {"a", "e", "i", "o", "u", "link"};
    static const int num_stopwords = sizeof(stopwords) / sizeof(stopwords[0]);
    for (int i = 0; i < num_stopwords; i++)
        if (strcmp(token, stopwords[i]) == 0)
            return true; // El token es una stopword.
    // Verificación del patron "docN".
    if (strncmp(token, "doc", 3) == 0) // Comprueba si el token comienza con "doc".
        return true;
    return false; // El token no es una stopword.
}

// Tokeniza el texto de entrada, eliminando puntuación y stopwords, e indexa cada palabra.
void tokenize_text(char *text, int doc_id, InvertedIndex **index)
{
    char *token;

    // Convierte todo el texto a minúsculas.
    for (int i = 0; text[i]; i++)
        text[i] = tolower(text[i]);

    // Reemplaza caracteres de puntuación por espacios.
    for (int i = 0; text[i]; i++)
        if (ispunct(text[i]))
            text[i] = ' ';

    // Separa el texto en palabras utilizando el espacio como delimitador.
    token = strtok(text, " ");

    // Procesa cada token.
    while (token != NULL)
    {
        // Verifica si el token es muy largo.
        if (strlen(token) >= MAX_WORD_SIZE)
        {
            fprintf(stderr, "La palabra es muy larga\n");
            exit(EXIT_FAILURE);
        }

        // Agrega las palabras válidas al índice invertido.
        if (!is_stopword(token))
            add_document(index, doc_id, token);
        token = strtok(NULL, " "); // Avanza al siguiente token.
    }
}

// Imprime el índice invertido mostrando cada palabra y los documentos asociados este es solo para ver el funcionamiento.
void print_inverted_index(InvertedIndex **index)
{
    fprintf(stdout, "\nIndice invertido:\n");
    for (int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        if (index[i] != NULL) // Solo muestra las palabras que existen en este índice.
        {
            InvertedIndex *current = index[i];
            while (current != NULL)
            {
                fprintf(stdout, "Palabra: %s - Documentos: ", current->word);
                Node *doc_node = current->docs_list;
                while (doc_node != NULL)
                {
                    fprintf(stdout, "%d ", doc_node->doc_id); // Imprime el ID de documentos asociados.
                    doc_node = doc_node->next;
                }
                fprintf(stdout, "\n");
                current = current->next;
            }
        }
    }
}

// Función hash para obtener un índice basado en el valor ASCII de los caracteres de una palabra.
unsigned int hash_function(char *word)
{
    unsigned int hash = 0;
    for (int i = 0; word[i] != '\0'; i++) // Recorre cada carácter en la palabra.
        hash = (hash * 31) + word[i];     // Calcula el hash utilizando la codificación ASCII de cada letra.

    return hash % HASH_TABLE_SIZE; // Retorna el hash limitado por el tamaño máximo de palabras.
} /*Edit por segfault, podria causar error por usar MAX_WORD_SIZE en vez de HASH_TABLE_SIZE*/

// Busca una palabra en el índice invertido y retorna la lista de documentos asociados.
Node *search_word(InvertedIndex **hash_table, char *word)
{
    unsigned int index = hash_function(word); // Obtiene el índice de la palabra en la tabla hash.
    InvertedIndex *current = hash_table[index];

    // Busca la palabra en el índice y retorna la lista de documentos si se encuentra.
    while (current != NULL)
    {
        if (strcmp(current->word, word) == 0)
            return current->docs_list;
        current = current->next;
    }

    return NULL; // Retorna NULL si la palabra no se encuentra.
}

void print_search_word(InvertedIndex **index, char *word_to_search)
{
    Node *results = search_word(index, word_to_search);
    if (!results)
    {
        printf("Palabra '%s' no encontrada.\n", word_to_search);
        return;
    }

    // Contador para la cantidad de veces que aparece la palabra en cada documento
    printf("La palabra '%s' se encuentra en los siguientes documentos:\n", word_to_search);
    // contador por documento
    int doc_count[MAX_DOCS] = {0};
    Node *current = results;
    while (current != NULL)
    {
        doc_count[current->doc_id]++;
        current = current->next;
    }

    for (int i = 0; i < MAX_DOCS; i++)
    {
        if (doc_count[i] > 0)
        {
            printf("Doc%d: %d veces\n", i, doc_count[i]);
        }
    }
}
// Lee los archivos que se encuentran guardados en el grafo y crea el indice
void build_index(Graph *graph, InvertedIndex **index)
{
    // Iterar sobre los documentos ya identificados en el grafo.
    for (int i = 0; i < graph->total_docs; i++)
    {
        FILE *file = fopen(graph->mapping_docs[i].name, "r");
        if (file == NULL)
        {
            printf("No se pudo abrir el archivo %s\n", graph->mapping_docs[i].name);
            continue;
        }

        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), file))
        {
            // Procesa cada línea de texto y la pasa al índice.
            tokenize_text(buffer, graph->mapping_docs[i].doc_id, index);
        }
        fclose(file);
    }
}

// Libera la memoria del índice invertido y los nodos de documentos asociados.
void release_inverted_index(InvertedIndex **hash_table)
{
    if (hash_table == NULL)
        return; // Verifica si la tabla hash es nula.

    // Recorre cada índice en la tabla hash.
    for (int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        InvertedIndex *current = hash_table[i];

        // Libera la memoria de cada palabra y su lista de documentos.
        while (current != NULL)
        {
            Node *doc_node = current->docs_list;
            while (doc_node != NULL)
            {
                Node *temp_doc_node = doc_node;
                doc_node = doc_node->next;
                free(temp_doc_node); // Libera cada nodo de documento.
            }
            InvertedIndex *temp = current;
            current = current->next;
            free(temp); // Libera el nodo de la palabra.
        }
        hash_table[i] = NULL;
    }
}
