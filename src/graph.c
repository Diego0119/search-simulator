/**
 * @file graph.c
 * @date 18-11-2024
 * @authors Miguel Loaiza, Diego Sanhueza, Miguel Maripillan y Felipe Cárcamo
 * @brief Archivo que contiene las funciones de los Grafos.
 *
 * Contiene la implementación de las funciones que tiene que ver con los grafos.
 */
#include "graph.h" ///< Incluye la definición de las estructuras y funciones del grafo.

/**
 * @brief Inicializar el Grafo.
 * @param graph Grafo.
 */
void initialize_graph(Graph *graph)
{
    /**
     * Inicializa las listas de enlaces de cada documento.
     * @code
     * for (int i = 0; i < MAX_DOCS; i++)
     * {
     *      graph->output_adjacent_list[i] = NULL;
     *      graph->input_adjacent_list[i] = NULL;
     * }
     * graph->total_docs = 0; // Inicializa el contador de documentos.
     * @endcode
     */
    for (int i = 0; i < MAX_DOCS; i++)
    {
        graph->output_adjacent_list[i] = NULL;
        graph->input_adjacent_list[i] = NULL;
    }
    graph->total_docs = 0;
}

/**
 * @brief Agregar un enlace dirigido entre dos documentos en el grafo.
 * @param graph Grafo.
 * @param source Documento de origen.
 * @param destination Documento de destino.
 */
void add_edge(Graph *graph, int source, int destination)
{
    /**
     * Crea nodo en la lista de enlaces salientes del documento origen al destino. Si no se puede asignar memoria, se muestra un mensaje de error.
     * @code
     * Node *newOutputNode = (Node *)malloc(sizeof(Node));
     * if (newOutputNode == NULL) // Verifica la asignación de memoria.
     * {
     *     fprintf(stderr, "Error al asignar memoria para enlace saliente\n");
     *    exit(EXIT_FAILURE);
     * }
     * newOutputNode->doc_id = destination;
     * newOutputNode->next = graph->output_adjacent_list[source];
     * graph->output_adjacent_list[source] = newOutputNode;
     * @endcode
     */
    Node *newOutputNode = (Node *)malloc(sizeof(Node));
    if (newOutputNode == NULL)
    {
        fprintf(stderr, "Error al asignar memoria para enlace saliente\n");
        exit(EXIT_FAILURE);
    }
    newOutputNode->doc_id = destination;
    newOutputNode->next = graph->output_adjacent_list[source];
    graph->output_adjacent_list[source] = newOutputNode;

    /**
     * Crea nodo en la lista de enlaces entrantes del documento destino al origen. Si no se puede asignar memoria, se muestra un mensaje de error.
     * @code
     * Node *newInputNode = (Node *)malloc(sizeof(Node));
     * if (newInputNode == NULL)
     * {
     *    fprintf(stderr, "Error al asignar memoria para enlace entrante\n");
     *   exit(EXIT_FAILURE);
     * }
     * newInputNode->doc_id = source;
     * newInputNode->next = graph->input_adjacent_list[destination];
     * graph->input_adjacent_list[destination] = newInputNode;
     * @endcode
     */
    Node *newInputNode = (Node *)malloc(sizeof(Node));
    if (newInputNode == NULL)
    {
        fprintf(stderr, "Error al asignar memoria para enlace entrante\n");
        exit(EXIT_FAILURE);
    }
    newInputNode->doc_id = source;
    newInputNode->next = graph->input_adjacent_list[destination];
    graph->input_adjacent_list[destination] = newInputNode;
}

/**
 * @brief Construir el Grafo a partir de documentos que contienen enlaces a otros documentos.
 * @param graph Grafo.
 */
void build_graph(Graph *graph)
{
    /**
     * Abre el directorio actual y verifica si se pudo abrir. Si no se pudo abrir, muestra un mensaje de error y termina el programa.
     * @code
     * DIR *dir;
     * struct dirent *ent;
     * if ((dir = opendir(".")) == NULL)
     * {
     *      fprintf(stderr, "No se pudo abrir el directorio");
     *      exit(EXIT_FAILURE);
     * }
     * @endcode
     */
    DIR *dir;
    struct dirent *ent;

    if ((dir = opendir(".")) == NULL)
    {
        fprintf(stderr, "No se pudo abrir el directorio");
        exit(EXIT_FAILURE);
    }

    /**
     * Itera sobre los archivos en el directorio.
     * @code
     * while ((ent = readdir(dir)) != NULL)
     * {
     *    *Contenido*
     * }
     * closedir(dir);
     * @endcode
     */
    while ((ent = readdir(dir)) != NULL)
    {
        /**
         * Obtiene el nombre del archivo. Verifica si el archivo es un documento válido.
         * @code
         * char *file_name = ent->d_name;
         * if (is_doc_name(file_name))
         * {
         *      *Contenido*
         * }
         * @endcode
         */
        char *file_name = ent->d_name;

        if (is_doc_name(file_name))
        {
            /**
             * Obtiene el ID del documento. Abre el archivo para leer enlaces. Si no se pudo abrir, muestra un mensaje de error.
             * @code
             * int doc_id = get_doc_id(graph, file_name);
             * FILE *file = fopen(file_name, "r");
             * if (file == NULL)
             * {
             *      fprintf(stderr, "No se pudo abrir el archivo %s\n", file_name);
             *      continue;
             * }
             * char line[256];
             * while (fgets(line, sizeof(line), file))
             * {
             *      *Contenido*
             * }
             * fclose(file);
             * @endcode
             */
            int doc_id = get_doc_id(graph, file_name);

            FILE *file = fopen(file_name, "r");
            if (file == NULL)
            {
                fprintf(stderr, "No se pudo abrir el archivo %s\n", file_name);
                continue;
            }

            char line[256];

            while (fgets(line, sizeof(line), file))
            {
                /**
                 * Busca enlaces en la línea. Extrae el número del documento enlazado. Verifica si el número de documento es válido.
                 * @code
                 * char *ptr = line;
                 * while ((ptr = strstr(ptr, "link: doc")) != NULL)
                 * {
                 *      ptr += 9;
                 *      int doc_number;
                 *      if (sscanf(ptr, "%d", &doc_number) != 1)
                 *      {
                 *          fprintf(stderr, "Formato de enlace inválido en %s\n", file_name);
                 *          continue;
                 *      }
                 *      if (doc_number <= 0 || doc_number > MAX_DOCS)
                 *      {
                 *          fprintf(stderr, "Número de documento inválido en enlace: %d\n", doc_number);
                 *          continue;
                 *      }
                 * }
                 * ptr++;
                 * @endcode
                 */
                char *ptr = line;

                while ((ptr = strstr(ptr, "link: doc")) != NULL)
                {
                    ptr += 9;
                    int doc_number;

                    if (sscanf(ptr, "%d", &doc_number) != 1)
                    {
                        fprintf(stderr, "Formato de enlace inválido en %s\n", file_name);
                        continue;
                    }

                    if (doc_number <= 0 || doc_number > MAX_DOCS)
                    {
                        fprintf(stderr, "Número de documento inválido en enlace: %d\n", doc_number);
                        continue;
                    }

                    /**
                     * Construye el nombre del documento destino. Verifica si el destino existe.
                     * Obtiene el ID del documento destino. Agrega el enlace entre documentos.
                     * @code
                     * char destination_name[MAX_NAME_DOC];
                     * snprintf(destination_name, sizeof(destination_name), "doc%d.txt", doc_number);
                     * FILE *destination_file = fopen(destination_name, "r");
                     * if (destination_file == NULL)
                     * {
                     *     fprintf(stderr, "El documento %s enlazado desde %s no existe\n", destination_name, file_name);
                     *    continue;
                     * }
                     * fclose(destination_file);
                     * int destination_id = get_doc_id(graph, destination_name);
                     * add_edge(graph, doc_id, destination_id);
                     * @endcode
                     */
                    char destination_name[MAX_NAME_DOC];
                    snprintf(destination_name, sizeof(destination_name), "doc%d.txt", doc_number);

                    FILE *destination_file = fopen(destination_name, "r");
                    if (destination_file == NULL)
                    {
                        fprintf(stderr, "El documento %s enlazado desde %s no existe\n", destination_name, file_name);
                        continue;
                    }
                    fclose(destination_file);

                    int destination_id = get_doc_id(graph, destination_name);

                    add_edge(graph, doc_id, destination_id);
                }
                ptr++;
            }
            fclose(file);
        }
    }
    closedir(dir);
}

/**
 * @brief Libera la memoria del grafo (nodos).
 * @param graph Grafo.
 */
void release_graph(Graph *graph)
{
    for (int i = 0; i < MAX_DOCS; i++)
    {
        /**
         * Libera nodos en la lista de enlaces salientes.
         * @code
         * Node *current_output = graph->output_adjacent_list[i];
         * while (current_output != NULL)
         * {
         *      Node *temp = current_output;
         *      current_output = current_output->next;
         *      free(temp);
         * }
         * graph->output_adjacent_list[i] = NULL;
         * @endcode
         */
        Node *current_output = graph->output_adjacent_list[i];
        while (current_output != NULL)
        {
            Node *temp = current_output;
            current_output = current_output->next;
            free(temp);
        }
        graph->output_adjacent_list[i] = NULL;

        /**
         * Libera nodos en la lista de enlaces entrantes.
         * @code
         * Node *current_input = graph->input_adjacent_list[i];
         * while (current_input != NULL)
         * {
         *      Node *temp = current_input;
         *      current_input = current_input->next;
         *      free(temp);
         * }
         * graph->input_adjacent_list[i] = NULL;
         * @endcode
         */
        Node *current_input = graph->input_adjacent_list[i];
        while (current_input != NULL)
        {
            Node *temp = current_input;
            current_input = current_input->next;
            free(temp);
        }
        graph->input_adjacent_list[i] = NULL;
    }
}

/**
 * @brief Contar el número de enlaces salientes de un documento.
 * @param graph Grafo.
 * @param doc_id ID del documento.
 * @return int
 */
int count_output_links(Graph *graph, int doc_id)
{
    /**
     * Recorre la lista y cuenta los enlaces salientes.
     * @code
     * int count = 0;
     * Node *current = graph->output_adjacent_list[doc_id];
     * while (current != NULL)
     * {
     *      count++;
     *      current = current->next;
     * }
     * return count;
     * @endcode
     */
    int count = 0;
    Node *current = graph->output_adjacent_list[doc_id];

    while (current != NULL)
    {
        count++;
        current = current->next;
    }

    return count;
}

/**
 * @brief Contar el número de enlaces entrantes a un documento.
 * @param graph Grafo.
 * @param doc_id ID del documento.
 * @return int
 */
int count_input_links(Graph *graph, int doc_id)
{
    /**
     * Recorre la lista y cuenta los enlaces entrantes.
     * @code
     * int count = 0;
     * Node *current = graph->input_adjacent_list[doc_id];
     * while (current != NULL)
     * {
     *      count++;
     *      current = current->next;
     * }
     * return count;
     * @endcode
     */
    int count = 0;
    Node *current = graph->input_adjacent_list[doc_id];

    while (current != NULL)
    {
        count++;
        current = current->next;
    }

    return count;
}

/**
 * @brief Obtiene el ID de un documento a partir de su nombre de archivo.
 * @param graph Grafo.
 * @param file_name Nombre del archivo.
 * @return int
 */
int get_doc_id(Graph *graph, char *file_name)
{
    /**
     * Busca el ID en el mapeo de documentos existentes.
     * @code
     * for (int i = 0; i < graph->total_docs; i++)
     *      if (strcmp(graph->mapping_docs[i].name, file_name) == 0)
     *          return graph->mapping_docs[i].doc_id;
     * @endcode
     * Verifica si se ha alcanzado el límite de documentos permitidos.
     * @code
     * if (graph->total_docs >= MAX_DOCS)
     * {
     *      fprintf(stderr, "Se ha alcanzado el número máximo de documentos\n");
     *      exit(EXIT_FAILURE);
     * }
     * @endcode
     */
    for (int i = 0; i < graph->total_docs; i++)
        if (strcmp(graph->mapping_docs[i].name, file_name) == 0)
            return graph->mapping_docs[i].doc_id;

    if (graph->total_docs >= MAX_DOCS)
    {
        fprintf(stderr, "Se ha alcanzado el número máximo de documentos\n");
        exit(EXIT_FAILURE);
    }

    int num_doc;

    /**
     * Extrae el número del documento del nombre del archivo.
     * @code
     * int num_doc;
     * if (sscanf(file_name, "doc%d.txt", &num_doc) != 1)
     * {
     *      fprintf(stderr, "Nombre de archivo inválido: %s\n", file_name);
     *      exit(EXIT_FAILURE);
     * }
     * @endcode
     * Guarda el mapeo del nuevo documento.
     * @code
     * strcpy(graph->mapping_docs[graph->total_docs].name, file_name);
     * graph->mapping_docs[graph->total_docs].doc_id = num_doc;
     * graph->total_docs++;
     * return num_doc;
     * @endcode
     */
    if (sscanf(file_name, "doc%d.txt", &num_doc) != 1)
    {
        fprintf(stderr, "Nombre de archivo inválido: %s\n", file_name);
        exit(EXIT_FAILURE);
    }

    strcpy(graph->mapping_docs[graph->total_docs].name, file_name);
    graph->mapping_docs[graph->total_docs].doc_id = num_doc;
    graph->total_docs++;

    return num_doc;
}

/**
 * @brief Verifica si el nombre del archivo sigue el patrón "docN.txt" con N >= 1.
 * @param file_name Nombre del archivo.
 * @return bool
 */
bool is_doc_name(char *file_name)
{
    /**
     * Verifica si el nombre del archivo sigue el patrón "docN.txt" con N >= 1.
     * @code
     * int len = strlen(file_name);
     * if (len < 8)
     *      return false;
     * if (strncmp(file_name, "doc", 3) != 0)
     *      return false;
     * if (strcmp(file_name + len - 4, ".txt") != 0)
     *      return false;
     * for (int i = 3; i < len - 4; i++)
     * {
     *      if (!isdigit(file_name[i]))
     *          return false;
     *      if (file_name[i] == '0' && i == 3)
     *          return false;
     * }
     * return true;
     * @endcode
     */
    int len = strlen(file_name);
    if (len < 8)
        return false;

    if (strncmp(file_name, "doc", 3) != 0)
        return false;

    if (strcmp(file_name + len - 4, ".txt") != 0)
        return false;

    for (int i = 3; i < len - 4; i++)
    {
        if (!isdigit(file_name[i]))
            return false;
        if (file_name[i] == '0' && i == 3)
            return false;
    }

    return true;
}

/**
 * @brief Muestra el grafo de enlaces, imprimiendo los documentos y sus enlaces salientes.
 * @param graph Grafo.
 */
void show_graph(Graph *graph)
{
    /**
     * Muestra los enlaces de cada documento.
     * @code
     * fprintf(stdout, "\nGrafo de enlaces:\n\n");
     * for (int i = 0; i < MAX_DOCS; i++)
     * {
     *      if (graph->output_adjacent_list[i] != NULL)
     *      {
     *          fprintf(stdout, "Documento %d enlaza a: ", i);
     *          Node *current = graph->output_adjacent_list[i];
     *          while (current != NULL)
     *          {
     *              fprintf(stdout, "%d ", current->doc_id);
     *              current = current->next;
     *          }
     *          fprintf(stdout, "\n");
     *      }
     * }
     * @endcode
     */
    fprintf(stdout, "\nGrafo de enlaces:\n\n");
    for (int i = 0; i < MAX_DOCS; i++)
    {
        if (graph->output_adjacent_list[i] != NULL)
        {
            fprintf(stdout, "Documento %d enlaza a: ", i);
            Node *current = graph->output_adjacent_list[i];
            while (current != NULL)
            {
                fprintf(stdout, "%d ", current->doc_id);
                current = current->next;
            }
            fprintf(stdout, "\n");
        }
    }
}
