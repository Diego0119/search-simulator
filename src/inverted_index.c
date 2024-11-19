/**
 * @file inverted_index.c
 * @date 18-11-2024
 * @authors Miguel Loaiza, Diego Sanhueza, Miguel Maripillan y Felipe Cárcamo
 * @brief Archivo que contiene las funciones del índice invertido.
 *
 * Contiene la implementación de las funciones que crean y manipulan el índice invertido.
 */
#include "graph.h"          ///< Incluye la definición de las estructuras y funciones del grafo.
#include "inverted_index.h" ///< Incluye la definición de las estructuras y funciones del índice invertido.

/**
 * @brief Crea un nuevo nodo en el índice invertido para una palabra específica.
 * @param word La palabra a agregar.
 * @return Un puntero al nuevo nodo creado.
 */
InvertedIndex *create_new_node(char *word)
{
    /**
     * Asigna memoria para el nuevo nodo del índice invertido.
     * Si la asignación falla, se imprime un mensaje de error y el programa termina.
     * @code
     * InvertedIndex *new_node = (InvertedIndex *)malloc(sizeof(InvertedIndex));
     * if (new_node == NULL)
     * {
     *     fprintf(stderr, "Error al asignar memoria\n");
     *     exit(EXIT_FAILURE);
     * }
     * @endcode
     */
    InvertedIndex *new_node = (InvertedIndex *)malloc(sizeof(InvertedIndex));
    if (new_node == NULL)
    {
        fprintf(stderr, "Error al asignar memoria\n");
        exit(EXIT_FAILURE);
    }

    /**
     * Copia la palabra en el nodo y establece la lista de documentos y el puntero siguiente a NULL.
     * Inicialmente, no hay documentos asociados con esta palabra, y el puntero al siguiente nodo también es NULL.
     * @code
     * strcpy(new_node->word, word);
     * new_node->docs_list = NULL;
     * new_node->next = NULL;
     * @endcode
     */
    strcpy(new_node->word, word);
    new_node->docs_list = NULL;
    new_node->next = NULL;
    return new_node;
}

/**
 * @brief Agrega un documento al índice invertido, asociándolo con una palabra específica.
 * @param hash_table Tabla hash que contiene el índice invertido.
 * @param doc_id ID del documento donde aparece la palabra.
 * @param word Palabra que se indexará.
 */
void add_document(InvertedIndex **hash_table, int doc_id, char *word)
{
    /**
     * Calcula el índice en la tabla hash para la palabra.
     * Busca la palabra en la lista enlazada correspondiente al índice.
     * @code
     * unsigned int index = hash_function(word);
     * InvertedIndex *current = hash_table[index];
     * while (current != NULL)
     * {
     *     if (strcmp(current->word, word) == 0)
     *     {
     *         // La palabra ya está en el índice; agrega el documento.
     *         Node *new_doc = (Node *)malloc(sizeof(Node));
     *         new_doc->doc_id = doc_id;
     *         new_doc->next = current->docs_list;
     *         current->docs_list = new_doc;
     *         return;
     *     }
     *     current = current->next;
     * }
     * @endcode
     */
    unsigned int index = hash_function(word);
    InvertedIndex *current = hash_table[index];

    while (current != NULL)
    {
        if (strcmp(current->word, word) == 0)
        {
            Node *new_doc = (Node *)malloc(sizeof(Node));
            new_doc->doc_id = doc_id;
            new_doc->next = current->docs_list;
            current->docs_list = new_doc;
            return;
        }
        current = current->next;
    }

    /**
     * Si la palabra no está en el índice, crea un nuevo nodo y la agrega al índice.
     * También asigna memoria para un nodo que representa el documento.
     * @code
     * InvertedIndex *new_node = create_new_node(word);
     * new_node->next = hash_table[index];
     * hash_table[index] = new_node;
     *
     * Node *new_doc = (Node *)malloc(sizeof(Node));
     * if (new_doc == NULL)
     * {
     *     fprintf(stderr, "Error al asignar memoria para nuevo documento\n");
     *     exit(EXIT_FAILURE);
     * }
     * new_doc->doc_id = doc_id;
     * new_doc->next = NULL;
     * new_node->docs_list = new_doc;
     * @endcode
     */
    InvertedIndex *new_node = create_new_node(word);
    new_node->next = hash_table[index];
    hash_table[index] = new_node;

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

/**
 * @brief Verifica si un token es una palabra irrelevante (stopword) que debe ignorarse en el índice.
 * @param token El token a analizar.
 * @return `true` si el token es una stopword, `false` en caso contrario.
 */
bool is_stopword(char *token)
{
    /**
     * Lista de palabras consideradas como stopwords.
     * @code
     * static const char *stopwords[] = {"a", "e", "i", "o", "u", "link"};
     * static const int num_stopwords = sizeof(stopwords) / sizeof(stopwords[0]);
     * @endcode
     */
    static const char *stopwords[] = {"a", "e", "i", "o", "u", "link"};
    static const int num_stopwords = sizeof(stopwords) / sizeof(stopwords[0]);

    /**
     * Convierte el token a minúsculas para evitar problemas con mayúsculas/minúsculas.
     * @code
     * for (int i = 0; token[i]; i++)
     * {
     *     token[i] = tolower((unsigned char)token[i]);
     * }
     * @endcode
     */
    for (int i = 0; token[i]; i++)
    {
        token[i] = tolower((unsigned char)token[i]);
    }

    /**
     * Compara el token con las stopwords. Si el token es una stopword, devuelve `true`.
     * @code
     * for (int i = 0; i < num_stopwords; i++)
     * {
     *     if (strcmp(token, stopwords[i]) == 0)
     *     {
     *         return true;
     *     }
     * }
     * @endcode
     */
    for (int i = 0; i < num_stopwords; i++)
    {
        if (strcmp(token, stopwords[i]) == 0)
        {
            return true;
        }
    }

    /**
     * Verificación del patrón "docN", donde N es un número.
     * Si el token comienza con "doc" seguido de un número, devuelve `true`.
     * @code
     * if (strncmp(token, "doc", 3) == 0 && isdigit(token[3]))
     * {
     *     return true;
     * }
     * @endcode
     */
    if (strncmp(token, "doc", 3) == 0 && isdigit(token[3]))
    {
        return true;
    }

    return false;
}

/**
 * @brief Tokeniza el texto de entrada, eliminando puntuación y stopwords, e indexa cada palabra.
 * @param text Texto de entrada que será tokenizado.
 * @param doc_id ID del documento al que pertenece el texto.
 * @param index Tabla hash que contiene el índice invertido.
 */
void tokenize_text(char *text, int doc_id, InvertedIndex **index)
{
    char *token;

    /**
     * Convierte todo el texto a minúsculas.
     * @code
     * for (int i = 0; text[i]; i++)
     *     text[i] = tolower(text[i]);
     * @endcode
     */
    for (int i = 0; text[i]; i++)
        text[i] = tolower(text[i]);

    /**
     * Reemplaza caracteres de puntuación por espacios.
     * @code
     * for (int i = 0; text[i]; i++)
     *     if (ispunct(text[i]))
     *         text[i] = ' ';
     * @endcode
     */
    for (int i = 0; text[i]; i++)
        if (ispunct(text[i]))
            text[i] = ' ';

    /**
     * Separa el texto en palabras utilizando el espacio como delimitador.
     * @code
     * token = strtok(text, " ");
     * @endcode
     */
    token = strtok(text, " ");

    /**
     * Procesa cada token.
     * @code
     * while (token != NULL)
     * {
     *     if (strlen(token) >= MAX_WORD_SIZE)
     *     {
     *         fprintf(stderr, "La palabra es muy larga\n");
     *         exit(EXIT_FAILURE);
     *     }
     *     if (!is_stopword(token))
     *         add_document(index, doc_id, token);
     *     token = strtok(NULL, " ");
     * }
     * @endcode
     */
    while (token != NULL)
    {
        if (strlen(token) >= MAX_WORD_SIZE)
        {
            fprintf(stderr, "La palabra es muy larga\n");
            exit(EXIT_FAILURE);
        }

        if (!is_stopword(token))
            add_document(index, doc_id, token);
        token = strtok(NULL, " ");
    }
}

/**
 * @brief Imprime el índice invertido mostrando cada palabra y los documentos asociados.
 * @param index Tabla hash que contiene el índice invertido.
 */
void print_inverted_index(InvertedIndex **index)
{
    fprintf(stdout, "\nIndice invertido:\n");

    /**
     * Recorre la tabla hash y muestra las palabras y sus documentos asociados.
     * @code
     * for (int i = 0; i < HASH_TABLE_SIZE; i++)
     * {
     *     if (index[i] != NULL)
     *     {
     *         InvertedIndex *current = index[i];
     *         while (current != NULL)
     *         {
     *             fprintf(stdout, "Palabra: %s - Documentos: ", current->word);
     *             Node *doc_node = current->docs_list;
     *             while (doc_node != NULL)
     *             {
     *                 fprintf(stdout, "%d ", doc_node->doc_id);
     *                 doc_node = doc_node->next;
     *             }
     *             fprintf(stdout, "\n");
     *             current = current->next;
     *         }
     *     }
     * }
     * @endcode
     */
    for (int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        if (index[i] != NULL)
        {
            InvertedIndex *current = index[i];
            while (current != NULL)
            {
                fprintf(stdout, "Palabra: %s - Documentos: ", current->word);
                Node *doc_node = current->docs_list;
                while (doc_node != NULL)
                {
                    fprintf(stdout, "%d ", doc_node->doc_id);
                    doc_node = doc_node->next;
                }
                fprintf(stdout, "\n");
                current = current->next;
            }
        }
    }
}

/**
 * @brief Función hash para obtener un índice basado en el valor ASCII de los caracteres de una palabra.
 * @param word Palabra a procesar.
 * @return Valor hash de la palabra.
 */

unsigned int hash_function(char *word)
{
    /**
     * Inicializa el valor hash en cero.
     * @code
     * unsigned int hash = 0;
     * @endcode
     */
    unsigned int hash = 0;

    /**
     * Recorre cada carácter en la palabra y actualiza el valor hash.
     * El hash se calcula multiplicando el valor anterior por 31 y sumando el código ASCII de cada carácter.
     * @code
     * for (int i = 0; word[i] != '\0'; i++)
     *     hash = (hash * 31) + word[i];
     * @endcode
     */
    for (int i = 0; word[i] != '\0'; i++)
        hash = (hash * 31) + word[i];

    /**
     * Limita el valor hash por el tamaño máximo de la tabla hash.
     * @code
     * return hash % HASH_TABLE_SIZE;
     * @endcode
     */
    return hash % HASH_TABLE_SIZE;
}

/**
 * @brief Busca una palabra en el índice invertido y retorna la lista de documentos asociados.
 * @param hash_table Tabla hash que contiene el índice invertido.
 * @param word Palabra que se busca en el índice.
 * @return Lista de nodos de documentos donde aparece la palabra, o `NULL` si no se encuentra.
 */
Node *search_word(InvertedIndex **hash_table, char *word)
{
    /**
     * Convierte la palabra a minúsculas para una comparación uniforme.
     * @code
     * for (int i = 0; word[i]; i++)
     *     word[i] = tolower(word[i]);
     * @endcode
     */
    for (int i = 0; word[i]; i++)
        word[i] = tolower(word[i]);

    /**
     * Obtiene el índice en la tabla hash utilizando la función hash.
     * @code
     * unsigned int index = hash_function(word);
     * @endcode
     */
    unsigned int index = hash_function(word);

    /**
     * Inicia la búsqueda en la lista de nodos de la tabla hash.
     * @code
     * InvertedIndex *current = hash_table[index];
     * @endcode
     */
    InvertedIndex *current = hash_table[index];

    /**
     * Recorre los nodos en busca de la palabra, comparando cada nodo con la palabra buscada.
     * Si se encuentra, se retorna la lista de documentos asociados.
     * @code
     * while (current != NULL)
     * {
     *     if (strcmp(current->word, word) == 0)
     *         return current->docs_list;
     *     current = current->next;
     * }
     * @endcode
     */
    while (current != NULL)
    {
        if (strcmp(current->word, word) == 0)
            return current->docs_list; // Retorna la lista de documentos si se encuentra la palabra.
        current = current->next;
    }

    /**
     * Retorna NULL si la palabra no se encuentra en la tabla hash.
     * @code
     * return NULL;
     * @endcode
     */
    return NULL;
}

/**
 * @brief Imprime los documentos y la frecuencia de aparición de una palabra junto con el PageRank.
 * @param index Tabla hash que contiene el índice invertido.
 * @param word_to_search Palabra a buscar en el índice.
 * @param graph Grafo que contiene los documentos.
 * @param pagerank Arreglo de valores de PageRank.
 */
void print_search_word_with_pagerank(InvertedIndex **index, char *word_to_search, Graph *graph, double *pagerank)
{
    /**
     * Verifica que los parámetros no sean nulos.
     * Si alguno lo es, imprime un mensaje de error y retorna.
     * @code
     * if (!index || !word_to_search || !graph || !pagerank)
     * {
     *     fprintf(stderr, "Error: Parámetros nulos pasados a la función.\n");
     *     return;
     * }
     * @endcode
     */
    if (!index || !word_to_search || !graph || !pagerank)
    {
        fprintf(stderr, "Error: Parámetros nulos pasados a la función.\n");
        return;
    }

    /**
     * Busca la palabra en el índice invertido.
     * Si no se encuentra, muestra un mensaje y retorna.
     * @code
     * Node *results = search_word(index, word_to_search);
     * if (!results)
     * {
     *     fprintf(stderr, "Palabra '%s' no encontrada.\n", word_to_search);
     *     return;
     * }
     * @endcode
     */
    Node *results = search_word(index, word_to_search);
    if (!results)
    {
        fprintf(stderr, "Palabra '%s' no encontrada.\n", word_to_search);
        return;
    }

    /**
     * Imprime un mensaje indicando que la palabra se ha encontrado en documentos e inicializa un arreglo para contar la frecuencia de la palabra en cada documento.
     * @code
     * fprintf(stdout, "\nLa palabra '%s' se encuentra en los siguientes documentos:\n\n", word_to_search);
     * int num_docs = graph->total_docs;
     * int doc_count[num_docs + 1];
     * for (int i = 0; i <= num_docs; i++)
     *     doc_count[i] = 0;
     * @endcode
     */
    fprintf(stdout, "\nLa palabra '%s' se encuentra en los siguientes documentos:\n\n", word_to_search);

    int num_docs = graph->total_docs;
    int doc_count[num_docs + 1];
    for (int i = 0; i <= num_docs; i++)
        doc_count[i] = 0;

    /**
     * Recorre la lista de resultados para contar la frecuencia de la palabra en cada documento.
     * Considera solo documentos con identificadores válidos.
     * @code
     * Node *current = results;
     * while (current != NULL)
     * {
     *     if (current->doc_id > 0 && current->doc_id <= num_docs)
     *     {
     *         doc_count[current->doc_id]++;
     *     }
     *     current = current->next;
     * }
     * @endcode
     */
    Node *current = results;
    while (current != NULL)
    {
        if (current->doc_id > 0 && current->doc_id <= num_docs)
        {
            doc_count[current->doc_id]++;
        }
        current = current->next;
    }

    /**
     * Crea un arreglo que contiene todos los documentos.
     * @code
     * int all_docs[num_docs];
     * for (int i = 1; i <= num_docs; i++)
     * {
     *     all_docs[i - 1] = i; 
     * }
     * @endcode
     */
    int all_docs[num_docs];
    for (int i = 1; i <= num_docs; i++)
    {
        all_docs[i - 1] = i; 
    }

    /**
     * Ordena todos los documentos por PageRank en orden descendente.
     * Utiliza un algoritmo de ordenamiento burbuja (bubble sort).
     * @code
     * for (int i = 0; i < num_docs - 1; i++)
     * {
     *     for (int j = i + 1; j < num_docs; j++)
     *     {
     *         int doc_i = all_docs[i];
     *         int doc_j = all_docs[j];
     *         if (pagerank[doc_i - 1] < pagerank[doc_j - 1])
     *         {
     *             int temp = all_docs[i];
     *             all_docs[i] = all_docs[j];
     *             all_docs[j] = temp;
     *         }
     *     }
     * }
     * @endcode
     */
    for (int i = 0; i < num_docs - 1; i++)
    {
        for (int j = i + 1; j < num_docs; j++)
        {
            int doc_i = all_docs[i];
            int doc_j = all_docs[j];
            if (pagerank[doc_i - 1] < pagerank[doc_j - 1])
            {
                int temp = all_docs[i];
                all_docs[i] = all_docs[j];
                all_docs[j] = temp;
            }
        }
    }
    
    /**
     * Imprime solo los documentos donde la palabra fue encontrada (doc_count > 0),
     * junto con la frecuencia y el PageRank.
     * @code
     * for (int i = 0; i < num_docs; i++)
     * {
     *     int doc_id = all_docs[i];
     *     if (doc_count[doc_id] > 0)
     *     {
     *         fprintf(stdout, "Doc%d: %d veces   -   PageRank = %.6f\n", doc_id, doc_count[doc_id], pagerank[doc_id - 1]);
     *     }
     * }
     * @endcode
     */
    for (int i = 0; i < num_docs; i++)
    {
        int doc_id = all_docs[i];
        if (doc_count[doc_id] > 0)
        {
            fprintf(stdout, "Doc%d: %d veces   -   PageRank = %.6f\n", doc_id, doc_count[doc_id], pagerank[doc_id - 1]);
        }
    }
}


/**
 * @brief Lee los archivos asociados al grafo y crea el índice invertido.
 * @param graph Grafo que contiene los datos de los documentos.
 * @param index Tabla hash que contiene el índice invertido.
 */
void build_index(Graph *graph, InvertedIndex **index)
{
    /**
     * Itera sobre los documentos identificados en el grafo.
     * @code
     * for (int i = 0; i < graph->total_docs; i++)
     * {
     *     FILE *file = fopen(graph->mapping_docs[i].name, "r");
     *     if (file == NULL)
     *     {
     *         fprintf(stderr, "No se pudo abrir el archivo %s\n", graph->mapping_docs[i].name);
     *         continue;
     *     }
     * }
     * @endcode
     */
    for (int i = 0; i < graph->total_docs; i++)
    {
        /**
         * Intenta abrir el archivo correspondiente al documento.
         * Si el archivo no puede ser abierto, muestra un error y pasa al siguiente documento.
         * @code
         * FILE *file = fopen(graph->mapping_docs[i].name, "r");
         * if (file == NULL)
         * {
         *     fprintf(stderr, "No se pudo abrir el archivo %s\n", graph->mapping_docs[i].name);
         *     continue;
         * }
         * @endcode
         */
        FILE *file = fopen(graph->mapping_docs[i].name, "r");
        if (file == NULL)
        {
            fprintf(stderr, "No se pudo abrir el archivo %s\n", graph->mapping_docs[i].name);
            continue;
        }

        /**
         * Define un buffer para leer cada línea del archivo.
         * @code
         * char buffer[1024];
         * while (fgets(buffer, sizeof(buffer), file))
         * {
         *     tokenize_text(buffer, graph->mapping_docs[i].doc_id, index);
         * }
         * @endcode
         */
        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), file))
        {
            /**
             * Procesa cada línea del archivo y la pasa a la función tokenize_text,
             * que procesa el texto y lo agrega al índice invertido.
             * @code
             * tokenize_text(buffer, graph->mapping_docs[i].doc_id, index);
             * @endcode
             */
            tokenize_text(buffer, graph->mapping_docs[i].doc_id, index);
        }

        /**
         * Cierra el archivo una vez que ha terminado de procesarlo.
         * @code
         * fclose(file);
         * @endcode
         */
        fclose(file);
    }
}

/**
 * @brief Libera la memoria del índice invertido y los nodos de documentos asociados.
 * @param hash_table Tabla hash que contiene el índice invertido.
 */
void release_inverted_index(InvertedIndex **hash_table)
{
    /**
     * Verifica si la tabla hash es nula y retorna si es el caso.
     * @code
     * if (hash_table == NULL)
     *     return;
     * @endcode
     */
    if (hash_table == NULL)
        return; // Verifica si la tabla hash es nula.

    /**
     * Recorre cada índice en la tabla hash.
     * @code
     * for (int i = 0; i < HASH_TABLE_SIZE; i++)
     * {
     *     InvertedIndex *current = hash_table[i];
     *     ...
     * }
     * @endcode
     */
    for (int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        /**
         * Procesa la lista de palabras asociada a cada índice en la tabla hash.
         * @code
         * InvertedIndex *current = hash_table[i];
         * while (current != NULL)
         * {
         *     Node *doc_node = current->docs_list;
         *     ...
         * }
         * @endcode
         */
        InvertedIndex *current = hash_table[i];

        /**
         * Libera la memoria de cada palabra y su lista de documentos.
         * @code
         * while (current != NULL)
         * {
         *     Node *doc_node = current->docs_list;
         *     while (doc_node != NULL)
         *     {
         *         Node *temp_doc_node = doc_node;
         *         doc_node = doc_node->next;
         *         free(temp_doc_node);
         *     }
         *     InvertedIndex *temp = current;
         *     current = current->next;
         *     free(temp);
         * }
         * @endcode
         */
        while (current != NULL)
        {
            Node *doc_node = current->docs_list;
            while (doc_node != NULL)
            {
                /**
                 * Libera cada nodo de documento.
                 * @code
                 * Node *temp_doc_node = doc_node;
                 * doc_node = doc_node->next;
                 * free(temp_doc_node);
                 * @endcode
                 */
                Node *temp_doc_node = doc_node;
                doc_node = doc_node->next;
                free(temp_doc_node); // Libera cada nodo de documento.
            }
            /**
             * Libera el nodo de la palabra.
             * @code
             * InvertedIndex *temp = current;
             * current = current->next;
             * free(temp);
             * @endcode
             */
            InvertedIndex *temp = current;
            current = current->next;
            free(temp); // Libera el nodo de la palabra.
        }
        /**
         * Establece el índice en la tabla hash como NULL después de liberar su memoria.
         * @code
         * hash_table[i] = NULL;
         * @endcode
         */
        hash_table[i] = NULL;
    }
}
