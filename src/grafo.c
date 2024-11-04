#include "header.h"

/* Variables globales*/
MapeoDocumento mapeo_docs[MAX_DOCS];
int total_docs = 0;

/* Inicializa el grafo estableciendo todas las listas de adyacencia a NULL*/

void inicializar_grafo(Grafo *grafo)
{
    for (int i = 0; i < MAX_DOCS; i++)
    {
        grafo->lista_adyacencia_salida[i] = NULL;
        grafo->lista_adyacencia_entrada[i] = NULL;
    }
}

/* Agrega una arista al grafo desde el documento de origen al documento de destino*/
void agregar_arista(Grafo *grafo, int origen, int destino){
    Nodo *nuevoNodoSalida = (Nodo *)malloc(sizeof(Nodo));    /* Agregar a la lista de enlaces salientes del origen*/
    
    if (nuevoNodoSalida == NULL {
        printf("Error al asignar memoria para enlace saliente\n");
        exit(EXIT_FAILURE);
    }
    
    nuevoNodoSalida->id_doc = destino;
    nuevoNodoSalida->next = grafo->lista_adyacencia_salida[origen];
    grafo->lista_adyacencia_salida[origen] = nuevoNodoSalida;

    Nodo *nuevoNodoEntrada = (Nodo *)malloc(sizeof(Nodo));    /* Agregar a la lista de enlaces entrantes del destino*/ 
    
    if (nuevoNodoEntrada == NULL){
        printf("Error al asignar memoria para enlace entrante\n");
        exit(EXIT_FAILURE);
    }
    
    nuevoNodoEntrada->id_doc = origen;
    nuevoNodoEntrada->next = grafo->lista_adyacencia_entrada[destino];
    grafo->lista_adyacencia_entrada[destino] = nuevoNodoEntrada;

}

void construir_grafo(Grafo *grafo){   /* Construye el grafo leyendo los documentos del directorio actual*/
    DIR *dir;   /* Abrir el directorio actual*/
    struct dirent *ent;
    
    if ((dir = opendir(".")) == NULL){
        perror("No se pudo abrir el directorio");
        exit(EXIT_FAILURE);
    }

    while ((ent = readdir(dir)) != NULL){   /* Leer los archivos del directorio y procesar documentos válidos*/
        
        char *nombre_archivo = ent->d_name;
        
        if (es_nombre_documento(nombre_archivo)) {
            int id_doc = obtener_id_doc(nombre_archivo);   /* Obtener el ID del documento*/

            FILE *archivo = fopen(nombre_archivo, "r");   /* Procesar el documento para extraer enlaces*/
            
            if (archivo == NULL){
                printf("No se pudo abrir el archivo %s\n", nombre_archivo);
                continue;
            }

            char linea[256];
            while (fgets(linea, sizeof(linea), archivo)){
                
                char *ptr = linea;   /* Buscar enlaces en la línea*/
                
                while ((ptr = strstr(ptr, "link: doc")) != NULL){  /* Solamente lee el formato especificado con el espacio*/
                    
                    ptr += 9; /* Avanzar después de "link: doc */
                    int numero_doc;
                    
                    if (sscanf(ptr, "%d", &numero_doc) != 1){
                        printf("Formato de enlace inválido en %s\n", nombre_archivo);
                        continue;
                    }

                    if (numero_doc <= 0 || numero_doc > MAX_DOCS){          /* Verificar que el número de documento es válido*/
                        printf("Número de documento inválido en enlace: %d\n", numero_doc);
                        continue;
                    }

                    char nombre_destino[256]; /* Construir el nombre del documento destino*/
                    sprintf(nombre_destino, "doc%d.txt", numero_doc);

                    FILE *archivo_destino = fopen(nombre_destino, "r");   /* Verificar si el documento destino existe*/
                    
                    if (archivo_destino == NULL){
                        printf("El documento %s enlazado desde %s no existe\n", nombre_destino, nombre_archivo);
                        continue;
                    }
                    
                    fclose(archivo_destino);

                    // Obtener el ID del documento destino
                    int id_destino = obtener_id_doc(nombre_destino);

                    // Agregar arista al grafo
                    agregar_arista(grafo, id_doc, id_destino);
                }
            }

            fclose(archivo);
        }
    }

    closedir(dir);
}


void liberar_grafo(Grafo *grafo){   /* Libera la memoria asignada al grafo para evitar fugas de memoria*/
    
    for (int i = 0; i < MAX_DOCS; i++){
        
        Nodo *actual_salida = grafo->lista_adyacencia_salida[i];
        
        while (actual_salida != NULL){
            
            Nodo *temp = actual_salida;
            actual_salida = actual_salida->next;
            free(temp);
        }
        grafo->lista_adyacencia_salida[i] = NULL;

        Nodo *actual_entrada = grafo->lista_adyacencia_entrada[i];
        while (actual_entrada != NULL){
            
            Nodo *temp = actual_entrada;
            actual_entrada = actual_entrada->next;
            free(temp);
        }
        grafo->lista_adyacencia_entrada[i] = NULL;
    }
}


int contar_enlaces_salida(Grafo *grafo, int id_doc){    /* Cuenta el número de enlaces salientes de un documento*/
    
    int contador = 0;
    Nodo *actual = grafo->lista_adyacencia_salida[id_doc];
    
    while (actual != NULL){    
        contador++;
        actual = actual->next;
    }
    
    return contador;
}


int contar_enlaces_entrada(Grafo *grafo, int id_doc){ /* Cuenta enlaces entrantes*/
    
    int contador = 0;
    Nodo *actual = grafo->lista_adyacencia_entrada[id_doc];
    
    while (actual != NULL){
        contador++;
        actual = actual->next;
    }
    
    return contador;
}

int obtener_id_doc(char *nombre_archivo){
    
    for (int i = 0; i < total_docs; i++){
        if (strcmp(mapeo_docs[i].nombre, nombre_archivo) == 0) {return mapeo_docs[i].id_doc;}
    }

    if (total_docs >= MAX_DOCS) {
        printf("Se ha alcanzado el número máximo de documentos\n");
        exit(EXIT_FAILURE);
    }

    int num_doc; 
    
    if (sscanf(nombre_archivo, "doc%d.txt", &num_doc) != 1){   /* Extraer el número del documento para asignar el ID correctamente*/
        printf("Nombre de archivo inválido: %s\n", nombre_archivo);
        exit(EXIT_FAILURE);
    }

    /* Guardar el mapeo*/
    strcpy(mapeo_docs[total_docs].nombre, nombre_archivo);
    mapeo_docs[total_docs].id_doc = num_doc;
    total_docs++;

    return num_doc;
}

bool es_nombre_documento(char *nombre_archivo){   /* Verifica si el nombre del archivo sigue el patron "docN.txt" con N >= 1 */    

    int len = strlen(nombre_archivo);
    if (len < 8)
        return false;

    if (strncmp(nombre_archivo, "doc", 3) != 0)
        return false;

    if (strcmp(nombre_archivo + len - 4, ".txt") != 0)
        return false;

    for (int i = 3; i < len - 4; i++){ /* Verifica que lo que está entre "doc" y ".txt" son números mayores a 0*/
        
        if (!isdigit(nombre_archivo[i]))
            return false;
        if (nombre_archivo[i] == '0' && i == 3)
            return false; /* No permité doc0.txt*/
    }

    return true;
}
