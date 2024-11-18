#include "header.h"

// Inicializa el grafo estableciendo listas de adyacencia y total de documentos en cero.
void initialize_graph(Graph *graph)
{
    // Inicializa listas de adyacencia a NULL.
    for (int i = 0; i < MAX_DOCS; i++)
    {
        graph->output_adjacent_list[i] = NULL;
        graph->input_adjacent_list[i] = NULL;
    }
    graph->total_docs = 0; // Inicializa el contador de documentos.
}

// Agrega un enlace dirigido entre dos documentos en el grafo.
void add_edge(Graph *graph, int source, int destination)
{
    // Crea nodo en la lista de enlaces salientes desde el documento de origen al destino.
    Node *newOutputNode = (Node *)malloc(sizeof(Node));
    if (newOutputNode == NULL) // Verifica la asignación de memoria.
    {
        fprintf(stderr, "Error al asignar memoria para enlace saliente\n");
        exit(EXIT_FAILURE);
    }
    newOutputNode->doc_id = destination;                       // Asigna el ID de destino al nodo.
    newOutputNode->next = graph->output_adjacent_list[source]; // Inserta al inicio de la lista
    graph->output_adjacent_list[source] = newOutputNode;

    // Crea nodo en la lista de enlaces entrantes al documento destino desde el origen.
    Node *newInputNode = (Node *)malloc(sizeof(Node));
    if (newInputNode == NULL) // Verifica la asignación de memoria.
    {
        fprintf(stderr, "Error al asignar memoria para enlace entrante\n");
        exit(EXIT_FAILURE);
    }
    newInputNode->doc_id = source;                                // Asigna el ID del origen al nodo.
    newInputNode->next = graph->input_adjacent_list[destination]; // Inserta al inicio de la lista.
    graph->input_adjacent_list[destination] = newInputNode;
}

// Construye el grafo a partir de documentos que contienen enlaces a otros documentos.
void build_graph(Graph *graph)
{
    DIR *dir; // Puntero al directorio actual.
    struct dirent *ent;

    if ((dir = opendir(".")) == NULL) // Abre el directorio actual
    {
        fprintf(stderr, "No se pudo abrir el directorio");
        exit(EXIT_FAILURE);
    }

    // Itera sobre los archivos en el directorio.
    while ((ent = readdir(dir)) != NULL)
    {
        char *file_name = ent->d_name;

        if (is_doc_name(file_name)) // Verifica si el archivo es un documento válido.
        {
            int doc_id = get_doc_id(graph, file_name); // Obtiene el ID del documento.

            FILE *file = fopen(file_name, "r"); // Abre el archivo para leer enlaces.
            if (file == NULL)
            {
                fprintf(stderr, "No se pudo abrir el archivo %s\n", file_name);
                continue;
            }

            char line[256];

            while (fgets(line, sizeof(line), file))
            {
                char *ptr = line; // Apuntador para buscar enlaces en la línea.

                while ((ptr = strstr(ptr, "link: doc")) != NULL) // Busca "link: doc".
                {
                    ptr += 9; // Avanza el puntero después de "link: doc".
                    int doc_number;

                    if (sscanf(ptr, "%d", &doc_number) != 1) // Extrae el número del documento enlazado.
                    {
                        fprintf(stderr, "Formato de enlace inválido en %s\n", file_name);
                        continue;
                    }

                    if (doc_number <= 0 || doc_number > MAX_DOCS) // Verifica si el número de documento es válido
                    {
                        fprintf(stderr, "Número de documento inválido en enlace: %d\n", doc_number);
                        continue;
                    }

                    // Construye el nombre del documento destino.
                    char destination_name[MAX_NAME_DOC];
                    snprintf(destination_name, sizeof(destination_name), "doc%d.txt", doc_number);

                    FILE *destination_file = fopen(destination_name, "r"); // Verifica si el destino existe.
                    if (destination_file == NULL)
                    {
                        fprintf(stderr, "El documento %s enlazado desde %s no existe\n", destination_name, file_name);
                        continue;
                    }
                    fclose(destination_file);

                    // Obtiene el ID del documento destino.
                    int destination_id = get_doc_id(graph, destination_name);

                    // Agrega el enlace entre documentos.
                    add_edge(graph, doc_id, destination_id);
                }
                ptr++;
            }
            fclose(file);
        }
    }
    closedir(dir);
}

// Libera la memoria asignada al grafo para evitar fugas de memoria.
void release_graph(Graph *graph)
{
    for (int i = 0; i < MAX_DOCS; i++)
    {
        // Libera nodos en la lista de enlaces salientes.
        Node *current_output = graph->output_adjacent_list[i];
        while (current_output != NULL)
        {
            Node *temp = current_output;
            current_output = current_output->next;
            free(temp);
        }
        graph->output_adjacent_list[i] = NULL;

        // Libera nodos en la lista de enlaces entrantes.
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

// Cuenta el número de enlaces salientes de un documento.
int count_output_links(Graph *graph, int doc_id)
{
    int count = 0;
    Node *current = graph->output_adjacent_list[doc_id];

    // Recorre la lista y cuenta los enlaces salientes.
    while (current != NULL)
    {
        count++;
        current = current->next;
    }

    return count;
}

// Cuenta el número de enlaces entrantes a un documento.
int count_input_links(Graph *graph, int doc_id)
{
    int count = 0;
    Node *current = graph->input_adjacent_list[doc_id];

    // Recorre la lista y cuenta los enlaces entrantes.
    while (current != NULL)
    {
        count++;
        current = current->next;
    }

    return count;
}

// Obtiene el ID de un documento a partir de su nombre de archivo.
int get_doc_id(Graph *graph, char *file_name)
{
    // Busca el ID en el mapeo de documentos existentes.
    for (int i = 0; i < graph->total_docs; i++)
        if (strcmp(graph->mapping_docs[i].name, file_name) == 0)
            return graph->mapping_docs[i].doc_id;

    // Verifica si se ha alcanzado el límite de documentos permitidos.
    if (graph->total_docs >= MAX_DOCS)
    {
        fprintf(stderr, "Se ha alcanzado el número máximo de documentos\n");
        exit(EXIT_FAILURE);
    }

    int num_doc;

    // Extrae el número del documento del nombre del archivo.
    if (sscanf(file_name, "doc%d.txt", &num_doc) != 1)
    {
        fprintf(stderr, "Nombre de archivo inválido: %s\n", file_name);
        exit(EXIT_FAILURE);
    }

    // Guarda el mapeo del nuevo documento.
    strcpy(graph->mapping_docs[graph->total_docs].name, file_name);
    graph->mapping_docs[graph->total_docs].doc_id = num_doc;
    graph->total_docs++;

    return num_doc;
}

// Verifica si el nombre del archivo sigue el patrón "docN.txt" con N >= 1.
bool is_doc_name(char *file_name)
{
    int len = strlen(file_name);
    if (len < 8) // Longitud mínima para cumplir el formato.
        return false;

    if (strncmp(file_name, "doc", 3) != 0) // Verifica prefijo "doc".
        return false;

    if (strcmp(file_name + len - 4, ".txt") != 0) // Verifica sufijo ".txt".
        return false;

    // Verifica que el número entre "doc" y ".txt" sea válido.
    for (int i = 3; i < len - 4; i++)
    {
        if (!isdigit(file_name[i]))
            return false;
        if (file_name[i] == '0' && i == 3) // No permite doc0.txt.
            return false;
    }

    return true;
}

// Muestra el grafo de enlaces, imprimiendo los documentos y sus enlaces salientes.
void show_graph(Graph *graph)
{
    fprintf(stdout, "Grafo de enlaces:\n");
    for (int i = 0; i < MAX_DOCS; i++)
    {
        if (graph->output_adjacent_list[i] != NULL) // Solo muestra documentos con enlaces.
        {
            fprintf(stdout, "Documento %d enlaza a: ", i);
            Node *current = graph->output_adjacent_list[i];
            while (current != NULL)
            {
                fprintf(stdout, "%d ", current->doc_id); // Imprime el ID de documentos enlazados.
                current = current->next;
            }
            fprintf(stdout, "\n");
        }
    }
}
