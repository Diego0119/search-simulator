#include "header.h"

/* Inicializa el grafo estableciendo todas las listas de adyacencia a NULL */
void initialize_graph(Graph *graph)
{
    for (int i = 0; i < MAX_DOCS; i++)
    {
        graph->output_adjacent_list[i] = NULL;
        graph->input_adjacent_list[i] = NULL;
    }
    graph->total_docs = 0;
}

/* Agrega una arista al grafo desde el documento de origen al documento de destino */
void add_edge(Graph *graph, int source, int destination)
{
    Node *newOutputNode = (Node *)malloc(sizeof(Node)); /* Agregar a la lista de enlaces salientes del origen */

    if (newOutputNode == NULL)
    {
        printf("Error al asignar memoria para enlace saliente\n");
        exit(EXIT_FAILURE);
    }

    newOutputNode->doc_id = destination;
    newOutputNode->next = graph->output_adjacent_list[source];
    graph->output_adjacent_list[source] = newOutputNode;

    Node *newInputNode = (Node *)malloc(sizeof(Node)); /* Agregar a la lista de enlaces entrantes del destino */

    if (newInputNode == NULL)
    {
        printf("Error al asignar memoria para enlace entrante\n");
        exit(EXIT_FAILURE);
    }

    newInputNode->doc_id = source;
    newInputNode->next = graph->input_adjacent_list[destination];
    graph->input_adjacent_list[destination] = newInputNode;
}

void build_graph(Graph *graph)
{             /* Construye el grafo leyendo los documentos del directorio actual */
    DIR *dir; /* Abrir el directorio actual */
    struct dirent *ent;

    if ((dir = opendir(".")) == NULL)
    {
        perror("No se pudo abrir el directorio");
        exit(EXIT_FAILURE);
    }

    while ((ent = readdir(dir)) != NULL)
    { /* Leer los archivos del directorio y procesar documentos válidos */

        char *file_name = ent->d_name;

        if (is_doc_name(file_name))
        {
            int doc_id = get_doc_id(graph, file_name); /* Obtener el ID del documento */

            FILE *file = fopen(file_name, "r"); /* Procesar el documento para extraer enlaces */

            if (file == NULL)
            {
                printf("No se pudo abrir el archivo %s\n", file_name);
                continue;
            }

            char line[256];
            while (fgets(line, sizeof(line), file))
            {

                char *ptr = line; /* Buscar enlaces en la línea */

                while ((ptr = strstr(ptr, "link: doc")) != NULL)
                { /* Solamente lee el formato especificado con el espacio */

                    ptr += 9; /* Avanzar después de "link: doc" */
                    int doc_number;

                    if (sscanf(ptr, "%d", &doc_number) != 1)
                    {
                        printf("Formato de enlace inválido en %s\n", file_name);
                        continue;
                    }

                    if (doc_number <= 0 || doc_number > MAX_DOCS)
                    { /* Verificar que el número de documento es válido */
                        printf("Número de documento inválido en enlace: %d\n", doc_number);
                        continue;
                    }

                    char destination_name[256]; /* Construir el nombre del documento destino */
                    sprintf(destination_name, "doc%d.txt", doc_number);

                    FILE *destination_file = fopen(destination_name, "r"); /* Verificar si el documento destino existe */

                    if (destination_file == NULL)
                    {
                        printf("El documento %s enlazado desde %s no existe\n", destination_name, file_name);
                        continue;
                    }

                    fclose(destination_file);

                    /* Obtener el ID del documento destino*/
                    int destination_id = get_doc_id(graph, destination_name);

                    /* Agregar arista al grafo*/
                    add_edge(graph, doc_id, destination_id);
                }
                ptr++;
            }

            fclose(file);
        }
    }

    closedir(dir);
}

void release_graph(Graph *graph)
{ /* Libera la memoria asignada al grafo para evitar fugas de memoria */

    for (int i = 0; i < MAX_DOCS; i++)
    {

        Node *current_output = graph->output_adjacent_list[i];

        while (current_output != NULL)
        {

            Node *temp = current_output;
            current_output = current_output->next;
            free(temp);
        }
        graph->output_adjacent_list[i] = NULL;

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

int count_output_links(Graph *graph, int doc_id)
{ /* Cuenta el número de enlaces salientes de un documento */

    int count = 0;
    Node *current = graph->output_adjacent_list[doc_id];

    while (current != NULL)
    {
        count++;
        current = current->next;
    }

    return count;
}

int count_input_links(Graph *graph, int doc_id)
{ /* Cuenta enlaces entrantes */

    int count = 0;
    Node *current = graph->input_adjacent_list[doc_id];

    while (current != NULL)
    {
        count++;
        current = current->next;
    }

    return count;
}

int get_doc_id(Graph *graph, char *file_name)
{

    for (int i = 0; i < graph->total_docs; i++)
    {
        if (strcmp(graph->mapping_docs[i].name, file_name) == 0)
            return graph->mapping_docs[i].doc_id;
    }

    if (graph->total_docs >= MAX_DOCS)
    {
        printf("Se ha alcanzado el número máximo de documentos\n");
        exit(EXIT_FAILURE);
    }

    int num_doc;

    if (sscanf(file_name, "doc%d.txt", &num_doc) != 1)
    { /* Extraer el número del documento para asignar el ID correctamente */
        printf("Nombre de archivo inválido: %s\n", file_name);
        exit(EXIT_FAILURE);
    }

    /* Guardar el mapeo */
    strcpy(graph->mapping_docs[graph->total_docs].name, file_name);
    graph->mapping_docs[graph->total_docs].doc_id = num_doc;
    graph->total_docs++;

    return num_doc;
}

bool is_doc_name(char *file_name)
{ /* Verifica si el nombre del archivo sigue el patrón "docN.txt" con N >= 1 */

    int len = strlen(file_name);
    if (len < 8)
        return false;

    if (strncmp(file_name, "doc", 3) != 0)
        return false;

    if (strcmp(file_name + len - 4, ".txt") != 0)
        return false;

    for (int i = 3; i < len - 4; i++)
    { /* Verifica que lo que está entre "doc" y ".txt" son números mayores a 0 */

        if (!isdigit(file_name[i]))
            return false;
        if (file_name[i] == '0' && i == 3)
            return false; /* No permite doc0.txt */
    }

    return true;
}

void show_graph(Graph *graph)
{
    printf("Grafo de enlaces:\n");
    for (int i = 0; i < MAX_DOCS; i++)
    {
        if (graph->output_adjacent_list[i] != NULL)
        {
            printf("Documento %d enlaza a: ", i);
            Node *current = graph->output_adjacent_list[i];
            while (current != NULL)
            {
                printf("%d ", current->doc_id);
                current = current->next;
            }
            printf("\n");
        }
    }
}
